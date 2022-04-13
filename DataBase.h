#pragma once

#include <map>
#include <functional>
#include <utility>
#include <string>

#include "User.h"

typedef std::map<std::string, std::function<void()>>::const_iterator map_constIterator;

class DataBase {
private:
    std::map<std::string, std::string> m_userPasswdMap;         // username - password map
    std::map < std::string, std::function<void()> > m_funcmap;  // function_name - function_pointer map
    const std::string m_filename = "DataBase.txt";
    User m_currUser;                                            // current user structure
public:

    DataBase();
    bool doesUserExist(const std::string& username) const;
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
    bool hasOperation(const std::string& operation) const // checks if given operation exists
        { return m_funcmap.count(operation); } 
    map_constIterator getfunc(const std::string& opt) const // provides function pointer from function name
        { return m_funcmap.find(opt); }      
};
void help();
void quit(DataBase& db);
void parseopt(const DataBase& db);
