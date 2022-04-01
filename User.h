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
    const std::string getUsername() const { return name; }
    const std::string getUserPasswd() const { return password; }
};