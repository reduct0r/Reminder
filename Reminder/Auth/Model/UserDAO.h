#ifndef REMINDER_REMINDER_MODEL_USERDAO_H_
#define REMINDER_REMINDER_MODEL_USERDAO_H_

#include <string>
#include <iostream>

class UserDAO {
 private:
  std::string username;
  std::string password;
  std::string sessionId;
 public:

  UserDAO(const std::string &username, const std::string &password, const std::string &session_id);

  UserDAO(const std::string &username, const std::string &password);

  UserDAO();

  const std::string &GetUsername() const;

  void SetUsername(const std::string &username);

  const std::string &GetPassword() const;

  void SetPassword(const std::string &password);

  const std::string &GetSessionId() const;

  void SetSessionId(const std::string &session_id);

  bool isEmpty();

};

#endif //REMINDER_REMINDER_MODEL_USERDAO_H_
