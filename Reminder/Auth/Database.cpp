#include "Database.h"
using namespace Reminder;

std::string Database::hashPassword(const std::string &password) {
  EVP_MD_CTX *mdctx = EVP_MD_CTX_new();
  const EVP_MD *md = EVP_sha256();

  unsigned char hash[SHA256_DIGEST_LENGTH];

  EVP_DigestInit_ex(mdctx, md, nullptr);

  EVP_DigestUpdate(mdctx, password.c_str(), password.length());

  unsigned int hash_len;
  EVP_DigestFinal_ex(mdctx, hash, &hash_len);

  EVP_MD_CTX_free(mdctx);

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
  try {
    std::string usernameToLowerCase = user.getUsername();
    std::transform(usernameToLowerCase.begin(),
                   usernameToLowerCase.end(),
                   usernameToLowerCase.begin(),
                   [](unsigned char c) { return std::tolower(c); });

    pqxx::work tunnel(connection);

    std::string
        queryPassword = "SELECT password FROM " + usersTableName + " WHERE username = '" + usernameToLowerCase + "';";
    std::string
        queryUsername = "SELECT username FROM " + usersTableName + " WHERE username = '" + usernameToLowerCase + "';";
    std::string
        querySessionId =
        "SELECT session_id FROM " + usersTableName + " WHERE username = '" + usernameToLowerCase + "';";

    pqxx::result password = tunnel.exec(queryPassword);
    pqxx::result username = tunnel.exec(queryUsername);
    pqxx::result sessionId = tunnel.exec(querySessionId);

    tunnel.commit();

    if (comparePasswords(user.getPassword(), password[0][0].as<std::string>())
        && user.getUsername() == username[0][0].as<std::string>()) {
      UserDAO existingUser(usernameToLowerCase, password[0][0].as<std::string>(), sessionId[0][0].as<std::string>());
      SessionIdService::saveNewSessionId(sessionId[0][0].as<std::string>());
      return existingUser;
    }

    if (password.empty() && username.empty()) {
      return {};
    }
    return {};
  } catch (const std::exception &e) {
    return {};
  }
}

std::string Database::parseConfigFile() {
  std::ifstream file("Config/DatabaseConfig.json");
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

  usersTableName = root["usersTableName"].asString();
  return root["connectionString"].asString();
}

UserDAO Database::containsSessionId(const std::string &sessionIdToken) {
  if (sessionIdToken.empty()) {
    return {};
  }
  try {
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
  } catch (const std::exception &e) {
    return {};
  }
}

std::vector<CardPreset> Database::getUserPresets(UserDAO &user) {
  try {
    std::vector<CardPreset> presets;
    pqxx::work tunnel(connection);

    std::string query = "SELECT presets FROM users WHERE username = \'" + user.getUsername() + "\';";
    pqxx::result result = tunnel.exec(query);
    tunnel.commit();

    if (result.empty()) {
      return {};
    } else {
      for (const auto &row : result) {
        if (row[0].is_null()) {
          continue;
        }

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

        for (const auto &preset_json : root) {
          CardPreset preset(preset_json["presetName"].asString());
          for (const auto &card_json : preset_json["cards"]) {
            Card card(card_json["title"].asString(), card_json["description"].asString());
            card.setNumber(card_json["cardId"].asInt());
            preset.addCard(card);
          }
          presets.push_back(preset);
        }
      }
      return presets;
    }
  } catch (const std::exception &e) {
    return {};
  }
}

bool Database::deleteUserPreset(const std::string &presetName, UserDAO &user) {
  try {
    pqxx::work txn(connection);

    std::string query =
        "UPDATE users\n"
        "SET presets = (\n"
        "    SELECT jsonb_agg(elem) \n"
        "    FROM jsonb_array_elements(presets) elem\n"
        "    WHERE elem->>'presetName' <> \'" + presetName + "\'\n"
        ")\n"
        "WHERE username = \'" + user.getUsername() + "\';";

    pqxx::result result = txn.exec(query);

    txn.commit();

    return result.affected_rows() > 0;
  } catch (const std::exception &e) {
    return false;
  }
}

bool Database::addUserPreset(CardPreset &cardPreset, UserDAO &user) {
  try {
    pqxx::work txn(connection);

    std::string query =
        "UPDATE users\n"
        "SET presets = COALESCE(presetsName, '[]'::jsonb) || '[" + cardPreset.toJson() + "]'::jsonb\n"
        "WHERE username = \'"
        + user.getUsername() + "\';";

    pqxx::result result = txn.exec(query);

    txn.commit();

    return result.affected_rows() > 0;
  } catch (const std::exception &e) {
    return false;
  }
}
