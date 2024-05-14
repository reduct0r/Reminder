#include "Database.h"
using namespace Reminder;

std::string Database::hashPassword(const std::string &password) {
  // Создание объекта контекста хеширования SHA-256
  EVP_MD_CTX *mdctx = EVP_MD_CTX_new();
  const EVP_MD *md = EVP_sha256();

  unsigned char hash[SHA256_DIGEST_LENGTH];

  // Инициализация контекста хеширования
  EVP_DigestInit_ex(mdctx, md, nullptr);

  // Обновление контекста хеширования данными пароля
  EVP_DigestUpdate(mdctx, password.c_str(), password.length());

  // Получение хеша
  unsigned int hash_len;
  EVP_DigestFinal_ex(mdctx, hash, &hash_len);

  // Освобождение контекста хеширования
  EVP_MD_CTX_free(mdctx);

  // Преобразование хеша в строку
  std::stringstream ss;
  for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
    ss << std::hex << std::setw(2) << std::setfill('0') << (int) hash[i];
  }
  return ss.str();
}

bool Database::comparePasswords(const std::string &loginUsedPassword, const std::string &databaseHashedPassword) {
  return Database::hashPassword(loginUsedPassword) == databaseHashedPassword;
}

UserDAO Database::createUser(const std::string &username, const std::string &password) {
  try {
    std::string usernameToLowerCase = username;
    std::transform(usernameToLowerCase.begin(),
                   usernameToLowerCase.end(),
                   usernameToLowerCase.begin(),
                   [](unsigned char c) { return std::tolower(c); });

    std::string hashedPassword = hashPassword(password);
    pqxx::work tunnel(connection);
    std::string sessionId = SessionIdService::generateRandomKey();
    std::string query =
        "INSERT INTO " + usersTableName + " (username, password, session_id) VALUES ('" + usernameToLowerCase + "', '" +
            hashedPassword + "', '" + sessionId + "');";
    tunnel.exec(query);
    tunnel.commit();

    UserDAO newUser(usernameToLowerCase, password, sessionId);
    SessionIdService::saveNewSessionId(sessionId);
    return newUser;
  } catch (const pqxx::unique_violation &e) {
    return {};
  }
}

UserDAO Database::getUser(UserDAO &user) {
  std::string usernameToLowerCase = user.GetUsername();
  std::transform(usernameToLowerCase.begin(),
                 usernameToLowerCase.end(),
                 usernameToLowerCase.begin(),
                 [](unsigned char c) { return std::tolower(c); });

  pqxx::work tunnel(connection);
  std::string
      queryPassword = "SELECT password FROM " + usersTableName + " WHERE username = '" + usernameToLowerCase + "';";
  std::string
      querySessionId = "SELECT username FROM " + usersTableName + " WHERE username = '" + usernameToLowerCase + "';";
  pqxx::result password = tunnel.exec(queryPassword);
  pqxx::result sessionId = tunnel.exec(querySessionId);
  tunnel.commit();

  if (password[0][0].as<std::string>() == user.GetPassword()
      && user.GetUsername() == sessionId[0][0].as<std::string>()) {
    UserDAO existingUser(usernameToLowerCase, password[0][0].as<std::string>(), sessionId[0][0].as<std::string>());
    SessionIdService::saveNewSessionId(sessionId[0][0].as<std::string>());
    return existingUser;
  }

  if (password.empty() && sessionId.empty()) {
    return {};
  }
  return {};
}

void Database::parseConfigFile() {
  std::ifstream file("/Users/exist/CLionProjects/Reminder/Reminder/Auth/DatabaseConfig.json");
  if (!file.is_open()) {
    std::cerr << "Невозможно открыть JSON файл" << std::endl;
    exit(1);
  }

  Json::Value root;
  Json::CharReaderBuilder builder;
  std::string errs;
  bool parsingSuccessful = Json::parseFromStream(builder, file, &root, &errs);
  file.close();

  if (!parsingSuccessful) {
    std::cerr << "Ошибка парсинга JSON: " << errs << std::endl;
    exit(1);
  }

  connectionString = root["connectionString"].asString();
  usersTableName = root["usersTableName"].asString();
}

UserDAO Database::containsSessionId(const std::string &sessionIdToken) {
  if (sessionIdToken.empty()) {
    return {};
  }

  pqxx::work tunnel(connection);
  std::string
      queryPassword = "SELECT username FROM " + usersTableName + " WHERE session_id = '" + sessionIdToken + "';";
  std::string
      querySessionId = "SELECT password FROM " + usersTableName + " WHERE session_id = '" + sessionIdToken + "';";
  pqxx::result username = tunnel.exec(queryPassword);
  pqxx::result password = tunnel.exec(querySessionId);

  auto usernameToLowerCase = username[0][0].as<std::string>();
  std::transform(usernameToLowerCase.begin(),
                 usernameToLowerCase.end(),
                 usernameToLowerCase.begin(),
                 [](unsigned char c) { return std::tolower(c); });

  tunnel.commit();
  if (username.empty() && password.empty()) {
    return {};
  }
  UserDAO existingUser(usernameToLowerCase, password[0][0].as<std::string>(), sessionIdToken);
  return existingUser;
}

int Database::countDatabasePresets(UserDAO &user) {
  pqxx::work tunnel(connection); // Туннель для работы с бд
  std::string query =
      "SELECT count(*) FROM presets WHERE username = " + user.GetUsername() + ";"; // Запрос в бд для получения пресетов
  pqxx::result result = tunnel.exec(query);
  tunnel.commit();

  if (result.empty()) {
    return 0;
  } else {
    return result[0][0].as<int>();
  }
}

std::vector<CardPreset> Database::getUserPresets(UserDAO &user) {
  std::vector<Reminder::CardPreset> presets; // Вектор для хранения пресетов из бд
  try {
    pqxx::work tunnel(connection); // Туннель для работы с бд
    std::string query = "SELECT presets_data FROM presets WHERE username = " + user.GetUsername()
        + ";"; // Запрос в бд для получения пресетов
    pqxx::result result = tunnel.exec(query); // Вызов запроса
    tunnel.commit();

    if (result.empty()) {
      return {};
    } else {
      for (const auto &row : result) {
        auto json_data = row[0].as<std::string>();
        Json::CharReaderBuilder builder;
        Json::CharReader *reader = builder.newCharReader();
        Json::Value root;
        std::string errors;
        if (!reader->parse(json_data.c_str(), json_data.c_str() + json_data.length(), &root, &errors)) {
          std::cerr << "Ошибка при разборе JSON: " << errors << std::endl;
          delete reader;
          continue;
        }
        delete reader;

        CardPreset preset(root["preset_name"].asString());
        preset.number = root["number"].asInt();

        for (const auto &card_json : root["cards"]) {
          Card card(card_json["card_name"].asString(), card_json["description"].asString());
          card.setNumber(card_json["card_number"].asInt());
          preset.preset.push_back(card);
        }
        presets.push_back(preset);
      }
      return presets;
    }
  } catch (const std::exception &e) {
    std::cerr << "Ошибка при выполнении запроса: " << e.what() << std::endl;
    return {};
  }
}

bool Database::deletePreset(const std::string &presetName, UserDAO &user) {
  try {
    pqxx::work txn(connection);

    std::string query =
        "DELETE FROM presets WHERE username = '" + user.GetUsername() + "' AND presets @> '[{\"presetName\": \""
            + presetName + "\"}]'";

    pqxx::result result = txn.exec(query);

    txn.commit();

    return result.affected_rows() > 0;
  } catch (const std::exception &e) {
    std::cerr << "Ошибка при выполнении запроса: " << e.what() << std::endl;
    return false;
  }
}

bool Database::addUserPreset(CardPreset &cardPreset, UserDAO &user) {
  try {
    pqxx::work txn(connection);

    std::string query =
        "UPDATE presets SET presets = presets || '" + cardPreset.toJson() + "' WHERE username = '" + user.GetUsername() + "'";

    pqxx::result result = txn.exec(query);

    txn.commit();

    return result.affected_rows() > 0;
  } catch (const std::exception &e) {
    std::cerr << "Ошибка при выполнении запроса: " << e.what() << std::endl;
    return false;
  }
}
