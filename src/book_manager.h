#ifndef BOOK_MANAGER_H
#define BOOK_MANAGER_H

#include "json_handler.h"
#include <iostream>
using namespace std;

class BookManager
{
public:
    nlohmann::json books = JsonHandler::loadJson("data/books.json");;
    void loadBooks();
    void displayBooks();
    void addBook();
    void searchBook();
};
#endif