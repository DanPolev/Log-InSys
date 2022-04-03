/* A simple log-in/registration system.
*  Write input username and password to file.
*/
#include <iostream>
#include <string>
#include <exception>

#include "DataBase.h"

// Usage example: filePutContents("./yourfile.txt", "content", true);
/*void filePutContents(const std::string& name, const std::string& content, bool append = false) {
    std::ofstream outfile;
    if (append)
        outfile.open(name, std::ios_base::app);
    else
        outfile.open(name);
    outfile << content;
}*/

int main()
{
    DataBase db;
    try {
        db.read();

        std::cout << "Enter username:";
        std::string username;
        std::cin >> username;
        if (db.doesUserExist(username)) {
            if (db.isPasswdValid(username)) {
                db.setCurrUser(username);
            }
        }
        else {
            db.createUser(username);
        }
        int i(0);
        while(1) {
            if (i == 0) {
                help();
                i++;
            }
            parseopt(db);
        }
    }
    catch (std::exception& e) {
        std::cout << e.what();
        return 0;
    }
    
    return 0;
}
