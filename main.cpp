#include <iostream>
#include <fstream>
#include <conio.h>
#include <string.h>

using namespace std;

class Lib{

    public:

        void menu();//done
        void student();//done
        void librarian();//done
        void viewBooks();//done
        void issue_Return();
        void addBook();//done
        void removeBook();//done

};

class book{

    public:
        char name[50];
        char author[50];

        void newBook();
        void displayBook();
        int isPresent(char* x);
        void bookName();

};



int main(){

    Lib lib0;
    lib0.menu();
    getch();
    return 0;

}

void Lib::menu(){

    while(true){
        int ch = -1;
        system("cls");
        cout<<"Library Management\n\n1. Student\n2. Librarian\n3. Exit\n\nEnter Choice: ";
        while(ch < 1 || ch > 3){

            cin>>ch;
            if(ch < 1 || ch > 3)
                cout<<"Invalid Option...\nEnter Choice:";

        }

        if(ch == 1)
            student();
        if(ch == 2)
            librarian();
        if(ch == 3)
            return;
    }
}

void Lib::student(){
    while(true){
        int ch = -1;
        system("cls");
        cout<<"Welcome Student\n\n1. View Available Books\n2. Issue/Return a Book\n3. Previous Menu\n\nEnter Choice:";
        while(ch < 1 || ch > 3){

            cin>>ch;
            if(ch < 1 || ch > 3)
                cout<<"Invalid Option...\nEnter Choice:";

        }
        if(ch == 1)
            viewBooks();

        if(ch == 2)
            issue_Return();

        if(ch == 3)
            return;
    }
}

void Lib::librarian(){

    while(true){

        int ch = -1;
        system("cls");
        cout<<"Welcome Librarian\n\n1. View Available Books\n2. Add Book\n3. Remove Book\n4. Previous Menu\n\nEnter Choice: ";
        while(ch < 1 || ch > 4){

            cin>>ch;
            if(ch < 1 || ch > 4)
                cout<<"Invalid Option...\nEnter Choice:";

        }

        if(ch == 1)
            viewBooks();
        //cout<<"check";
        if(ch == 2)
            addBook();

        if(ch == 3)
            removeBook();

        if(ch == 4)
            return;

    }

}

void Lib::addBook(){

    system("cls");

    fstream num;
    num.open("num.txt", ios::in);
    int n;
    num >> n;
    num.close();

    book temp;
    fstream books;
    books.open("books.txt", ios::app);
    temp.newBook();
    books.write((char*)&temp,sizeof(temp));
    books.close();

    n++;
    num.open("num.txt", ios::out);
    num << n;
    num.close();

}

void Lib::removeBook(){

    system("cls");

    fstream num;
    num.open("num.txt", ios::in);
    int n;
    num >> n;
    num.close();

    if(n == 0){

        cout<<"No Books in Library\nPress any key to return to previous menu...";
        getch();
        return;

    }

    int del = 0;

    book tBook;
    char bName[50];
    fstream books;
    fstream temp;
    books.open("books.txt", ios::in);
    temp.open("temp.txt", ios::out);

    char ch;
    cin.get(ch);
    cout<<"Enter Name of Book to Delete: ";
    cin.getline(bName,50);
    int i;

    for(i = 0; i < n; i++){
        books.read((char*)&tBook,sizeof(tBook));
        if(tBook.isPresent(bName)){
            del = 1;
            break;
        }
        del = 0;
    }

    if(del == 0){

        cout<<"Book Not Found.\nPress any key to return to previous menu...";
        books.close();
        temp.close();
        getch();
        return;
    }

    books.seekg(0);
    if(del == 1){
        if(n != 1){
            for(int j = 0; j < n; j++){
                books.read((char*)&tBook,sizeof(tBook));
                if(j != i)
                    temp.write((char*)&tBook,sizeof(tBook));
            }
        }

        n--;
        num.open("num.txt", ios::out);
        num << n;
        num.close();
    }

    books.close();
    temp.close();

    remove("books.txt");
    rename("temp.txt","books.txt");
    cout<<"Book Removed\nPress any key to return to previous menu...";
    getch();
    return;

}

void Lib::viewBooks(){

    system("cls");
    fstream num;
    num.open("num.txt", ios::in);
    int n;
    num >> n;
    num.close();

    if(!n){

        cout<<"No Books in Library\nPress any key to return to previous menu...";
        getch();
        return;

    }

    book temp;
    fstream books;
    books.open("books.txt", ios::in);

    for(int i =0;i < n; i++){
        cout<<"---------- "<<(i+1)<<" ----------\n\n";
        books.read((char*)&temp,sizeof(temp));
        temp.displayBook();


    }

    cout<<"\nPress any key to return to previous menu...";
    getch();
    books.close();


}

void Lib::issue_Return(){

    system("cls");
    int allowIssue = 1;
    char ch;
    char sName[50];
    cin.get(ch);
    cout<<"Enter Student Name: ";
    cin.getline(sName,50);

    char* fileName = sName;
    strcat(fileName,".txt");

    fstream stu;
    stu.open(fileName, ios::in);
    if(stu)
    {

        allowIssue = 0;
        book temp;
        stu.read((char*)&temp,sizeof(temp));
        temp.bookName();
        cout<<" has already been issued to this name.\nTo issue a new book first return your current book\n\nWould you like to return your book? (y/n): ";
        char ch;
        cin>>ch;
        if(ch == 'y'){

            stu.close();
            remove(fileName);
            cout<<"Thank you for Returning ";
            temp.bookName();
            cout<<"\n\n\nPress any key to return to previous menu...";
            getch();
            return;

        }
        else{
            cout<<"You have chosen not to return ";
            temp.bookName();
            cout<<"\n\n\nPress any key to return to previous menu...";
            getch();
            return;
        }

    }
    else{

        fstream num;
        num.open("num.txt", ios::in);
        int n;
        num >> n;
        num.close();

        char bName[50];
        cout<<"Enter Name of Book you would like to issue: ";
        cin.getline(bName,50);

        fstream books;
        books.open("books.txt", ios::in);
        book tBook;
        int i;
        for(i = 0; i < n; i++){
            books.read((char*)&tBook,sizeof(tBook));
            if(tBook.isPresent(bName)){
                allowIssue = 1;
                break;
            }
            allowIssue = 0;
        }

        if(i != n){

            fstream stu;
            stu.open(fileName, ios::out);
            stu.write((char*)&tBook,sizeof(tBook));
            cout<<"Thank you for issuing "<<bName<<" form the Library...\n";
            stu.close();
        }
        else {

            cout<<"Book not found...\n";

        }

        books.close();
    }








    cout<<"\nPress any key to return to previous menu...";
    getch();

}

void book::newBook(){

    char ch;
    cin.get(ch);
    cout<<"Enter Name: ";
    cin.getline(name,50);
    cout<<"Enter Author: ";
    cin.getline(author,50);

}

void book::displayBook(){

    cout<<"Book Name: "<<name<<"\nAuthor: "<<author<<"\n\n";

}

int book::isPresent(char* x){

    if(strlen(x) != strlen(name))
        return 0;

    for(unsigned int i = 0; i < strlen(x); i++){
        if(x[i] != name[i])
            return 0;
    }

    return 1;


}

void book::bookName(){

    cout<<name;

}
