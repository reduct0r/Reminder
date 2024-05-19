#ifndef REMINDER_REMINDER_DATABASE_DATABASE_H_
#define REMINDER_REMINDER_DATABASE_DATABASE_H_

#include "pqxx/pqxx"
#include <json/json.h>
#include <fstream>
#include <openssl/sha.h>
#include <algorithm>
#include "Model/UserDAO.h"
#include "Service/SessionIdService.h"
#include "../Game/GameProcess.h"

namespace Reminder {
class Database {
 private:
  pqxx::connection connection;
  std::string usersTableName;
 public:

  Database() : connection(parseConfigFile()) {
    parseConfigFile();
  }

  virtual ~Database() {
    connection.close();
  }

  std::string hashPassword(const std::string &password);

  bool comparePasswords(const std::string &password, const std::string &hashedPassword);

  std::string parseConfigFile();

  UserDAO createUser(const std::string &username, const std::string &password);

  UserDAO getUser(UserDAO &user);

  UserDAO containsSessionId(const std::string &sessionIdToken);

  std::vector<CardPreset> getUserPresets(UserDAO &user);

  bool deleteUserPreset(const std::string &presetName, UserDAO &user);

  bool addUserPreset(CardPreset &newCardPreset, UserDAO &user);
};
}

#endif
