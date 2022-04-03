#pragma once

#include <map>
#include <functional>
#include <utility>
#include <string>

#include "User.h"

class DataBase {
private:
    std::map<std::string, std::string> m_userPasswdMap;
    static std::map < std::string, std::function<void()> > m_funcmap;
    const std::string m_filename = "DataBase.txt";
    User m_currUser;
public:

    DataBase() {
        m_funcmap.emplace(std::make_pair("chn", &changeUsername));
        m_funcmap.emplace(std::make_pair("chp", &changePasswd));
        m_funcmap.emplace(std::make_pair("duser", &deleteUser));
        m_funcmap.emplace(std::make_pair("q", &quit));
    }

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