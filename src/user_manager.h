#ifndef USER_MANAGER_H
#define USER_MANAGER_H

#include <iostream>
#include "book_manager.h"
#include "json_handler.h"

class UserManager {
private:
    

public:
    nlohmann::json users = JsonHandler::loadJson("data/users.json");;
    void loadUsers();
    void borrowBook(BookManager& bookManager);
    void returnBook(BookManager& bookManager);
    void registerUser();
    void showUserInfo(BookManager& bookManager);
};

#endif
