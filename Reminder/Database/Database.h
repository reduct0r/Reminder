#ifndef REMINDER_REMINDER_DATABASE_DATABASE_H_
#define REMINDER_REMINDER_DATABASE_DATABASE_H_

#include <string>
#include "pqxx/pqxx"
#include <iostream>
#include <json/json.h>
#include <fstream>

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

  void parseConfigFile();

  std::string addUser(const std::string &username, const std::string &password);

  std::string getPassword(const std::string &name);
};
}

#endif
