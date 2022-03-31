#pragma once

//#include <string>

class User {
    std::string name;
    std::string password;

public:

    void setUser(const std::string& username, const std::string& passwd) {
        name = username;
        password = passwd;
    }
    std::string getUsername() { return name; }
    std::string getUserPasswd() { return password; }
};