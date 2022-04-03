#pragma once

#include <map>
#include <functional>
#include <utility>
#include <string>

#include "User.h"

typedef std::map<std::string, std::function<void()>>::const_iterator map_constIterator;

class DataBase {
private:
    std::map<std::string, std::string> m_userPasswdMap;
    std::map < std::string, std::function<void()> > m_funcmap; // TODO: how to make it static???
    const std::string m_filename = "DataBase.txt";
    User m_currUser;
public:

    DataBase();
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
    map_constIterator getfunc(const std::string& opt) const { return m_funcmap.find(opt); }
    void quit(); // TODO: Make class-exception to throw SUCCESS_EXIT and then print map
};
void help();
//void quit();
void parseopt(const DataBase& db);
