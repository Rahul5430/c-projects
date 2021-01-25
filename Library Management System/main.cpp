#include <iostream>
#include <iomanip>
#include <fstream>
#include <unistd.h>
using namespace std;

class Book {
    private:
        char bookNo[6];
        char bookName[100];
        char authorName[20];
    public:
        void createBook()
        {
            cout<<"\nNEW BOOK ENTRY...\n";
            cout<<"\nEnter The Book Number : ";
            cin>>bookNo;
            cout<<"\nEnter The Name Of The Book : ";
            getchar();
            gets(bookName);
            cout<<"\nEnter The Name Of The Author : ";
            gets(authorName);
            cout<<"\n\n\nBook Created...";
        }
        void showBook()
        {
            cout<<"\nBook Number : "<<bookNo;
            cout<<"\nBook Name : ";
            puts(bookName);
            cout<<"Author Name : ";
            puts(authorName);
            getchar();
        }
        void modifyBook()
        {
            cout<<"\nBook Number : "<<bookNo;
            cout<<"\nModified Book Name : ";
            getchar();
            gets(bookName);
            cout<<"\nModified Author's Name : ";
            gets(authorName);
        }
        char* retBookNo()
        {
            return bookNo;
        }
        void report()
        {
            cout<<bookNo<<setw(50)<<bookName<<setw(30)<<authorName<<endl;
        }
};

class Student {
    private:
        char admno[6];
        char name[20];
        char stbkno[6];
        int token;
    public:
        void createStudent()
        {
            system("cls");
            cout<<"\nNEW STUDENT ENTRY...\n";
            cout<<"\nEnter The admission no. ";
            cin>>admno;
            getchar();
            cout<<"\n\nEnter The Name of The Student ";
            gets(name);
            token=0;
            stbkno[0]='/0';
            cout<<"\n\nStudent Record Created..";
        }
        void showStudent()
        {
            cout<<"\nAdmission no. : "<<admno;
            cout<<"\nStudent Name : ";
            puts(name);
            cout<<"\nNo of Book issued : "<<token;
            if(token==1)
                cout<<"\nBook No "<<stbkno;
        }
        void modifyStudent()
        {
            cout<<"\nAdmission No : "<<admno;
            getchar();
            cout<<"\nModify Student Name : ";
            gets(name);
        }
        char* retAdmNo()
        {
            return admno;
        }
        char* retStBkNo()
        {
            return stbkno;
        }
        int retToken()
        {
            return token;
        }
        void addToken()
        {
            token = 1;
        }
        void resetToken()
        {
            token = 0;
        }
        void getStBkNo(char t[])
        {
            strcpy(stbkno, t);
        }
        void report()
        {
            cout<<"\t"<<admno<<setw(30)<<name<<setw(10)<<token<<endl;
        }
};

fstream fp, fp1;
Book book;
Student st;

void writeBook()
{
    char ch;
    fp.open("book.dat", ios::out|ios::app);
    do
    {
        system("cls");
        book.createBook();
        fp.write((char*)&book, sizeof(Book));
        cout<<"Do you want to add more books..(y/n?) : ";
        cin>>ch;
    } while (ch=='y' || ch=='Y');
    fp.close();
}

void writeStudent()
{
    char ch;
    fp.open("student.dat", ios::out | ios::app);
    do
    {
        st.createStudent();
        fp.write((char*)&st, sizeof(Student));
        cout<<"\n\nDo You Want To Add More Record...(y/n)?";
        cin>>ch;
    } while (ch=='y' || ch=='Y');
    fp.close();
}

void displaySpecificBook(char n[])
{
    cin.ignore();
    cout<<"\nBOOK DETAILS\n";
    int flag=0;
    fp.open("book.dat", ios::in);
    while (fp.read((char*)&book, sizeof(Book)))
    {
        if (strcmpi(book.retBookNo(), n) == 0)
        {
            book.showBook();
            flag = 1;
        }
    }
    fp.close();
    if (flag == 0)
    {
        cout<<"\n\nBook Does Not Exist";
        getchar();
    }
}

void displaySpecificStudent(char n[])
{
    cout<<"\nSTUDENT DETAILS\n";
    int flag=0;
    fp.open("student.dat", ios::in);
    while (fp.read((char*)&st, sizeof(Student)))
    {
        if ((strcmpi(st.retAdmNo(), n) == 0))
        {
            st.showStudent();
            flag=1;
        }
    }
    fp.close();
    if (flag == 0)
    {
        cout<<"\n\nStudent Does Not Exist";
    }
    getchar();
    getchar();
}

void modifyBook()
{
    char n[6];
    int found = 0;
    system("cls");
    cout<<"\n\n\tMODIFY BOOK RECORD...";
    cout<<"\n\n\tEnter The Book No. Of The Book : ";
    cin>>n;
    fp.open("book.dat", ios::in | ios::out);
    while (fp.read((char*)&book, sizeof(Book)) && found == 0)
    {
        if (strcmpi(book.retBookNo(), n) == 0)
        {
            book.showBook();
            cout<<"\nEnter The New Details Of Book"<<endl;
            book.modifyBook();
            int pos = -1 * sizeof(book);
            fp.seekp(pos, ios::cur);
            fp.write((char*)&book, sizeof(Book));
            cout<<"\n\n\tRecord Updated";
            found = 1;
        }
    }
    fp.close();
    if (found == 0)
        cout<<"\n\nRecord Not Found";
    getchar();
    getchar();
}

void modifyStudent()
{
    char n[6];
    int found=0;
    system("cls");
    cout<<"\n\n\tMODIFY STUDENT RECORD... ";
    cout<<"\n\n\tEnter The Admission Number Of The Student : ";
    cin>>n;
    fp.open("student.dat", ios::in | ios::out);
    while (fp.read((char*)&st, sizeof(Student)) && found == 0)
    {
        if (strcmpi(st.retAdmNo(), n) == 0)
        {
            st.showStudent();
            cout<<"\nEnter The New Details Of The Student"<<endl;
            st.modifyStudent();
            int pos = -1 * sizeof(st);
            fp.seekp(pos, ios::cur);
            fp.write((char*)&st, sizeof(Student));
            cout<<"\n\n\t Record Updated";
            found = 1;
        }
    }
    fp.close();
    if (found == 0)
    {
        cout<<"\n\n Record Not Found ";
    }
    getchar();
}

void deleteBook()
{
    char n[6];
    system("cls");
    cout<<"\n\n\n\tDELETE BOOK ...";
    cout<<"\n\nEnter The Book no. of the Book You Want To Delete : ";
    cin>>n;
    fp.open("book.dat",ios::in|ios::out);
    fstream fp2;
    fp2.open("Temp.dat",ios::out);
    fp.seekg(0,ios::beg);
    while(fp.read((char*)&book,sizeof(Book)))
    {
        if(strcmpi(book.retBookNo(), n) != 0)  
        {
            fp2.write((char*)&book,sizeof(Book));
        }
    }
        
    fp2.close();
    fp.close();
    remove("book.dat");
    rename("Temp.dat","book.dat");
    cout<<"\n\n\tRecord Deleted ..";
    getchar();
}

void deleteStudent()
{
    char n[6];
    int flag = 0;
    system("cls");
    cout<<"\n\n\n\tDELETE STUDENT...";
    cout<<"\n\nEnter The Admission No. Of The Student You Want To Delete : ";
    cin>>n;
    fp.open("student.dat", ios::in | ios::out);
    fstream fp2;
    fp2.open("Temp.dat", ios::out);
    fp.seekg(0, ios::beg);
    while (fp.read((char*)&st, sizeof(Student)))
    {
        if (strcmpi(st.retAdmNo(), n) != 0)
        {
            fp2.write((char*)&st, sizeof(Student));
        }
        else
        {
            flag = 1;
        }
    }
    fp2.close();
    fp.close();
    remove("student.dat");
    rename("Temp.dat", "student.dat");
    if (flag == 1)
    {
        cout<<"\n\n\tRecord Deleted...";
    }
    else
    {
        cout<<"\n\nRecord Not Found";
    }
    getchar();
    getchar();
}

void displayAllBooks()
{
    system("cls");
    fp.open("book.dat", ios::in);
    if (!fp)
    {
        cout<<"ERROR OPENING FILE!";
        getchar();
        return ;
    }
    cout<<"\n\n\t\tBOOK LIST\n\n";
    cout<<"======================================================================================\n";
    cout<<"Book Number"<<setw(35)<<"Book Name"<<setw(35)<<"Author\n";
    cout<<"======================================================================================\n";
    while (fp.read((char*)&book, sizeof(Book)))
    {
        book.report();
    }
    fp.close();
    getchar();
    getchar();
}

void displayAllStudents()
{
    system("cls");
    fp.open("student.dat", ios::in);
    if (!fp)
    {
        cout<<"ERROR!!! FILE COULD NOT BE OPEN";
        getchar();
        return;
    }
    cout<<"\n\n\t\tSTUDENT LIST\n\n";
    cout<<"===================================================================\n";
    cout<<"\tAdmission No."<<setw(15)<<"Name"<<setw(20)<<"Book Issued\n";
    cout<<"===================================================================\n";
    while (fp.read((char*)&st, sizeof(Student)))
    {
        st.report();
    }
    fp.close();
    getchar();
    getchar();
}

void bookIssue()
{
    char sn[6], bn[6];
    int found=0, flag=0;
    system("cls");
    cout<<"\n\nBOOK ISSUE...";
    cout<<"\n\n\tEnter The Student's Admission No : ";
    cin>>sn;
    fp.open("student.dat", ios::in | ios::out);
    fp1.open("book.dat", ios::in | ios::out);
    while (fp.read((char*)&st, sizeof(Student)) && found == 0)
    {
        if (strcmpi(st.retAdmNo(), sn) == 0)
        {
            found = 1;
            if (st.retToken() == 0)
            {
                cout<<"\n\n\tEnter The Book No : ";
                cin>>bn;
                while (fp1.read((char*)&book, sizeof(Book)) && flag == 0)
                {
                    if (strcmpi(book.retBookNo(), bn) == 0)
                    {
                        book.showBook();
                        flag=1;
                        st.addToken();
                        st.getStBkNo(book.retBookNo());
                        int pos = -1 * sizeof(st);
                        fp.seekp(pos, ios::cur);
                        fp.write((char*)&st, sizeof(Student));
                        cout<<"\n\n\t Book Issued Successfully\n\nPlease Note: Write current date in backside of book and submit within 15 days. Fine Rs. 1 for each day after 15 days period";
                    }
                }
                if (flag == 0)
                {
                    cout<<"Book No. Does Not Exist";
                }
            }
            else
            {
                cout<<"You Have Not Returned The Last Book";
                sleep(2);
            }
        }
    }
    if (found == 0)
    {
        cout<<"Student Record Does Not Exist...";
        sleep(2);
    }
    getchar();
    fp.close();
    fp1.close();
}

void bookDeposit()
{
    char sn[6], bn[6];
    int found=0, flag=0, day, fine;
    system("cls");
    cout<<"\n\nBOOK DEPOSIT...";
    cout<<"\n\n\tEnter The Student's Admission No : ";
    cin>>sn;
    fp.open("student.dat", ios::in | ios::out);
    fp1.open("book.dat", ios::in | ios::out);
    while (fp.read((char*)&st, sizeof(Student)) && found == 0)
    {
        if (strcmpi(st.retAdmNo(), sn) == 0)
        {
            found = 1;
            if (st.retToken() == 1)
            {
                while (fp1.read((char*)&book, sizeof(Book)) && flag == 0)
                {
                    if (strcmpi(book.retBookNo(), st.retStBkNo()) == 0)
                    {
                        book.showBook();
                        flag=1;
                        cout<<"\n\nBook Deposited In No. Of Days : ";
                        cin>>day;
                        if (day>15)
                        {
                            fine = (day - 15) * 1;
                            cout<<"\n\nFine Has To Be Deposited Rs. "<<fine;
                        }
                        st.resetToken();
                        int pos = -1 * sizeof(st);
                        fp.seekp(pos, ios::cur);
                        fp.write((char*)&st, sizeof(Student));
                        cout<<"\n\n\t Book Deposited Successfully";
                        sleep(2);
                    }
                }
                if (flag == 0)
                {
                    cout<<"Book No. Does Not Exist";
                    sleep(2);
                }
            }
            else
            {
                cout<<"No Book Is Issued... Please Check!!";
                sleep(2);
            }
        }
    }
    if (found == 0)
    {
        cout<<"Student Record Does Not Exist...";
        sleep(2);
    }
    getchar();
    fp.close();
    fp1.close();
}

class Admin {
    private:
        int ch2;
    public:
        void adminMenu()
        {
            system("cls");
            cout<<"\n\n\n\tADMINISTRATOR MENU";
            cout<<"\n\n\t1.CREATE STUDENT RECORD";
            cout<<"\n\n\t2.DISPLAY ALL STUDENTS RECORD";
            cout<<"\n\n\t3.DISPLAY SPECIFIC STUDENT RECORD ";
            cout<<"\n\n\t4.MODIFY STUDENT RECORD";
            cout<<"\n\n\t5.DELETE STUDENT RECORD";
            cout<<"\n\n\t6.CREATE BOOK ";
            cout<<"\n\n\t7.DISPLAY ALL BOOKS ";
            cout<<"\n\n\t8.DISPLAY SPECIFIC BOOK ";
            cout<<"\n\n\t9.MODIFY BOOK ";
            cout<<"\n\n\t10.DELETE BOOK ";
            cout<<"\n\n\t11.BACK TO MAIN MENU";
            cout<<"\n\n\tPlease Enter Your Choice (1-11) : ";
            cin>>ch2;
            switch (ch2)
            {
                case 1:
                    system("cls");
                    writeStudent();
                    break;
                case 2:
                    displayAllStudents();
                    break;
                case 3: {
                    char num[6];
                    system("cls");
                    cout<<"\n\n\tPlease Enter The Admission No : ";
                    cin>>num;
                    displaySpecificStudent(num);
                    break;
                }
                case 4:
                    modifyStudent();
                    break;
                case 5:
                    deleteStudent();
                    break;
                case 6:
                    system("cls");
                    writeBook();
                    break;
                case 7:
                    system("cls");
                    displayAllBooks();
                    break;
                case 8: {
                    char num[6];
                    system("cls");
                    cout<<"\n\n\tPlease Enter The Book No : ";
                    cin>>num;
                    displaySpecificBook(num);
                    break;
                }
                case 9:
                    modifyBook();
                    break;
                case 10:
                    deleteBook();
                    break;
                case 11: return;
                default: cout<<"\a";
            }
            adminMenu();
        }
        void adminAccess()
        {
            cout<<"Admin Access";
        }
};

class Intro {
    private:
        char ch;
    public:
        Intro()
        {
            system("cls");
            cout<<"\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t\t\t\t   LIBRARY";
            cout<<"\n\n\t\t\t\t\t\t\t\t\t\t  MANAGEMENT";
            cout<<"\n\n\t\t\t\t\t\t\t\t\t\t   SYSTEM";
            cout<<"\n\n\t\t\t\t\t\t\t\t\t    MADE BY : RAHUL SHARMA";
            cout<<"\n\n\t\t\t\t\t\t\t\t\t\tCOLLEGE : PEC";
            sleep(3);
            cout<<"\n\n\t\t\t\t\t\t\t\t\t(Press Any Key To Continue)";
            getchar();
        }
        void choose()
        {
            do
            {
                system("cls");
                cout<<"\n\n\n\tMAIN MENU";
                cout<<"\n\n\t01. BOOK ISSUE";
                cout<<"\n\n\t02. BOOK DEPOSIT";
                cout<<"\n\n\t03. ADMINISTRATOR MENU";
                cout<<"\n\n\t04. EXIT";
                cout<<"\n\n\tPlease Select Your Option (1-4) : ";
                cin>>ch;
                switch (ch)
                {
                    case '1':
                        system("cls");
                        bookIssue();
                        break;
                    case '2':
                        bookDeposit();
                        break;
                    case '3':
                        Admin admin;
                        admin.adminMenu();
                        break;
                    case '4':
                        exit(0);
                    default:
                        cout<<"\a";
                }
            } while(ch != '4');
        }
};

int main()
{
    Intro intro;
    intro.choose();
    return 0;
}
