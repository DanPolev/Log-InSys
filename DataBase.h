#pragma once

#include <map>
#include <functional>
//#include <string>

#include "User.h"

class DataBase {
private:
    // TODO: add m_id here
    std::map<std::string, std::string> m_userPasswdMap;
    std::map<std::string, std::function<void()>> m_funcmap;
    const std::string m_filename = "DataBase.txt";
    User m_currUser;
public:

    bool doesUserExist(const std::string& username);
    const std::string setPassword();
    void createUser(const std::string& username);
    bool isPasswdValid(const std::string& username, int quitID = 1);
    void setCurrUser(const std::string& username);
    const User getCurrUser() { return m_currUser; }
    void read();
    void print() const;
    void changeUsername();
    //void changePasswd();
    //void deleteUser();
};

void help();
//const char parseopt();