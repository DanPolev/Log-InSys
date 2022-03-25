/* Trivial log-in/registration system.
*  Write input username and password to file.
*/
#include <Windows.h>
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <utility>
#include <exception>
#include <iomanip>  // for setw() func


class DataBase {
private:
    // TODO: add m_id here
    std::map<std::string, std::string> m_userPasswdMap;
public:

    bool isUserCreated(const std::string& username) const;
    void createUser(const std::string& username);
    void print() const;
    void update();
};

bool DataBase::isUserCreated(const std::string& username) const {
    auto search = m_userPasswdMap.find(username);
    if (search == m_userPasswdMap.end()) {
        return false;
    } else {
        return true;
    }
}

void DataBase::createUser(const std::string& username) {
    std::string password;
    std::cout << "Enter password:";
    std::cin >> password;
    m_userPasswdMap.insert(std::make_pair(username, password));
    std::cout << username << "'s account created.\n";
}

void DataBase::print() const{
    std::ofstream outFile("DataBase.txt");
    if (!outFile.is_open()) {
        throw std::runtime_error("DataBase::print(): Cannont open DataBase.txt file.");
    }

    std::setiosflags(std::ios::left);
    const int columnWidth(10);
    outFile << "# Username  Password\n";
    for (const auto& elmt : m_userPasswdMap) {
        outFile << "  " << elmt.first << std::setw(columnWidth) << elmt.second << "\n";
    }
    outFile.close();
}

int main()
{
    DataBase db;
    try {
        std::cout << "Enter username:";
        std::string username;
        std::cin >> username;
        if (db.isUserCreated(username)) {

        }
        else {
            std::cout << "There is no account with such username.\n";
            std::cout << "Creating new account...\n";
            db.createUser(username);
        }
        db.print();
    }
    catch (std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        exit(1);
    }
    
    return 0;
}
