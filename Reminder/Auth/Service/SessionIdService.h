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

  static bool saveStringToLocal(const std::string &data) {
    if (!createDirectory("local")) {
      return false;
    }

    return saveStringToFile("local/session.txt", data);
  }

  static std::string readStringFromLocal() {
    std::ifstream file("local/session.txt");
    std::string data;

    if (file.is_open()) {
      std::getline(file, data);
      file.close();
    }

    return data;
  }

 private:
  static bool createDirectory(const std::string &path) {
    //int status = mkdir(path.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    return 1;
  }

  static bool saveStringToFile(const std::string &filename, const std::string &data) {
    std::ofstream file(filename);
    if (!file.is_open()) {
      return false;
    }

    file << data;
    file.close();

    return true;
  }

};

#endif //REMINDER_REMINDER_SERVICE_SESSIONIDSERVICE_H_
