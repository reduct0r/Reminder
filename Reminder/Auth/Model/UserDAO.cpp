#include "UserDAO.h"

const std::string &UserDAO::getUsername() const {
  return username;
}
void UserDAO::setUsername(const std::string &username) {
  UserDAO::username = username;
}
const std::string &UserDAO::getPassword() const {
  return password;
}
void UserDAO::setPassword(const std::string &password) {
  UserDAO::password = password;
}
const std::string &UserDAO::getSessionId() const {
  return sessionId;
}
void UserDAO::setSessionId(const std::string &session_id) {
  sessionId = session_id;
}

UserDAO::UserDAO(const std::string &username, const std::string &password, const std::string &session_id) : username(
    username), password(password), sessionId(session_id) {}

UserDAO::UserDAO(const std::string &username, const std::string &password) : username(username), password(password) {}

UserDAO::UserDAO() {}

bool UserDAO::isEmpty() {
  return (username == "" && password == "");
}