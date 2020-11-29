#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <sstream>
#include <string>
#include <algorithm>
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
            cout<<"Please enter username (NOTE: Username is case-insensitive) : ";
            cin>>username;
            transform(username.begin(), username.end(), username.begin(), ::tolower);
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
    cout<<"Please enter username (NOTE: Username is case-insensitive) : ";
    cin>>username;
    transform(username.begin(), username.end(), username.begin(), ::tolower);
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
    if (fin.is_open())
    {
        int i=0;
        vector<string> row;
        string line;
        while (fin >> line)
        {
            if (i == 0)
            {
                i++;
                continue;
            }
            vector<string> row;
            row.clear();
            stringstream s(line);
            string word;
            while (getline(s, word, ','))
            {
                row.push_back(word);
            }
            db[row[0]] = row[1];
            i++;
        }
        fin.close();
    }
    else
    {
        cout<<"Error opening file!"<<endl;
    }

    database::iterator itr;
    for (itr = db.begin(); itr!=db.end(); itr++)
    {
        cout<<itr->first<<" "<<itr->second<<endl;
    }
    cout<<"Welcome to Login Portal!"<<endl;
    Choice c;
    c.choose();

    fstream fout;
    fout.open("database.txt", ios::out);
    if (fout.is_open())
    {
        database::iterator itr;
        fout<<"Username,Password"<<endl;
        for (itr = db.begin(); itr != db.end(); itr++)
        {
            fout<<itr->first<<","<<itr->second<<endl;
        }
    }
    else
    {
        cout<<"Error opening file to save credentials"<<endl;
    }
    return 0;
}