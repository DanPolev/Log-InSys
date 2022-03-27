#pragma once

#include <map>
#include <string>

class DataBase {
private:
    // TODO: add m_id here
    std::map<std::string, std::string> m_userPasswdMap;
    const std::string m_filename = "DataBase.txt";
public:

    bool isUserCreated(const std::string& username) const;
    std::string setPassword();
    void createUser(const std::string& username);
    bool isPasswdValid(std::string& username);
    void read();
    void print() const;
    //void deleteUser();
    //void changeUsername();
    //void changePasswd();
};

