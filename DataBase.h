#pragma once

#include <map>
#include <functional>
#include <utility>
//#include <string>

#include "User.h"

typedef std::map<std::string, std::string> Tstringmap;
typedef std::map<std::string, std::function<void()>> Tstring_functionMap;

class DataBase {
private:
    Tstringmap m_userPasswdMap;
    const Tstring_functionMap m_funcmap { {"chn", &changeUsername}};
    const std::string m_filename = "DataBase.txt";
    User m_currUser;
public:

    bool doesUserExist(const std::string& username);
    const std::string setPassword();
    void createUser(const std::string& username);
    bool isPasswdValid(const std::string& username, int quitID = 1);
    void setCurrUser(const std::string& username);
    const User getCurrUser() const { return m_currUser; }
    void read();
    void print() const;
    void changeUsername();
    void changePasswd();
    void deleteUser();
};

void help();
void quit();
//const char parseopt();