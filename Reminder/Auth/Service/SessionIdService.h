#ifndef REMINDER_REMINDER_SERVICE_SESSIONIDSERVICE_H_
#define REMINDER_REMINDER_SERVICE_SESSIONIDSERVICE_H_

#include <string>
#include <iostream>
#include <openssl/rand.h>
#include <sstream>
#include <iomanip>
#include <fstream>
#include <sys/stat.h>
#include <cerrno>

class SessionIdService {
 public:

  static bool compareTo(const std::string &dbToken, const std::string &userToken) {
    return dbToken == userToken;
  }

  static std::string generateRandomKey() {
    int const key_length = 16;
    unsigned char key[key_length];

    if (RAND_bytes(key, key_length) != 1) {
      return "";
    }

    std::stringstream sessionIdToken;
    sessionIdToken << std::hex << std::setfill('0');
    for (int i = 0; i < key_length; ++i) {
      sessionIdToken << std::setw(2) << static_cast<int>(key[i]);
    }

    return sessionIdToken.str();
  }

  static std::string readSessionId() {
    std::ifstream file("Config/sessionId.txt");
    std::string data;

    if (file.is_open()) {
      std::getline(file, data);
      file.close();
    }

    return data;
  }

  static bool deleteSessionId() {
    std::ofstream file
        ("Config/sessionId.txt", std::ofstream::out | std::ofstream::trunc);

    if (!file.is_open()) {
      return false;
    }
    file.close();

    return true;
  }

  static bool saveNewSessionId(const std::string &data) {
    std::string filename = "Config/sessionId.txt";
    std::ofstream file(filename, std::ofstream::out | std::ofstream::trunc);

    if (!file.is_open()) {
      return false;
    }

    file.clear();
    file << data;
    file.close();

    return true;
  }
};

#endif //REMINDER_REMINDER_SERVICE_SESSIONIDSERVICE_H_
