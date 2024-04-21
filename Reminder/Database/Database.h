#ifndef REMINDER_REMINDER_DATABASE_DATABASE_H_
#define REMINDER_REMINDER_DATABASE_DATABASE_H_

#include <string>
#include "pqxx/pqxx"
#include <iostream>
#include <json/json.h>
#include <fstream>

namespace {
class Database {
 private:
  pqxx::connection connection;
  std::string connectionString;
  std::string usersTableName;
 public:
  Database() {
    initDatabase();
  }

  virtual ~Database() {
    connection.close();
  }

  void initDatabase() {
    parseConfigFile();
    connection = pqxx::connection(connectionString);
    if (!connection.is_open()) {
      std::cerr << "Ошибка: Невозможно открыть базу данных\n";
      exit(1);
    }
  }

  void parseConfigFile() {
    std::ifstream file("/Users/exist/CLionProjects/Reminder/Reminder/Database/DatabaseConfig.json");
    if (!file.is_open()) {
      std::cerr << "Не удалось открыть файл JSON" << std::endl;
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

  void addRecord(const std::string &username, const std::string &password) {
    pqxx::work txn(connection);
    std::string query = "INSERT INTO" + usersTableName + "VALUES ('" + username + "', '" + password + "')";
    txn.exec(query);
    txn.commit();
    std::cout << "Запись добавлена успешно\n";
  }

  std::string getValue(const std::string &name) {
    pqxx::work txn(connection);
    std::string query = "SELECT password FROM" + usersTableName + "WHERE name = '" + name + "'";
    pqxx::result result = txn.exec(query);
    txn.commit();

    if (result.empty()) {
      std::cerr << "Ошибка: Нет записи с таким именем\n";
      return "";
    }
    return result[0][0].as<std::string>();
  }
};
}

#endif
