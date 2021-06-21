///***********************************************************
//                           Header File in Project
//************************************************************

#include <bits/stdc++.h>
#include <windows.h>
#include<conio.h>
using namespace std;

void gotoxy(short x, short y)
{
    COORD pos = {x, y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}


//***************************************************************
//                   CLASS USED IN PROJECT
//****************************************************************

class Book
{
    char bookNo[6];
    char bookName[50];
    char bookAuthorName[20];

public:
    void create_book()
    {
        cin.ignore();
        cout << "\nNew Book Entry.....\n";
        cout << "\nEnter The Book No: ";
        cin >> bookNo;
        cin.ignore();
        cout << "\nEnter the name of the Book: ";
        cin.getline(bookName, 50, '\n');
        cout << "\nEnter the Author's Name: ";
        cin.getline(bookAuthorName, 20, '\n');
        cout << "\n\nBook Created Successfully..";
    }

    void show_book()
    {
        cout << "\nBook No: " << bookNo;
        cout << "\nBook Name: " << bookName;
        cout << "\nAuthor: " << bookAuthorName;
    }

    void modify_book()
    {
        cout << "\nBook No: " << bookNo;
        cin.ignore();
        cout << "\nModify Book Name: ";
        cin.getline(bookName, 50, '\n');
        cin.ignore();
        cout << "\nModify Author's Name Of Book: ";
        cin.getline(bookAuthorName, 20, '\n');
    }

    char *returnBookNo()
    {
        return bookNo;
    }

    void report()
    {
        cout << bookNo << setw(30) << bookName << setw(30) << bookAuthorName << endl;
    }
};

// **************************  Book class ends here

//**************************** Student CLass Start ************//

class Student
{

    char id[6];
    char name[20];
    char issueBookNo[6];
    int token;

public:
    void createStudent()
    {
        cin.ignore();
        cout << "\nNew Student Entry....\n";
        cout << "\nStudent Id: ";
        cin >> id;
        cin.ignore();
        cout << "\nName: ";
        cin.getline(name, 20, '\n');
        issueBookNo[0] = '/0';
        token = 0;
        cout << "\n\nStudent Record Created Successfull..";
    }

    void showStudent()
    {
        cout << "\nId: " << id;
        cout << "\nName: " << name;
        cout << "\nNo Of Book Issued: " << token;
        if (token == 1)
            cout << "\nBook No: " << issueBookNo;
    }

    void modifyStudent()
    {
        cout << "\nStudent ID: " << id;
        cin.ignore();
        cout << "\nModify Student Name: ";
        cin.getline(name, 20, '\n');
    }

    char *returnID()
    {
        return id;
    }
    char *returnIssueBooKNo()
    {
        return issueBookNo;
    }
    int returnToken()
    {
        return token;
    }
    void setToken()
    {
        token = 1;
    }
    void resetToken()
    {
        token = 0;
    }
    void getsIssueBookNo(char t[])
    {
        strcpy(issueBookNo, t);
    }
    void report()
    {
        cout <<"\t"<< id << setw(12) << name << setw(20) << token << endl;
    }
};
///**************** Student Class End Here**************

//***************************************************************
//    	global declaration for stream object, object
//****************************************************************
fstream fp, fp1;

void fpopenBook()
{
    fp.read("book.dat", ios::in | ios::out);
}
void fpCloseBook()
{
    fp.close();
}

void fpopenStudent()
{
    fp.read("student.dat", ios::in | ios::out);
}
void fpCloseStudent()
{
    fp.close();
}

class Adminestrator : public Book, public Student
{
    Book book;
    Student student;

public:
    //***************************************************************
    //    	function to write in file
    //****************************************************************

    void writeBook()
    {
        char ch;
        fp.open("book.dat", ios::out | ios::app);
        do
        {
            book.create_book();
            fp.write((char *)&book, sizeof(Book));
            cout << "\n\nDo you Want to add more record..(y/n?): ";
            cin >> ch;
        }
        while (ch == 'y' || ch == 'Y');
        fp.close();
    }

    void writeStudent()
    {
        char ch;
        fp.open("student.dat", ios::out | ios::app);
        do
        {
            student.createStudent();
            fp.write((char *)&student, sizeof(Student));
            cout << "\n\nDo you want to add more record....(Y/n?): ";
            cin >> ch;
        }
        while (ch == 'Y' || ch == 'y');
        fp.close();
    }

    //***************************************************************
    //    	function to read specific record from file
    //****************************************************************

    void displaySpecificBook(char n[])
    {
        cout << "\nBook Details\n";
        int flag = 0;
        fp.open("book.dat", ios::in);
        while (fp.read((char *)&book, sizeof(Book)))
        {
            if (strcmpi(book.returnBookNo(), n) == 0)
            {
                book.show_book();
                flag = 1;
            }
        }
        fp.close();
        if (flag == 0)
            cout << "\n\nBook does not exist.";
    }

    void displaySpecificStudent(char n[])
    {
        cout << "\n\nStudent Details\n";
        int flag = 0;
        fp.open("student.dat", ios::in);
        while (fp.read((char *)&student, sizeof(Student)))
        {
            if ((strcmpi(student.returnID(), n) == 0))
            {
                student.showStudent();
                flag = 1;
            }
        }
        fp.close();
        if (flag == 0)
            cout << "\n\nStudent does not exist.";
    }

    //***************************************************************
    //    	function to modify record of file
    //****************************************************************

    void modifyBook()
    {
        char n[6];
        int found = 0;
        cout << "\n\nModify Book Recorded Section......";
        cout << "\n\nEnter the book number of the Book: ";
        cin >> n;
        fp.open("book.dat", ios::in | ios::out);
        while ((fp.read((char *)&book, sizeof(Book))) && found == 0)
        {
            if (strcmpi(book.returnBookNo(), n) == 0)
            {
                book.show_book();
                cout << "\nEnter The New Details of Book\n";
                book.modify_book();
                int pos = -1 * sizeof(book);
                fp.seekp(pos, ios::cur);
                fp.write((char *)&book, sizeof(Book));
                cout << "\n\n\t Record Updated...";
                found = 1;
            }
        }
        fp.close();
        if (found == 0)
            cout << "\n\n Record Not Found";
    }

    void modifyStudent()
    {
        char n[6];
        int found = 0;
        cout << "\n\nModify Student Information....";
        cout << "\n\nEnter the Id Number of the student: ";
        cin >> n;
        fp.open("student.dat", ios::in | ios::out);
        while (fp.read((char *)&student, sizeof(Student)) && found == 0)
        {
            if (strcmpi(student.returnID(), n) == 0)
            {
                student.showStudent();
                cout << "\nEnter the new Details of Student: \n";
                student.modifyStudent();
                int pos = -1 * sizeof(student);
                fp.seekp(pos, ios::cur);
                fp.write((char *)&student, sizeof(Student));
                cout << "\n\n\t Record Update Successfull....";
                found = 1;
            }
        }

        fp.close();
        if (found == 0)
            cout << "\n\n Record Not Found. ";
    }

    //***************************************************************
    //    	function to delete record of file
    //****************************************************************

    void deleteBook()
    {
        char n[6];
        cout << "\n\n\n\tDelete Book.............";
        cout << "\n\nEnter the Book number of the Book you Want to delete: ";
        cin >> n;
        fp.open("book.dat", ios::in | ios::out);
        fstream fp2;
        fp2.open("temp.dat", ios::out);
        fp.seekg(0, ios::beg);
        while (fp.read((char *)&book, sizeof(Book)))
        {
            if (strcmpi(book.returnBookNo(), n) != 0)
            {
                fp2.write((char *)&book, sizeof(Book));
            }
        }
        fp2.close();
        fp.close();
        remove("book.dat");
        rename("temp.dat", "book.dat");
        cout << "\n\n\tRecord Deleted ..";
    }

    void deleteStudent()
    {
        char n[6];
        int flag = 0;
        cout << "\n\n\n\tDelete Student...";
        cout << "\n\nEnter the ID Numer of the student you want to delete: ";
        cin >> n;
        fp.open("student.dat", ios::in | ios::out);
        fstream fp2;
        fp2.open("temp.dat", ios::out);
        fp.seekg(0, ios::beg);
        while (fp.read((char *)&student, sizeof(Student)))
        {
            if (strcmpi(student.returnID(), n) != 0)
            {
                fp2.write((char *)&student, sizeof(Student));
            }
            else flag=1;
        }
        fp2.close();
        fp.close();
        remove("student.dat");
        rename("temp.dat", "student.dat");
        if(flag==1)
            cout<<"\n\n\tRecord Deleted ..";
        else
            cout<<"\n\nRecord not found";
    }

    //***************************************************************
    //    	function to display all students list
    //****************************************************************

    void displayAllBooks()
    {
        fp.open("book.dat", ios::in);
        if (!fp)
        {
            cout << "Error !!! File Could not be OPEN";
            return;
        }
        cout << "\n\n\t\t Book List\n\n";
        cout<<"=========================================================================\n";
        cout<<"Book Number"<<setw(30)<<"Book Name"<<setw(30)<<"Author\n";
        cout<<"=========================================================================\n";
        while (fp.read((char *)&book, sizeof(Book)))
        {
            book.report();
        }
        fp.close();
    }

    void displayAllStudents()
    {
        fp.open("student.dat", ios::in);
        if (!fp)
        {
            cout << "Error !!! File could not be OPEN ";
            return;
        }

        cout << "\n\n\t\t Student List\n\n";
        cout<<"==================================================================\n";
        cout<<"\tID"<<setw(15)<<"Name"<<setw(20)<<"Book Issued\n";
        cout<<"==================================================================\n";

        while (fp.read((char *)&student, sizeof(Student)))
        {
            student.report();
        }

        fp.close();
    }

    //***************************************************************
    //    	function to issue book
    //****************************************************************
    void bookIssue()
    {
        char studentNo[6], bookNo[6];
        int found = 0, flag = 0;
        cout << "\n\nBook Issue.....";
        cout << "\n\n\tEnter the student's ID: ";
        cin >> studentNo;
        fp.open("student.dat", ios::in | ios::out);
        fp1.open("book.dat", ios::in | ios::out);

        while (fp.read((char *)&student, sizeof(Student)) && found == 0)
        {
            if (strcmpi(student.returnID(), studentNo) == 0)
            {
                found = 1;
                if (student.returnToken() == 0)
                {
                    cout << "\n\n\tEnter the Book Number: ";
                    cin >> bookNo;
                    while (fp1.read((char *)&book, sizeof(Book)) && flag == 0)
                    {
                        if (strcmpi(book.returnBookNo(), bookNo) == 0)
                        {
                            book.show_book();
                            flag = 1;
                            student.setToken();
                            student.getsIssueBookNo(book.returnBookNo());
                            int pos = -1 * sizeof(student);
                            fp.seekp(pos, ios::cur);
                            fp.write((char *)&student, sizeof(Student));
                            cout << "\n\n\tBook issued successfull\n\Please Note: Write the current date in backside of your book and submit within 15 days fine Taka. 1 for each day after 15 days period.";
                        }
                    }
                    if (flag == 0)
                        cout << "Book no Does not exist";
                }
                else
                {
                    cout << "You have not returned the last Book.";
                }
            }
        }

        if (found == 0)
            cout << "Student Record Not Exist....";
        fp.close();
        fp1.close();
    }

    //***************************************************************
    //    	function to deposit book
    //****************************************************************

    void bookDeposit()
    {
        char studentID[6], bookNo[6];
        int found = 0, flag = 0, day, fine;
        cout << "\n\nBook Deposit...";
        cout << "\n\n\tEnter the student ID: ";
        cin >> studentID;
        fp.open("student.dat", ios::in | ios::out);
        fp1.open("book.dat", ios::in | ios::out);
        while (fp.read((char *)&student, sizeof(Student)) && found == 0)
        {
            if (strcmpi(student.returnID(), studentID) == 0)
            {
                found = 1;
                if (student.returnToken() == 1)
                {
                    while (fp1.read((char *)&book, sizeof(Book)) && flag == 0)
                    {
                        if (strcmpi(book.returnBookNo(), student.returnIssueBooKNo()) == 0)
                        {
                            book.show_book();
                            flag = 1;
                            cout << "\n\nBook deposited in No. of days: ";
                            cin >> day;
                            if (day > 15)
                            {
                                fine = (day - 15) * 1;
                                cout << "\n\nFine has to deposited Taka. " << fine;
                            }
                            student.resetToken();
                            int pos = -1 * sizeof(student);
                            fp.seekp(pos, ios::cur);
                            fp.write((char *)&student, sizeof(Student));
                            cout << "\n\n\tBook Deposited successfully.";
                        }
                    }
                    if (flag == 0)
                        cout << "Book no does not exist";
                }
                else
                    cout << "No book is issued..please check!!";
            }
        }

        if (found == 0)
            cout << "Student record not exist...";

        fp.close();
        fp1.close();
    }
};

//***************************************************************
//    	INTRODUCTION FUNCTION
//****************************************************************

void intro()
{

    gotoxy(35, 11);
    cout << "LIBRARY";
    gotoxy(35, 14);
    cout << "MANAGEMENT";
    gotoxy(35, 17);
    cout << "SYSTEM";
    cout << "\n\nMADE BY : MEHEDI HASAN SHUVO";
    cout << "\n\nUniversity : Dhaka University & Engineering Technology";
}

//***************************************************************
//    	ADMINISTRATOR MENU FUNCTION
//****************************************************************

void admin_menu()
{

    int ch2;
    Adminestrator adminestrator;

    cout << "\n\n\n\tADMINISTRATOR MENU";
    cout << "\n\n\t1.CREATE STUDENT RECORD";
    cout << "\n\n\t2.DISPLAY ALL STUDENTS RECORD";
    cout << "\n\n\t3.DISPLAY SPECIFIC STUDENT RECORD ";
    cout << "\n\n\t4.MODIFY STUDENT RECORD";
    cout << "\n\n\t5.DELETE STUDENT RECORD";
    cout << "\n\n\t6.CREATE BOOK ";
    cout << "\n\n\t7.DISPLAY ALL BOOKS ";
    cout << "\n\n\t8.DISPLAY SPECIFIC BOOK ";
    cout << "\n\n\t9.MODIFY BOOK ";
    cout << "\n\n\t10.DELETE BOOK ";
    cout << "\n\n\t11.BACK TO MAIN MENU";
    cout << "\n\n\tPlease Enter Your Choice (1-11) ";
    cin >> ch2;
    switch (ch2)
    {
    case 1:
        adminestrator.writeStudent();
        break;
    case 2:
        adminestrator.displayAllStudents();

        break;
    case 3:
        char num[6];

        cout << "\n\n\tPlease Enter The Admission No. ";
        cin >> num;
        adminestrator.displaySpecificStudent(num);
        break;
    case 4:
        adminestrator.modifyStudent();
        break;
    case 5:
        adminestrator.deleteStudent();
        break;
    case 6:
        adminestrator.writeBook();
        break;
    case 7:
        adminestrator.displayAllBooks();
        break;
    case 8:
    {
        char num[6];

        cout << "\n\n\tPlease Enter The book No. ";
        cin >> num;
        adminestrator.displaySpecificBook(num);
        break;
    }
    case 9:
        adminestrator.modifyBook();
        break;
    case 10:
        adminestrator.deleteBook();
        break;
    case 11:
        return;
    default:
        cout << "\a";
    }
    admin_menu();
}

//***************************************************************
//    	THE MAIN FUNCTION OF PROGRAM
//****************************************************************


int main()
{
    char ch;
    Adminestrator adminestrator;
    intro();
    do
    {

        cout<<"\n\n\n\tMAIN MENU";
        cout<<"\n\n\t01. BOOK ISSUE";
        cout<<"\n\n\t02. BOOK DEPOSIT";
        cout<<"\n\n\t03. ADMINISTRATOR MENU";
        cout<<"\n\n\t04. EXIT";
        cout<<"\n\n\tPlease Select Your Option (1-4) ";
        ch=getche();
        switch(ch)
        {
        case '1':
            adminestrator.bookIssue();
            break;
        case '2':
            adminestrator.bookDeposit();
            break;
        case '3':
            admin_menu();
            break;
        case '4':
            exit(0);
        default :
            cout<<"\a";
        }
    }
    while(ch!='4');
    return 0;
}

//***************************************************************
//    			END OF PROJECT
//***************************************************************