#include "Database.h"
using namespace Reminder;

std::string decryptPassword(const std::string &password) {
  std::string decryptedPassword = password.substr(0, password.length() - 10);
  return decryptedPassword;
}

std::string encryptPassword(const std::string &password) {
  std::string encryptedPassword = password + "ENCRYPTION";
  return encryptedPassword;
}

std::string Database::addUser(const std::string &username, const std::string &password) {
  try {
    std::string encryptedPassword = encryptPassword(password);
    pqxx::work tunnel(connection);
    std::string query =
        "INSERT INTO " + usersTableName + " (username, password) VALUES ('" + username + "', '" +
            encryptedPassword + "');";
    tunnel.exec(query);
    tunnel.commit();

    std::string returnString =
        "New user added:\n{\n'username':'" + username + "',\n'encryptedPassword':'" + encryptedPassword +
            "'\n}";
    return returnString;
  } catch (const pqxx::unique_violation &e) {
    return "Username is already taken :( Take another one!";
  }
}

std::string Database::getPassword(const std::string &name) {
  pqxx::work tunnel(connection);
  std::string query = "SELECT password FROM " + usersTableName + " WHERE username = '" + name + "';";
  pqxx::result result = tunnel.exec(query);
  tunnel.commit();
  if (result.empty()) {
    return "There is no user with this name";
  }
  return decryptPassword(result[0][0].as<std::string>());
}

void Database::parseConfigFile() {
  std::ifstream file("/Users/exist/CLionProjects/Reminder/Reminder/Database/DatabaseConfig.json");
  if (!file.is_open()) {
    std::cerr << "Unable to open JSON file" << std::endl;
    exit(1);
  }

  Json::Value root;
  Json::CharReaderBuilder builder;
  std::string errs;
  bool parsingSuccessful = Json::parseFromStream(builder, file, &root, &errs);
  file.close();

  if (!parsingSuccessful) {
    std::cerr << "Error parsing JSON: " << errs << std::endl;
    exit(1);
  }

  connectionString = root["connectionString"].asString();
  usersTableName = root["usersTableName"].asString();
}
