#ifndef REMINDER_REMINDER_DATABASE_DATABASE_H_
#define REMINDER_REMINDER_DATABASE_DATABASE_H_

#include <string>
#include "pqxx/pqxx"
#include <iostream>
#include <json/json.h>
#include <fstream>
#include <openssl/evp.h>
#include <openssl/sha.h>
#include <algorithm>

namespace Reminder {
class Database {
 private:
  pqxx::connection connection;
  std::string connectionString;
  std::string usersTableName;
 public:
  Database() {
    parseConfigFile();
    this->connection = pqxx::connection(connectionString);
  }

  virtual ~Database() {
    connection.close();
  }

  static std::string hashPassword(const std::string &password);

  static bool comparePasswords(const std::string &password, const std::string &hashedPassword);

  void parseConfigFile();

  std::string addUser(const std::string &username, const std::string &password);

  std::string getPassword(const std::string &username);
};
}

#endif
