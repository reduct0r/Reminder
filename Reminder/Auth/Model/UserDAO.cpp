#include "UserDAO.h"

const std::string &UserDAO::GetUsername() const {
  return username;
}
void UserDAO::SetUsername(const std::string &username) {
  UserDAO::username = username;
}
const std::string &UserDAO::GetPassword() const {
  return password;
}
void UserDAO::SetPassword(const std::string &password) {
  UserDAO::password = password;
}
const std::string &UserDAO::GetSessionId() const {
  return sessionId;
}
void UserDAO::SetSessionId(const std::string &session_id) {
  sessionId = session_id;
}

UserDAO::UserDAO(const std::string &username, const std::string &password, const std::string &session_id) : username(
    username), password(password), sessionId(session_id) {}

UserDAO::UserDAO(const std::string &username, const std::string &password) : username(username), password(password) {}
UserDAO::UserDAO() {

}

bool UserDAO::isEmpty() {
  return (username == "" && password == "");
}