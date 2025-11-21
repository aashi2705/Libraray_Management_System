#include <iostream>
#include <conio.h>
#include <cstdlib>
#include <cstring>
using namespace std;

struct Book {
    char name[30];
    char author[30];
    int id;
    Book* next;
};

struct Student {
    char name[30];
    char email[20];
    char book[20];
    char author[30];
    int id;
    Student* next;
};

class LibrarySystem {
private:
    Book* start_lib;
    Student* start;

public:
    LibrarySystem() : start_lib(nullptr), start(nullptr) {
        initialize_lib();
    }

    ~LibrarySystem() {
        // Clean up memory
        Book* currentBook = start_lib;
        while (currentBook != nullptr) {
            Book* nextBook = currentBook->next;
            delete currentBook;
            currentBook = nextBook;
        }

        Student* currentStudent = start;
        while (currentStudent != nullptr) {
            Student* nextStudent = currentStudent->next;
            delete currentStudent;
            currentStudent = nextStudent;
        }
    }

    void initialize_lib() {
        Book* books[] = {
            new Book{"The Kite Runner", "Khaled Hosseini", 101, nullptr},
            new Book{"To Kill A Mockingbird", "Harper Lee", 102, nullptr},
            new Book{"The Alchemist", "Paulo Coelho", 103, nullptr},
            new Book{"Pride And Prejudice", "Jane Austen", 104, nullptr},
            new Book{"A Tale Of Two Cities", "Charles Dickens", 105, nullptr}
        };

        for (int i = 0; i < 4; i++) {
            books[i]->next = books[i + 1];
        }

        start_lib = books[0];
    }

    void greetings() {
        cout << "\n\n";
        cout << "\t\t\t     ****************************************\n";
        cout << "\t\t\t     *                                      *\n";
        cout << "\t\t\t     *                                      *\n";
        cout << "\t\t\t     *     ----------------------------     *\n";
        cout << "\t\t\t     *      WELCOME TO STUDENT LIBRARY      *\n";
        cout << "\t\t\t     *     ----------------------------     *\n";
        cout << "\t\t\t     *                                      *\n";
        cout << "\t\t\t     *                                      *\n";
        cout << "\t\t\t     ****************************************\n";
        cout << "\n\n";
        cout << "\t\t\t     ****************************************\n";
        cout << "\t\t\t     *                                      *\n";
        cout << "\t\t\t     *       ------------------------       *\n";
        cout << "\t\t\t     *           STUDENT LIBRARY            *\n";
        cout << "\t\t\t     *       ------------------------       *\n";
        cout << "\t\t\t     *                                      *\n";
        cout << "\t\t\t     *                                      *\n";
        cout << "\t\t\t     *       Chandigarh, India              *\n";
        cout << "\t\t\t     *     Email: studentlib@gmail.com      *\n";
        cout << "\t\t\t     *     Contact: 3456789102              *\n";
        cout << "\t\t\t     *                                      *\n";
        cout << "\t\t\t     ****************************************\n";
        cout << "\n\n\t\t\t             Press any key to continue: ";
        getch();
    }

    void main_menu() {
        int choice;
        do {
            system("cls");
            cout << "\n\n";
            cout << "\n\t\t\t*************************************************\n";
            cout << "\n\t\t\t\t      MAIN MENU: ";
            cout << "\n\t\t\t\t     1. ISSUE OF BOOKS ";
            cout << "\n\t\t\t\t     2. RETURN OF BOOKS ";
            cout << "\n\t\t\t\t     3. DISPLAY STUDENT DETAILS ";
            cout << "\n\t\t\t\t     4. DISPLAY AVAILABLE BOOKS ";
            cout << "\n\t\t\t\t     5. EXIT ";
            cout << "\n\t\t\t*************************************************\n";
            cout << "\n\t\t\t\t      Enter your choice: ";
            cin >> choice;

            switch (choice) {
                case 1:
                    book_issue();
                    break;
                case 2:
                    book_return();
                    break;
                case 3:
                    display_students();
                    break;
                case 4:
                    display_books();
                    break;
                case 5:
                    cout << "\n\t\t\t\t Thank you for using the Library System!\n";
                    break;
                default:
                    cout << "\n\t\t\t\t ...Invalid Option!...\n";
                    cout << "\n\t\t\t\t Press any key to try again: ";
                    getch();
            }
        } while (choice != 5);
    }

    void book_issue() {
        system("cls");
        if (start_lib == nullptr) {
            cout << "\n\t\t\t\t No books left in the library to issue!\n";
            cout << "\t\t\t\t Sorry for the inconvenience!\n";
            cout << "\n\t\t\t\t Press any key to continue: ";
            getch();
            return;
        }

        display_books();
        
        int id;
        cout << "\n\n\t Enter the Book ID: ";
        cin >> id;

        Book* ptr = start_lib;
        Book* prev = nullptr;
        
        while (ptr != nullptr && ptr->id != id) {
            prev = ptr;
            ptr = ptr->next;
        }

        if (ptr == nullptr) {
            cout << "\n\t\t ...Invalid Book ID!...\n";
            cout << "\n\t\t Press any key to try again: ";
            getch();
            return;
        }

        // Create new student
        Student* new_student = new Student;
        cout << "\n\t Enter Student Details:\n";
        cout << "\n\t Enter your Name: ";
        cin >> new_student->name;
        cout << "\n\t Enter your Email: ";
        cin >> new_student->email;
        strcpy(new_student->book, ptr->name);
        strcpy(new_student->author, ptr->author);
        new_student->id = ptr->id;
        new_student->next = nullptr;

        // Add student to list
        if (start == nullptr) {
            start = new_student;
        } else {
            Student* temp = start;
            while (temp->next != nullptr) {
                temp = temp->next;
            }
            temp->next = new_student;
        }

        // Remove book from library
        delete_book(id);

        cout << "\n\t Issue of Book ID " << new_student->id << " done successfully!\n";
        cout << "\n\n\t*************************************************\n";
        cout << "\n\n\t Press any key to go to the main menu: ";
        getch();
    }

    void book_return() {
        system("cls");
        if (start == nullptr) {
            cout << "\n\t\t\t No books have been issued yet!\n";
            cout << "\n\t\t\t Press any key to continue: ";
            getch();
            return;
        }

        int identity;
        cout << "\n\n\t*************** Books Submission: ****************\n";
        cout << "\n\n\t Enter your Book ID: ";
        cin >> identity;

        Student* ptr = start;
        Student* prev = nullptr;

        while (ptr != nullptr && ptr->id != identity) {
            prev = ptr;
            ptr = ptr->next;
        }

        if (ptr == nullptr) {
            cout << "\n\t Sorry the book doesn't exist! Please recheck the entered ID";
            cout << "\n\t\t\t\t Press any key to try again: ";
            getch();
            return;
        }

        // Display student details
        cout << "\n\t_________________________________________________\n";
        cout << "\n\t Student Name: " << ptr->name;
        cout << "\n\t Student Email: " << ptr->email;
        cout << "\n\t Name of Book Issued: " << ptr->book;
        cout << "\n\t_________________________________________________\n";

        // Return book to library
        add_book(ptr->book, ptr->author, ptr->id);

        // Remove student from list
        if (prev == nullptr) {
            start = ptr->next;
        } else {
            prev->next = ptr->next;
        }
        delete ptr;

        cout << "\n\n\t Return of Book ID " << identity << " done successfully!\n";
        cout << "\n\t Thank you! \n\t Do visit again! ";
        cout << "\n\n\t Press any key to go to the main menu: ";
        getch();
    }

    void display_students() {
        system("cls");
        if (start == nullptr) {
            cout << "\n\t\t\t No students have issued books yet!\n";
            cout << "\n\t\t\t Press any key to continue: ";
            getch();
            return;
        }

        Student* ptr = start;
        while (ptr != nullptr) {
            cout << "\n\t************* Details of Students: **************\n";
            cout << "\n\t_________________________________________________\n";
            cout << "\n\t\t Student Name: " << ptr->name;
            cout << "\n\t\t Student Email: " << ptr->email;
            cout << "\n\t\t Name of Book Issued: " << ptr->book;
            cout << "\n\t\t Book ID: " << ptr->id;
            cout << "\n\t_________________________________________________\n";
            cout << "\n\n\t*************************************************\n";
            ptr = ptr->next;
        }
        cout << "\n\n\t Press any key to go to the main menu: ";
        getch();
    }

    void display_books() {
        system("cls");
        if (start_lib == nullptr) {
            cout << "\n\t\t\t No books available in the library!\n";
            return;
        }

        Book* ptr = start_lib;
        int i = 1;
        cout << "\n\t*************** Books Available: ****************\n";
        while (ptr != nullptr) {
            cout << "\n\t_________________________________________________\n";
            cout << "\n\t Book " << i;
            cout << "\n\t Book Title: " << ptr->name;
            cout << "\n\t Name of Author: " << ptr->author;
            cout << "\n\t Book ID: " << ptr->id;
            cout << "\n\t_________________________________________________\n";
            ptr = ptr->next;
            i++;
        }
    }

private:
    void delete_book(int id) {
        Book* ptr = start_lib;
        Book* prev = nullptr;

        while (ptr != nullptr && ptr->id != id) {
            prev = ptr;
            ptr = ptr->next;
        }

        if (ptr == nullptr) return;

        if (prev == nullptr) {
            start_lib = ptr->next;
        } else {
            prev->next = ptr->next;
        }
        delete ptr;
    }

    void add_book(const char* bookname, const char* authorname, int id) {
        Book* new_book = new Book;
        strcpy(new_book->name, bookname);
        strcpy(new_book->author, authorname);
        new_book->id = id;
        new_book->next = nullptr;

        if (start_lib == nullptr) {
            start_lib = new_book;
        } else {
            Book* ptr = start_lib;
            while (ptr->next != nullptr) {
                ptr = ptr->next;
            }
            ptr->next = new_book;
        }
    }
};

int main() {
    LibrarySystem library;
    library.greetings();
    library.main_menu();
    return 0;
}