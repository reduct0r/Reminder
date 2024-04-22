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

std::string Database::addUser(const std::string &username, const std::string &password) {
  try {
    std::string usernameToLowerCase = username;
    std::transform(usernameToLowerCase.begin(),
                   usernameToLowerCase.end(),
                   usernameToLowerCase.begin(),
                   [](unsigned char c) { return std::tolower(c); });

    std::string hashedPassword = hashPassword(password);
    pqxx::work tunnel(connection);
    std::string query =
        "INSERT INTO " + usersTableName + " (username, password) VALUES ('" + usernameToLowerCase + "', '" +
            hashedPassword + "');";
    tunnel.exec(query);
    tunnel.commit();

    std::string returnString =
        "Новая запись в таблице:\n{\n'username':'" + usernameToLowerCase + "',\n'encryptedPassword':'" + hashedPassword
            +
                "'\n}";
    return returnString;
  } catch (const pqxx::unique_violation &e) {
    return "Такой никнейм уже занят! Придумайте что-то другое :)\n";
  }
}

std::string Database::getPassword(const std::string &username) {
  std::string usernameToLowerCase = username;
  std::transform(usernameToLowerCase.begin(),
                 usernameToLowerCase.end(),
                 usernameToLowerCase.begin(),
                 [](unsigned char c) { return std::tolower(c); });
  pqxx::work tunnel(connection);
  std::string query = "SELECT password FROM " + usersTableName + " WHERE username = '" + usernameToLowerCase + "';";
  pqxx::result result = tunnel.exec(query);
  tunnel.commit();
  if (result.empty()) {
    return "Пользователя с такими никнеймом не существует! Проверьте правильность введенных данных\n";
  }
  return result[0][0].as<std::string>();
}

void Database::parseConfigFile() {
  std::ifstream file("/Users/exist/CLionProjects/Reminder/Reminder/Database/DatabaseConfig.json");
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
