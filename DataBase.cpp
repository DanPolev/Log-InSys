#include <iostream>
#include <fstream>
#include <sstream>
#include <utility>
#include <map>
#include <string>
#include <exception>
#include <iomanip>  // for setw() func

#include "DataBase.h"

bool DataBase::doesUserExist(const std::string& username) {
    bool doesKeyExist = m_userPasswdMap.count(username);
    if (!doesKeyExist) {
        return false;
    }
    else {
        return true;
    }
}

const std::string DataBase::setPassword() {
    std::cout << "Enter password:";
    std::string password;
    std::cin >> password;
    return password;
}

void DataBase::createUser(const std::string& username) {
    std::cout << "There is no account with such username.\n"
              << "Creating new account...\n";
    std::string password = setPassword();
    m_userPasswdMap.insert(std::make_pair(username, password));
    m_currUser.setUser(username, password);
    std::cout << username << "'s account created.\n";
}

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
            m_currUser.setUser(username, password);
            return true;
        }
    } while (m_userPasswdMap[username] != password);
}

void DataBase::setCurrUser(const std::string& username) {
    std::string password = m_userPasswdMap[username];
    m_currUser.setUser(username, password);
}

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
<<<<<<< HEAD
=======

void DataBase::changeUsername() {
    if (!isPasswdValid(m_currUser.getUsername(), 3)) {
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
}

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
    print();
    quit();
}

void help() {
    std::cout << "List of operations with database:\n"
              << "  chn  - change current user's username;\n"
              << "  chp  - change current user's password;\n"
              << "  dusr - delete current user;\n"
              << "  q    - quit the program.\n";
}

void quit() {
    throw std::runtime_error("Quit function've called. Shutdown the program...\n");
}

/*const char parseopt() {
    std::cout << ":";
    std::string opt;
    std::cin >> opt;

}*/
>>>>>>> 78a39dc (- rename isUserCreated() into doesUserExist() with little corrections;)
