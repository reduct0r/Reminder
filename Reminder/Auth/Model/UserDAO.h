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

  const std::string &getUsername() const;

  void setUsername(const std::string &username);

  const std::string &getPassword() const;

  void setPassword(const std::string &password);

  const std::string &getSessionId() const;

  void setSessionId(const std::string &session_id);

  bool isEmpty();

};

#endif //REMINDER_REMINDER_MODEL_USERDAO_H_
