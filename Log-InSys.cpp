/* A simple log-in/registration system.
 * Saves username and password to the database file.
 * Lets user perform simple operations with database:
 * - change username;
 * - change password;
 * - delete own account from database file.
*/
#include <iostream>
#include <string>
#include <exception>

#include "DataBase.h"

int main()
{
    DataBase db;
    try {
        db.read();

        std::cout << "Enter username:";
        std::string username;
        std::cin >> username;
        bool isAuthorized(false);
        if (db.doesUserExist(username)) {
            if (db.isPasswdValid(username)) {
                isAuthorized = true;
                db.setCurrUser(username);
            }
        }
        else {
            db.createUser(username);
            isAuthorized = true;
        }

        if (isAuthorized) {
            inputHandle(db);
        }
    }
    catch (std::exception& e) {
        std::cout << e.what();
    }
    
    return 0;
}
