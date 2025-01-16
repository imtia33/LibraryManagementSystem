#include "book_manager.h"
#include "json_handler.h"
using namespace std;
#include "../include/nlohmann/json.hpp" 

void BookManager::loadBooks()  //loads the books from the json file
{
    books = JsonHandler::loadJson("data/books.json");
}


void BookManager::displayBooks() {
    for (const auto& doc : books.items()) {    
        const auto& isbn = doc.key();
        const auto& book = doc.value();

        std::cout << "ISBN: " << isbn << "\n"
                  << "Title: " << book["title"] << "\n"
                  << "Author: " << book["author"] << "\n"
                  << "Publisher: " << book["publisher"] << "\n"
                  << "Quantity: " << book["quantity"] << "\n\n";
    }
}

void BookManager::addBook(){
    string isbn,title,author,publisher;
    int quantity;
    cout<<"Enter the ISBN: ";
    cin>>isbn;
    cout<<"Title: ";
    cin.ignore();  // ignore the newline character
    cin>>title;
    if(title.empty()){
        cout<<"Title cannot be empty. Please enter the title again: ";
        cin>>title;
    }
    cout<<"Author: ";
    cin>>author;
    if(author.empty()){
        cout<<"Author cannot be empty. Please enter the author again: ";
        cin>>author;
    }
    cout<<"Publisher: ";
    cin>>publisher;
    if(publisher.empty()){
        cout<<"Publisher cannot be empty. Please enter the publisher again: ";
        cin>>publisher;
    }
    cout<<"Quantity: ";
    cin >> quantity;
    if (!(quantity)) { // to handle invalid input
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    quantity = 1;
   }
   if (books.contains(isbn)) {
    if (books[isbn].is_object()) {
        // Increment quantity if the book exists
        books[isbn]["quantity"] = books[isbn]["quantity"].get<int>() + 1;
        JsonHandler::saveJson("data/books.json", books);
        cout << "Book added to the collection" << endl;
    } else {
        cout << "Error: The existing entry for this ISBN is not an object." << endl;
    }
} else {
    // Add new book
    books[isbn] = {
        {"title", title},
        {"author", author},
        {"publisher", publisher},
        {"quantity", quantity}
    };
    JsonHandler::saveJson("data/books.json", books);
    cout << "Book added to the collection" << endl;
}

}

void BookManager::searchBook(){
    string searchQuery;
    //books = JsonHandler::loadJson("data/books.json");
    cout << "Enter the search query (ISBN, Title, Author, Publisher): ";  //searches the book based on the search query
    cin.ignore();  // ignore the newline character
    getline(cin, searchQuery);
    bool found = false;

    for (const auto& doc : books.items()) {

        const auto& book = doc.value();
       // cout << book.dump() << endl;
        // Check if the search query matches the ISBN or any of the book details
        if (doc.key() == searchQuery || 
            (book.contains("title") && book["title"].get<string>() == searchQuery) || 
            (book.contains("author") && book["author"].get<string>() == searchQuery) || 
            (book.contains("publisher") && book["publisher"].get<string>() == searchQuery)) {
            std::cout << "ISBN: " << doc.key() << "\n"
                      << "Title: " << book["title"] << "\n"
                      << "Author: " << book["author"] << "\n"
                      << "Publisher: " << book["publisher"] << "\n"
                      << "Quantity: " << book["quantity"] << "\n\n";
            found = true;
        }
    }
    if (!found) {
        cout << "No books found matching the search query." << endl;
    }
}