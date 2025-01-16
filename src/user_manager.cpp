#include "user_manager.h"
#include "json_handler.h"
#include <chrono>
#include <ctime>
using namespace std;
#include "../include/nlohmann/json.hpp" 

void UserManager::loadUsers()  //loads the user data from the json file
{
    users = JsonHandler::loadJson("data/users.json");
}

void UserManager::borrowBook(BookManager& bookManager) {
    string userId, isbn;

    // Validate user ID input
    do {
        cout << "Student ID: ";
        cin >> userId;
        if (userId.empty()) {
            cout << "Student ID cannot be empty. Please enter the ID again.\n";
        }
    } while (userId.empty());

    // Validate ISBN input
    do {
        cout << "ISBN: ";
        cin >> isbn;
        if (isbn.empty()) {
            cout << "ISBN cannot be empty. Please enter the ISBN again.\n";
        }
    } while (isbn.empty());

    // Check if the user exists in the 'users' JSON
    if (users.contains(userId)) {
        if (!users[userId].is_object()) {
            cout << "Error: The user data is corrupted or of incorrect type.\n";
            return;
        }
        cout << "User " << userId << " found in the system.\n";  // Debugging line
    } else {
        cout << "User not found: " << userId << endl;  // Debugging line
        return;
    }

    // Check if the book exists in the 'books' JSON
    if (bookManager.books.contains(isbn)) {
        if (!bookManager.books[isbn].is_object()) {
            cout << "Error: The book data is corrupted or of incorrect type.\n";
            return;
        }
    } else {
        cout << "Book not found: " << isbn << endl;  // Debugging line
        return;
    }

    // Check if the user already borrowed the book
    if (users[userId].contains("borrowed_books")) {
        if (users[userId]["borrowed_books"].contains(isbn)) {
            cout << "You have already borrowed this book.\n";
            return;
        }
    }

    // Check if the book is available for borrowing
    if (bookManager.books[isbn]["quantity"].get<int>() > 0) {
        // Add the book to the user's borrowed books
        users[userId]["borrowed_books"].push_back(isbn);

        // Decrease the quantity of the book
        bookManager.books[isbn]["quantity"] = bookManager.books[isbn]["quantity"].get<int>() - 1;

        // Save the updated data
        JsonHandler::saveJson("data/books.json", bookManager.books);
        JsonHandler::saveJson("data/users.json", users);

        cout << "Book borrowed successfully.\n";
    } else {
        cout << "Sorry, the book is out of stock.\n";
    }
}

void UserManager::returnBook(BookManager& bookManager){  //pass by reference
    string userId,isbn;
    do {
        cout<<"Student ID: ";
        cin>>userId;
        if(userId.empty()) {
            cout<<"Student ID cannot be empty. Please enter the ID again.\n";
        }
    } while(userId.empty());

    do {
        cout<<"ISBN: ";
        cin>>isbn;
        if(isbn.empty()) {
            cout<<"ISBN cannot be empty. Please enter the ISBN again.\n";
        }
    } while(isbn.empty());
    if(users.contains(userId) && bookManager.books.contains(isbn)){
        if(users[userId].contains("borrowed_books")){
            if(users[userId]["borrowed_books"].contains(isbn)){
                users[userId]["borrowed_books"].erase(std::remove(users[userId]["borrowed_books"].begin(), users[userId]["borrowed_books"].end(), isbn), users[userId]["borrowed_books"].end());
                bookManager.books[isbn]["quantity"]=bookManager.books[isbn]["quantity"].get<int>()+1;
                JsonHandler::saveJson(bookManager.books,"data/books.json");
                JsonHandler::saveJson(users,"data/users.json");
                cout<<"Book returned successfully.\n";
            }else{
                cout<<"You have not borrowed this book.\n";
            }
        }else{
            cout<<"You have not borrowed this book.\n";
        }
    }else{
        cout<<"Invalid Student ID or ISBN.\n";
    }
}

void UserManager::registerUser() {
    string userId, name;
    cout << "Enter the Student ID: ";
    cin >> userId;

    // Check if the user already exists and if the data is in the correct format
    if (users.contains(userId)) {
        if (!users[userId].is_object()) {
            cout << "Error: The existing entry for this Student ID is corrupted or of incorrect type.\n";
            return;
        }
        cout << "User already exists.\n";
        return;
    }

    cout << "Enter the Name: ";
    cin.ignore();  // Ignore the newline character
    getline(cin, name);
    if (name.empty()) {
        cout << "Name cannot be empty. Please enter the name again: ";
        getline(cin, name);
    }

    // Initialize the new user
    users[userId] = {
        {"name", name},
        {"borrowed_books", nlohmann::json::array()}  // Initialize as an empty array
    };

    JsonHandler::saveJson("data/users.json", users);
    cout << "User registered successfully. Welcome to Library management system.\n";
}

void UserManager::showUserInfo(BookManager& bookManager) {
    string userId;
    cout << "Enter the Student ID: ";
    cin >> userId;

    // Check if the user exists
    if (users.contains(userId)) {
        cout << "Student ID: " << userId << "\n";
        cout << "Name: " << users[userId]["name"] << "\n";

        // Check if the 'borrowed_books' field exists and is an array
        if (users[userId].contains("borrowed_books") && users[userId]["borrowed_books"].is_array()) {
            cout << "Borrowed Books: \n";

            // Iterate through the borrowed books
            for (auto& isbn : users[userId]["borrowed_books"]) {
                if (isbn.is_string()) {
                    cout << isbn.get<string>() << "\n"; // Print the ISBN
                    if (bookManager.books.contains(isbn.get<string>())) {
                        const auto& book = bookManager.books[isbn.get<string>()];
                        cout << "Title: " << book["title"] << "\n"
                             << "Author: " << book["author"] << "\n"
                             << "Publisher: " << book["publisher"] << "\n";
                        
                        // Optional: Print the due date if it exists
                        if (users[userId].contains("due_date") && users[userId]["due_date"].is_number()) {
                            std::time_t due_date = users[userId]["due_date"].get<std::time_t>();
                            cout << "Due Date: " << std::ctime(&due_date) << "\n";
                        }
                    }
                } else {
                    cout << "Error: Invalid data in borrowed_books.\n";
                }
            }
        } else {
            cout << "No books borrowed.\n";
        }
    } else {
        cout << "Invalid Student ID.\n";
    }
}


