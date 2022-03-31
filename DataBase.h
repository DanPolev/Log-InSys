#pragma once

#include <map>
//#include <string>

#include "User.h"

class DataBase {
private:
    // TODO: add m_id here
    std::map<std::string, std::string> m_userPasswdMap;
    const std::string m_filename = "DataBase.txt";
    User m_currUser;
public:

    bool isUserCreated(const std::string& username);
    std::string setPassword();
    void createUser(const std::string& username);
    bool isPasswdValid(std::string& username);
    void setCurrUser(const std::string& username);
    User getCurrUser() { return m_currUser; }
    void read();
    void print() const;
    //void deleteUser();
    //void changeUsername();
    //void changePasswd();
};

