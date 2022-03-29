#include <iostream>
#include <fstream>
#include <sstream>
#include <utility>
#include <exception>
#include <iomanip>  // for setw() func

#include "DataBase.h"

bool DataBase::isUserCreated(const std::string& username) {
    auto search = m_userPasswdMap.find(username);
    if (search == m_userPasswdMap.end()) {
        return false;
    }
    else {
        return true;
    }
}

std::string DataBase::setPassword() {
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
bool DataBase::isPasswdValid(std::string& username) {
    std::string password;
    int quitID(1);
    do {
        password = setPassword();
        if (m_userPasswdMap[username] != password) {
            std::cout << "Incorrect password!\n";

            if (quitID >= 3) {
                std::cout << "Attempt limit is exceeded! Shutdown program...\n";
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
        std::string errstr = "DataBase::print(): Cannot open " + m_filename + "file.";
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
