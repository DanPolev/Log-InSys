#include <iostream>
#include <fstream>
#include <sstream>
#include <utility>
#include <map>
#include <string>
#include <exception>
#include <iomanip>

#include "DataBase.h"

/*********************
* DataBase::DataBase
* ------------------
* DataBase constructor.
**********************/
DataBase::DataBase() {
    m_funcmap["chn"] = [this]() { changeUsername(); };
    m_funcmap["chp"] = [this]() { changePasswd(); };
    m_funcmap["duser"] = [this]() { deleteUser(); };
    m_funcmap["help"] = []() { help(); };
    m_funcmap["q"] = [this]() { quit(*this); };
}

/*************************
* DataBase::doesUserExist
* -----------------------
* Checks if user with the username
* exists.
* Returns true if user already exists.
* Otherwise - false.
**************************/
bool DataBase::doesUserExist(const std::string& username) const {
    bool doesKeyExist = m_userPasswdMap.count(username);
    if (!doesKeyExist) {
        return false;
    }
    else {
        return true;
    }
}
/*************************
* DataBase::setPassword
* ---------------------
* Gets the password from user's input.
* Returns the password to caller.
****************************/
const std::string DataBase::setPassword() {
    std::cout << "Enter password:";
    std::string password;
    std::cin >> password;
    return password;
}
/****************************
* DataBase::createUser
* --------------------
* Adds user to username-password map.
*****************************/
void DataBase::createUser(const std::string& username) {
    std::cout << "There is no account with such username.\n"
              << "Creating new account...\n";
    std::string password = setPassword();
    m_userPasswdMap.insert(std::make_pair(username, password));
    m_currUser.setUser(username, password);
    std::cout << username << "'s account created.\n";
}
/**************************
* DataBase::isPasswdValid
* -----------------------
* Checks password input from user
* with such username.
* Returns true if input password is correct.
* Otherwise, after "quitID" attempts return false.
******************************/
bool DataBase::isPasswdValid(const std::string& username, int quitID) {
    std::string password;
    do {
        password = setPassword();
        if (m_userPasswdMap[username] != password) {
            std::cout << "Incorrect password!\n";

            if (quitID >= 3) {
                std::cout << "Attempt limit is exceeded! Access denied!\n";
                return false;
            }

            std::cout << 3 - quitID;
            (3 - quitID > 1) ? std::cout << " attempts remain!\n" : std::cout << " attempt remains!\n";
            quitID++;

        }
        else {
            return true;
        }
    } while (m_userPasswdMap[username] != password);
}
/****************************
* DataBase::setCurrUser
* ---------------------
* Sets current user parameters
* from username-password map.
******************************/
void DataBase::setCurrUser(const std::string& username) {
    std::string password = m_userPasswdMap[username];
    m_currUser.setUser(username, password);
}
/************************************
* DataBase::read
* --------------
* Reads file with usernames and passwords.
* Makes username-password map from these data.
***************************************/
void DataBase::read() {
    std::ifstream inFile;
    inFile.open(m_filename, std::ios::in);

    if (!inFile.is_open()) {
        return;
    }

    std::string str;
    while (std::getline(inFile, str)) {
        if (str[0] == '#') continue;

        std::string username;
        std::string password;
        std::stringstream isstream(str);
        isstream >> username >> password;

        m_userPasswdMap.insert(std::make_pair(username, password));
    }
}
/***************************************
* DataBase::print
* ---------------
* Prints out username-password map to file.
****************************************/
void DataBase::print() const {
    std::ofstream outFile;

    outFile.open(m_filename, std::ios::out);
    if (!outFile.is_open()) {
        std::string errstr = "DataBase::print(): Cannot open " + m_filename + "file.\n";
        throw std::runtime_error(errstr);
    }

    outFile << "# Username        Password\n";
    const int columnWidth(16);
    for (const auto& elmt : m_userPasswdMap) {
        outFile << "  " << std::left << std::setw(columnWidth) << elmt.first << elmt.second << "\n";
    }
    std::cout << m_filename << " created.\n";
    outFile.close();
}
/*******************************
* DataBase::changeUsername
* ------------------------
* Changes username of current user.
* Checks if input username already exists.
* Updates username-password map.
*******************************/
void DataBase::changeUsername() {
    if (!isPasswdValid(m_currUser.getUsername())) {
        return;
    }
    std::cout << "Enter new username:";
    std::string newUsername;
    do {
        std::cin >> newUsername;
        if (doesUserExist(newUsername)) {
            std::cout << "There is already such username!\nEnter another one:\n";
        }
    } while (doesUserExist(newUsername));

    auto nodeHandler = m_userPasswdMap.extract(m_currUser.getUsername());    
    nodeHandler.key() = newUsername;
    m_userPasswdMap.insert(std::move(nodeHandler));
    m_currUser.setUser(newUsername, m_currUser.getUserPasswd());
    std::cout << "Your username's been changed.\n";
}
/**************************
* DataBase::changePasswd
* ----------------------
* Changes password of current user.
* Update username-password map.
**************************/
void DataBase::changePasswd() {
    if (!isPasswdValid(m_currUser.getUsername())) {
        return;
    }

    std::cout << "Enter new password:";
    std::string newPassword;
    std::cin >> newPassword;

    m_userPasswdMap[m_currUser.getUsername()] = newPassword;
    std::cout << m_currUser.getUsername() << "'s password's been changed.\n";
}
/****************************
* DataBase::deleteUser
* --------------------
* Deletes current user's data from
* username-password map.
* Then quits the program.
*****************************/
void DataBase::deleteUser() {
    if (!isPasswdValid(m_currUser.getUsername(), 3)) {
        return;
    }
    std::cout << "CAUTION: You are going to delete your data from database!\n";
    std::cout << "Are you sure?(y/n):";
    char answer;
    std::cin >> answer;
    if (answer == 'n') return;

    m_userPasswdMap.erase(m_currUser.getUsername());
    std::cout << "User " << m_currUser.getUsername() << " deleted.\n";
    quit(*this);
}
/**************************************
* quit
* ----
* Quits program by throwing exception.
**************************************/
void quit(DataBase& db) {
    db.print();
    throw std::runtime_error("Quit function've called. Shutdown the program...\n");
}
/******************************
* help
* ----
* Prints possible operations with database
* to current user.
********************************/
void help() {
    std::cout << "---------------------------------\n"
        << "List of operations with database:\n"
        << "  chn  - change current user's username;\n"
        << "  chp  - change current user's password;\n"
        << "  duser - delete current user;\n"
        << "  help - call help;\n"
        << "  q    - quit the program.\n";
}
/*****************************************
* parseopt
* --------
* Gets option from user as string
* and call corresponding function
* from function_name-function_pointer map.
******************************************/
void parseopt(const DataBase& db) {
    std::cout << ":";
    std::string opt;
    std::cin >> opt;
    bool correctOpt = db.hasOperation(opt);
    map_constIterator it_func;
    if (!correctOpt) {
        it_func = db.getfunc("help");
    } else {
        it_func = db.getfunc(opt);
    }
    it_func->second();
}
