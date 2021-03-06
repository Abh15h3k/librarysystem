#include <iostream>
#include <fstream>
#include <conio.h>
#include <string.h>
#include <stdlib.h>

using namespace std;

class Lib{

    public:

        void menu();//done
        void student();//done
        void librarian();//done
        void viewBooks(int);//done
        void issue_Return();//done
        void addBook();//done
        void removeBook();//done
        int pass();
        string getpass(const char *prompt);

};

class book{

    public:
        char name[50];
        char author[50];
        char publication[50];

        int newBook();
        void displayBook();
        int isPresent(char* x);
        void bookName();
        void issue();

};

int main(){

    Lib lib0;
    lib0.menu();
    getch();
    return 0;

}

void Lib::menu(){

    while(true){
        char ch = ' ';
        system("cls");
        cout<<"<<<<<<<<<<<< Library Management >>>>>>>>>>>>\n\n\t\t1. Student\n\t\t2. Librarian\n\t\t3. Exit\n\n\t\tEnter Choice: ";
        while(ch != '1' && ch != '2' && ch != '3'){

            cin>>ch;
            if(ch == '1' || ch == '2' || ch == '3')
                break;
            else
                cout<<"\t\tInvalid Option...\n\t\tEnter Choice:";

        }

        if(ch == '1')
            student();
        else if(ch == '2'){
            string passw = getpass("Enter Password: ");
            const char *password = passw.c_str();
            if(strcmp(password,"admin123")==0)
                librarian();
            else{
                cout<<"\t\tWrong Password...";
                getch();
            }
        }
        else if(ch == '3')
            return;
    }
}

void Lib::student(){
    while(true){
        char ch = ' ';
        system("cls");
        cout<<"<<<<<<<<<<<< Welcome Student >>>>>>>>>>>>\n\n\t    1. View Available Books\n\t    2. Issue/Return a Book\n\t    3. Previous Menu\n\n\t    Enter Choice: ";
        while(ch != '1' && ch != '2' && ch != '3'){

            cin>>ch;
            if(ch == '1' || ch == '2' || ch == '3')
                break;
            else
                cout<<"\t    Invalid Option...\n\t    Enter Choice:";

        }

        if(ch == '1')
            viewBooks(0);
        else if(ch == '2')
            issue_Return();
        else if(ch == '3')
            return;
    }
}

void Lib::librarian(){

    while(true){

        char ch = ' ';
        system("cls");
        cout<<"<<<<<<<<<<<<<<< Welcome Librarian >>>>>>>>>>>>\n\n\t      1. View Available Books\n\t      2. Add Book\n\t      3. Remove Book\n\t      4. Previous Menu\n\n\t      Enter Choice: ";
        while(ch != '1' && ch != '2' && ch != '3' && ch != '4'){

            cin>>ch;
            if(ch == '1' || ch == '2' || ch == '3' || ch == '4')
                break;
            else
                cout<<"\t      Invalid Option...\n\t      Enter Choice:";

        }

        if(ch == '1')
            viewBooks(0);
        else if(ch == '2')
            addBook();
        else if(ch == '3')
            removeBook();
        else if(ch == '4')
            return;

    }

}

void Lib::addBook(){

    system("cls");
    cout<<"<<<<<<<<<<<< Add New Book >>>>>>>>>>>>\n\n";

    fstream num;
    num.open("num.txt", ios::in);
    int n;
    num >> n;
    num.close();

    book temp;
    fstream books;
    books.open("books.txt", ios::app | ios::binary);
    int ins = temp.newBook();
    if(ins){
        books.write((char*)&temp,sizeof(temp));
        n++;
        num.open("num.txt", ios::out);
        num << n;
        num.close();
        cout<<"\tBook Added\n";
    }
    else
        cout<<"\tBook not Added\n";
    books.close();



    cout<<"\nPress any key to return to previous menu...";
    getch();

}

void Lib::removeBook(){

    system("cls");
    cout<<"<<<<<<<<<<<< Book Removal >>>>>>>>>>>>\n\n";
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
    books.open("books.txt", ios::in | ios::binary);
    temp.open("temp.txt", ios::out | ios::binary);

    char ch;
    cin.get(ch);
    viewBooks(1);
    cout<<"(Type cancel if you do not want to remove a book)\nEnter Name of Book to Remove: ";
    cin.getline(bName,50);
    if(!(strcmpi(bName, "cancel"))){
        cout<<"Book Removal aborted\n\nPress any key to return to previous menu...";
        getch();
        return;

    }
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
    cout<<" Book Removed\nPress any key to return to previous menu...";
    getch();
    return;

}

void Lib::viewBooks(int x = 0){

    system("cls");
    cout<<"<<<<<<<<<<<< Library >>>>>>>>>>>>\n\n";
    fstream num;
    num.open("num.txt", ios::in);
    int n;
    num >> n;
    num.close();

    if(!n){

        cout<<"     No Books in Library\n     Press any key to return to previous menu...";
        getch();
        return;

    }

    book temp;
    fstream books;
    books.open("books.txt", ios::in | ios::binary);

    for(int i =0;i < n; i++){
        cout<<"     ---------- "<<(i+1)<<" ----------\n\n";
        books.read((char*)&temp,sizeof(temp));
        temp.displayBook();


    }
    if(x == 0){
        cout<<"\n     Press any key to return to previous menu...";
        getch();
    }
    books.close();


}

void Lib::issue_Return(){

    system("cls");
    char ch;
    char sName[50];

    cout<<"<<<<<<<<<<<< Issue/Return >>>>>>>>>>>>\n\n";

    cin.get(ch);
    cout<<"\tEnter Student Name: ";
    cin.getline(sName,50);

    char* fileName = sName;
    strcat(fileName,".txt");

    fstream stu;
    stu.open(fileName, ios::in);
    if(stu)
    {

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
        viewBooks(1);
        if(n == 0){
            return;
        }
        cout<<"\n";
        char bName[50];
        cout<<"Enter Name of Book you would like to issue: ";
        cin.getline(bName,50);

        if(strlen(bName) == 6){

            if(strcmpi(bName,"cancel") == 0){

                cout<<"You have chosen not to issue any book...\n\nPress any key to return to previous menu...";
                getch();
                return;

            }

        }

        fstream books;
        books.open("books.txt", ios::in | ios::binary);
        book tBook;
        int i;
        for(i = 0; i < n; i++){
            books.read((char*)&tBook,sizeof(tBook));
            if(tBook.isPresent(bName)){
                break;
            }
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

int Lib::pass(){

    char p[20];
    char ch;
    cin.get(ch);
    cout<<"\t\tEnter Password: ";
    cin.getline(p,20);
    if(strcmp(p,"admin123") == 0){
        return 1;
    }
    else
    {
        cout<<"\t\tWrong Password...";
        getch();
    }
    return 0;
}

string Lib::getpass(const char *prompt)
{
  const char BACKSPACE=127;
  const char RETURN=10;
  bool show_asterisk=true;
  string password;
  unsigned char ch=0;

  cout<<"\t\t"<<prompt;

  while((ch=getch())!=RETURN)
    {
       if(ch==BACKSPACE)
         {
            if(password.length()!=0)
              {
                 if(show_asterisk)
                 cout <<"\b \b";
                 password.resize(password.length()-1);
              }
         }
       else
         {
             password+=ch;
             if(show_asterisk)
                 cout <<'*';
         }
    }
  cout <<endl;
  return password;
}

int book::newBook(){

    char ch;
    cin.get(ch);
    cout<<"\tEnter Book Name: ";
    cin.getline(name,50);
    cout<<"\tEnter Author: ";
    cin.getline(author,50);
    cout<<"\tEnter Publication: ";
    cin.getline(publication,50);
    cout<<"\n\tAre you Sure?(y/n): ";
    cin>>ch;
    if(ch == 'n')
        return 0;
    return 1;

}

void book::displayBook(){

    cout<<"     Book Name: "<<name<<"\n     Author: "<<author<<"\n     Publication: "<<publication<<"\n\n";

}

int book::isPresent(char* x){

    if(strlen(x) != strlen(name))
        return 0;
    if(strcmpi(x,name) != 0)
        return 0;
    return 1;

}

void book::bookName(){
    cout<<name;
}
