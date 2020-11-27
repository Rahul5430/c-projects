#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <sstream>
using namespace std;

typedef map <string, string> database;
database db;

class SignUp{
    private:
        string username;
        string password;
    public:
        SignUp() {
            cout<<"Welcome to the Sign up page"<<endl;
        }
        void userSignUp(); 
};

class Login {
    private:
        string username;
        string password;
    public:
        Login() {
            cout<<"Welcome to the Login page"<<endl;
        }
        void userLogin() {
            //cout<<"Welcome to the Login page"<<endl;
            cout<<"Please enter username : ";
            cin>>username;
            if (db.find(username) != db.end())
            {
                cout<<"Please enter password : ";
                cin>>password;
                if (db[username] == password)
                {
                    cout<<"Login Successful"<<endl;
                    char choice;
                    cout<<"Do you want to Login(l) or Signup(s) again? : ";
                    cin>>choice;
                    if (choice == 'l' || choice == 'L')
                    {
                        Login l;
                        l.userLogin();
                    }
                    else if (choice == 's' || choice == 'S')
                    {
                        SignUp s;
                        s.userSignUp();
                    }
                    else
                    {
                        cout<<"OK Bye!";
                    }
                }
                else
                {
                    cout<<"Wrong Credentials, please try again!\n";
                    userLogin();
                }
            }
            else
            {
                cout<<"No username found, please try again!\n";
                userLogin();
            }
        }
};

void SignUp::userSignUp() {
    cout<<"Please enter username : ";
    cin>>username;
    if (db.find(username) != db.end())
    {
        cout<<"The username is already taken, please try again"<<endl;
        userSignUp();
    }
    else
    {
        cout<<"Enter password : ";
        cin>>password;
        db[username] = password;
        cout<<"Sign Up Successful!"<<endl;
        char choice;
        cout<<"Do you want to login now? (y/n) : ";
        cin>>choice;
        if (choice == 'y' || choice == 'L')
        {
            Login l;
            l.userLogin();
        }
        else
        {
            cout<<"OK Bye!";
        }
    }
}

class Choice {
    private:
        char choice;
    public:
        void choose() {
            cout<<"Do you want to Login(l) or Signup(s)? : ";
            cin>>choice;
            if (choice == 'l' || choice == 'L')
            {
                Login l;
                l.userLogin();
            }
            else if (choice == 's' || choice == 'S')
            {
                SignUp s;
                s.userSignUp();
            }
            else
            {
                cout<<"INVALID INPUT"<<endl;
                choose();
            }
        }
};

int main()
{
    fstream fin;
    fin.open("database.txt", ios::in);
    //vector<string> row;
    string temp, line;
    while (fin >> temp)
    {
        vector<string> row;
        //row.clear();
        getline(fin, line);
        stringstream s(line);
        string word;
        cout<<"hi1"<<endl;
        while (getline(s, word, ','))
        {
            row.push_back(word);
            cout<<"hi2"<<endl;
        }
        //db[row[0]] = row[1];
        //cout<<row[0]<<endl;
        //cout<<row[1]<<endl;
        //cout<<row[2]<<endl;
        cout<<"hi3"<<endl;
    }

    db["Rahul"] = "abc123";
    db["Abc123"] = "rahul";
    cout<<"Welcome to Login Portal!"<<endl;
    cout<<db["rahul"]<<endl;
    Choice c;
    c.choose();
    return 0;
}