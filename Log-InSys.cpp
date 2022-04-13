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
        bool locked(true);
        if (db.doesUserExist(username)) {
            if (db.isPasswdValid(username)) {
                locked = false;
                db.setCurrUser(username);
            }
        }
        else {
            db.createUser(username);
            locked = false;
        }

        if (!locked) {
            int i(0);
            while (1) {
                if (i == 0) {
                    help();
                    i++;
                }
                parseopt(db);
            }
        }
    }
    catch (std::exception& e) {
        std::cout << e.what();
    }
    
    return 0;
}
