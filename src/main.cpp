#include <iostream>
#include "book_manager.h"
#include "user_manager.h"
using namespace std;
int main()
{
    BookManager bookManager;
    UserManager userManager;

    int choice;
    do{
    // system("cls"); // clear the console for each choice
     cout<<"\t\t\t\tLibrary Management System\n";
     cout<<"\t\t\t\t-------------------------\n";
     cout<<"\t\t\t\t1. Display all books      \n";
     cout<<"\t\t\t\t2. Add a book       \n";
     cout<<"\t\t\t\t3. Search for book          \n";
     cout<<"\t\t\t\t4. Borrow a book         \n";
     cout<<"\t\t\t\t5. Return Book       \n";
     cout<<"\t\t\t\t6. Register User       \n";
     cout<<"\t\t\t\t7. Show User Information       \n";
     cout<<"\t\t\t\t8. Exit               \n";
     cout<<"\t\t\t\t-------------------------\n";
     cout<<"\t\t\t\tEnter your choice: ";
     cin>>choice;
     switch(choice)
     {
       case 1:
       bookManager.displayBooks();
       break;
       case 2:
       bookManager.addBook();
       break;
       case 3:
       bookManager.searchBook();
       break;
       case 4:
       userManager.borrowBook(bookManager);
       break;
       case 5:
       userManager.returnBook(bookManager);
       break;
       case 6:
       userManager.registerUser();
       break;
       case 7:
       userManager.showUserInfo(bookManager);
       break;
       case 8:
       cout<<"Closing the app.....\n";
       break;
       default:
       cout<<"Please Choose a Option from above\n";
     }
    }while(choice!=8); // Changed the condition to exit the loop when choice is 8
    return 0;
}