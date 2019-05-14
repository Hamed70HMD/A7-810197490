#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <fstream>
#include <cstdlib>
#include "MyExceptions.h"

using namespace std;

//POST login ? username hamed password jksagdfg
//POST signup ? username hamed password jksagdfg email asfag age 15265

class Film
{
private:
    int id;
    std::string name = "";
    std::string year = "";
    std::string lenght = "";
    std::string price = "";
    std::string summary = "";
    std::string director = "";

public:
    Film(int _id);
    void set_name(std::string _name);
    void set_year(std::string _year);
    void set_lenght(std::string _length);
    void set_price(std::string _price);
    void set_summary(std::string _summary);
    void set_director(std::string _director);

    std::string set_name();
    std::string set_year();
    std::string set_lenght();
    std::string set_price();
    std::string set_summary();
    std::string set_director();
};
Film::Film(int _id) : id(_id) {}
void Film::set_name(std::string _name) { name = _name; }
void Film::set_year(std::string _year) { year = _year; }
void Film::set_lenght(std::string _length) { lenght = _length; }
void Film::set_price(std::string _price) { price = _price; }
void Film::set_summary(std::string _summary) { summary = _summary; }
void Film::set_director(std::string _director) { director = _director; }

std::string Film::set_name() { return name; }
std::string Film::set_year() { return year; }
std::string Film::set_lenght() { return lenght; }
std::string Film::set_price() { return price; }
std::string Film::set_summary() { return summary; }
std::string Film::set_director() { return director; }

//-------------------------------------------------------------------------------------------------------------------
class User
{
private:
    int id;
    std::string username = "";
    std::string password = "";
    std::string email = "";
    std::string age = "";
    bool publisher = false;

public:
    User(int _id);
    
    void set_username(std::string _username);
    void set_password(std::string _password);
    void set_email(std::string _email);
    void set_age(std::string _age);
    void set_publisher(bool _publisher);

    int get_id();
    std::string get_username();
    std::string get_password();
    std::string get_email();
    std::string get_age();
    bool get_publisher();

};
User::User(int _id) : id(_id) {}

void User::set_username(std::string _username) { username = _username; }
void User::set_password(std::string _password) { password = _password; }
void User::set_email(std::string _email) { email = _email; }
void User::set_age(std::string _age) { age = _age; }
void User::set_publisher(bool _publisher) { publisher = _publisher; }

int User::get_id() { return id; }
std::string User::get_username() { return username; }
std::string User::get_password() { return password; }
std::string User::get_email() { return email; }
std::string User::get_age() { return age; }
bool User::get_publisher() { return publisher; }


class Interface
{
private:
    int user_id = 1;
    int film_id = 1;
    int logedin_user_index;
    std::string command;
    std::vector<std::string> command_word;
    std::vector<User> user;
public:
    Interface();
    void read_data();
    void set_data();
    void print_data();
};



Interface::Interface()
{
}

void Interface::read_data()
{
    getline(cin, command);
    istringstream iss(command);
    std::string sub;
    int i = 1;
    while (iss >> sub)
    {
        command_word.push_back(sub);
    }
}
void Interface::set_data()
{
    if (command_word[0] == "POST")
    {
        if (command_word[1] == "signup")
        {
            user.push_back(User(user_id));
            logedin_user_index == user_id - 1;
            user_id++;
            for (int i = 3; i < command_word.size(); i++)
            {
                if (command_word[i] == "username")
                {
                    user[user_id - 2].set_username(command_word[i + 1]);
                    i++;
                }
                else if (command_word[i] == "password")
                {
                    user[user_id - 2].set_password(command_word[i + 1]);
                    i++;
                }
                else if (command_word[i] == "email")
                {
                    user[user_id - 2].set_email(command_word[i + 1]);
                    i++;                
                }
                else if (command_word[i] == "age")
                {
                    user[user_id - 2].set_age(command_word[i + 1]);
                    i++;
                }
                else if (command_word[i] == "publisher" || command_word[i] == "[publisher")
                {
                    if (command_word[i + 1] == "true")
                        user[user_id - 2].set_publisher(true);
                    else
                        user[user_id - 2].set_publisher(false);  
                    i++;                
                }
                else
                    throw BadCommand();                
            }
            if (user[user_id - 2].get_username() == "" || user[user_id - 2].get_password() == "" 
                    || user[user_id - 2].get_email() == "" || user[user_id - 2].get_age() == "")
            {
                cout << "asfsgd";
                throw WrongInput();
            }
            else
            {
                cout << "OK" << endl;
            }            
        }
        else if (command_word[1] == "login")
        {
            std::string temp_username, temp_password;
            for (int i = 3; i < command_word.size(); i++)
            {
                if (command_word[i] == "username")
                {
                    temp_username = command_word[i + 1];
                }
                else if (command_word[i] == "password")
                {
                    temp_password = command_word[i + 1];
                }
                else
                    throw WrongInput();
            }
            for (int i = 0; i < user.size(); i++)
            {
                if(user[i].get_username() == temp_username && user[i].get_password() == temp_password)
                {
                    logedin_user_index = i;
                    cout << "OK" << endl;
                }
                else
                {
                    throw WrongInput();
                }  
            }
        }
        else if (command_word[1] == "films")
        {
            user.push_back(User(user_id));
            user_id++;
            for (int i = 3; i < command_word.size(); i++)
            {
                if (command_word[i] == "username")
                {
                    user[user_id - 2].set_username(command_word[i + 1]);
                    i++;
                }
                else if (command_word[i] == "password")
                {
                    user[user_id - 2].set_password(command_word[i + 1]);
                    i++;                
                }
                else if (command_word[i] == "email")
                {
                    user[user_id - 2].set_email(command_word[i + 1]);
                    i++;                
                }
                else if (command_word[i] == "age")
                {
                    user[user_id - 2].set_age(command_word[i + 1]);
                    i++;                
                }
                else if (command_word[i] == "publisher" || command_word[i] == "[publisher")
                {
                    if (command_word[i + 1] == "true")
                        user[user_id - 2].set_publisher(true);
                    else
                        user[user_id - 2].set_publisher(true);  
                    i++;                
                }
                // else
                //     throw BadCommand();
            } 
        }
        else if (command_word[1] == "money")
        {
            user.push_back(User(user_id));
            user_id++;
            for (int i = 3; i < command_word.size(); i++)
            {
                if (command_word[i] == "username")
                {
                    user[user_id - 2].set_username(command_word[i + 1]);
                    i++;
                }
                else if (command_word[i] == "password")
                {
                    user[user_id - 2].set_password(command_word[i + 1]);
                    i++;                
                }
                else if (command_word[i] == "email")
                {
                    user[user_id - 2].set_email(command_word[i + 1]);
                    i++;                
                }
                else if (command_word[i] == "age")
                {
                    user[user_id - 2].set_age(command_word[i + 1]);
                    i++;                
                }
                else if (command_word[i] == "publisher" || command_word[i] == "[publisher")
                {
                    if (command_word[i + 1] == "true")
                        user[user_id - 2].set_publisher(true);
                    else
                        user[user_id - 2].set_publisher(true);  
                    i++;                
                }
                // else
                //     throw BadCommand();
            } 
        }
        else if (command_word[1] == "replies")
        {
            user.push_back(User(user_id));
            user_id++;
            for (int i = 3; i < command_word.size(); i++)
            {
                if (command_word[i] == "username")
                {
                    user[user_id - 2].set_username(command_word[i + 1]);
                    i++;
                }
                else if (command_word[i] == "password")
                {
                    user[user_id - 2].set_password(command_word[i + 1]);
                    i++;                
                }
                else if (command_word[i] == "email")
                {
                    user[user_id - 2].set_email(command_word[i + 1]);
                    i++;                
                }
                else if (command_word[i] == "age")
                {
                    user[user_id - 2].set_age(command_word[i + 1]);
                    i++;                
                }
                else if (command_word[i] == "publisher" || command_word[i] == "[publisher")
                {
                    if (command_word[i + 1] == "true")
                        user[user_id - 2].set_publisher(true);
                    else
                        user[user_id - 2].set_publisher(true);  
                    i++;                
                }
                // else
                //     throw BadCommand();
            } 
        }
        else if (command_word[1] == "followers")
        {
            user.push_back(User(user_id));
            user_id++;
            for (int i = 3; i < command_word.size(); i++)
            {
                if (command_word[i] == "username")
                {
                    user[user_id - 2].set_username(command_word[i + 1]);
                    i++;
                }
                else if (command_word[i] == "password")
                {
                    user[user_id - 2].set_password(command_word[i + 1]);
                    i++;                
                }
                else if (command_word[i] == "email")
                {
                    user[user_id - 2].set_email(command_word[i + 1]);
                    i++;                
                }
                else if (command_word[i] == "age")
                {
                    user[user_id - 2].set_age(command_word[i + 1]);
                    i++;                
                }
                else if (command_word[i] == "publisher" || command_word[i] == "[publisher")
                {
                    if (command_word[i + 1] == "true")
                        user[user_id - 2].set_publisher(true);
                    else
                        user[user_id - 2].set_publisher(true);  
                    i++;                
                }
                // else
                //     throw BadCommand();
            } 
        }
        else if (command_word[1] == "buy")
        {
            user.push_back(User(user_id));
            user_id++;
            for (int i = 3; i < command_word.size(); i++)
            {
                if (command_word[i] == "username")
                {
                    user[user_id - 2].set_username(command_word[i + 1]);
                    i++;
                }
                else if (command_word[i] == "password")
                {
                    user[user_id - 2].set_password(command_word[i + 1]);
                    i++;                
                }
                else if (command_word[i] == "email")
                {
                    user[user_id - 2].set_email(command_word[i + 1]);
                    i++;                
                }
                else if (command_word[i] == "age")
                {
                    user[user_id - 2].set_age(command_word[i + 1]);
                    i++;                
                }
                else if (command_word[i] == "publisher" || command_word[i] == "[publisher")
                {
                    if (command_word[i + 1] == "true" || command_word[i + 1] == "true]")
                        user[user_id - 2].set_publisher(true);
                    else
                        user[user_id - 2].set_publisher(true);  
                    i++;                
                }
                // else
                //     throw BadCommand();
            } 
        }
        else if (command_word[1] == "rate")
        {
            user.push_back(User(user_id));
            user_id++;
            for (int i = 3; i < command_word.size(); i++)
            {
                if (command_word[i] == "username")
                {
                    user[user_id - 2].set_username(command_word[i + 1]);
                    i++;
                }
                else if (command_word[i] == "password")
                {
                    user[user_id - 2].set_password(command_word[i + 1]);
                    i++;                
                }
                else if (command_word[i] == "email")
                {
                    user[user_id - 2].set_email(command_word[i + 1]);
                    i++;                
                }
                else if (command_word[i] == "age")
                {
                    user[user_id - 2].set_age(command_word[i + 1]);
                    i++;                
                }
                else if (command_word[i] == "publisher" || command_word[i] == "[publisher")
                {
                    if (command_word[i + 1] == "true")
                        user[user_id - 2].set_publisher(true);
                    else
                        user[user_id - 2].set_publisher(true);  
                    i++;                
                }
                // else
                //     throw BadCommand();
            } 
        }
        else if (command_word[1] == "comments")
        {
            user.push_back(User(user_id));
            user_id++;
            for (int i = 3; i < command_word.size(); i++)
            {
                if (command_word[i] == "username")
                {
                    user[user_id - 2].set_username(command_word[i + 1]);
                    i++;
                }
                else if (command_word[i] == "password")
                {
                    user[user_id - 2].set_password(command_word[i + 1]);
                    i++;                
                }
                else if (command_word[i] == "email")
                {
                    user[user_id - 2].set_email(command_word[i + 1]);
                    i++;                
                }
                else if (command_word[i] == "age")
                {
                    user[user_id - 2].set_age(command_word[i + 1]);
                    i++;                
                }
                else if (command_word[i] == "publisher" || command_word[i] == "[publisher")
                {
                    if (command_word[i + 1] == "true")
                        user[user_id - 2].set_publisher(true);
                    else
                        user[user_id - 2].set_publisher(true);  
                    i++;                
                }
                // else
                //     throw BadCommand();
            } 
        }
        else
            throw BadCommand();
    }
    else if (command_word[0] == "PUT")
    {
        if (command_word[1] == "films")
        {
            user.push_back(User(user_id));
            user_id++;
            for (int i = 3; i < command_word.size(); i++)
            {
                if (command_word[i] == "username")
                {
                    user[user_id - 2].set_username(command_word[i + 1]);
                    i++;
                }
                else if (command_word[i] == "password")
                {
                    user[user_id - 2].set_password(command_word[i + 1]);
                    i++;                
                }
                else if (command_word[i] == "email")
                {
                    user[user_id - 2].set_email(command_word[i + 1]);
                    i++;                
                }
                else if (command_word[i] == "age")
                {
                    user[user_id - 2].set_age(command_word[i + 1]);
                    i++;                
                }
                else if (command_word[i] == "publisher" || command_word[i] == "[publisher")
                {
                    if (command_word[i + 1] == "true")
                        user[user_id - 2].set_publisher(true);
                    else
                        user[user_id - 2].set_publisher(true);  
                    i++;                
                }
                else
                    throw BadCommand();
            } 
        }
        else
            throw WrongInput();
    }
    else if (command_word[0] == "GET")
    {
        if (command_word[1] == "followers")
        {
            user.push_back(User(user_id));
            user_id++;
            for (int i = 3; i < command_word.size(); i++)
            {
                if (command_word[i] == "username")
                {
                    user[user_id - 2].set_username(command_word[i + 1]);
                    i++;
                }
                else if (command_word[i] == "password")
                {
                    user[user_id - 2].set_password(command_word[i + 1]);
                    i++;                
                }
                else if (command_word[i] == "email")
                {
                    user[user_id - 2].set_email(command_word[i + 1]);
                    i++;                
                }
                else if (command_word[i] == "age")
                {
                    user[user_id - 2].set_age(command_word[i + 1]);
                    i++;                
                }
                else if (command_word[i] == "publisher" || command_word[i] == "[publisher")
                {
                    if (command_word[i + 1] == "true")
                        user[user_id - 2].set_publisher(true);
                    else
                        user[user_id - 2].set_publisher(true);  
                    i++;                
                }
                else
                    throw BadCommand();
            } 
        }
        else if (command_word[1] == "published")
        {
            user.push_back(User(user_id));
            user_id++;
            for (int i = 3; i < command_word.size(); i++)
            {
                if (command_word[i] == "username")
                {
                    user[user_id - 2].set_username(command_word[i + 1]);
                    i++;
                }
                else if (command_word[i] == "password")
                {
                    user[user_id - 2].set_password(command_word[i + 1]);
                    i++;                
                }
                else if (command_word[i] == "email")
                {
                    user[user_id - 2].set_email(command_word[i + 1]);
                    i++;                
                }
                else if (command_word[i] == "age")
                {
                    user[user_id - 2].set_age(command_word[i + 1]);
                    i++;                
                }
                else if (command_word[i] == "publisher" || command_word[i] == "[publisher")
                {
                    if (command_word[i + 1] == "true")
                        user[user_id - 2].set_publisher(true);
                    else
                        user[user_id - 2].set_publisher(true);  
                    i++;                
                }
                else
                    throw BadCommand();
            } 
        }
        else if (command_word[1] == "films")
        {
            user.push_back(User(user_id));
            user_id++;
            for (int i = 3; i < command_word.size(); i++)
            {
                if (command_word[i] == "username")
                {
                    user[user_id - 2].set_username(command_word[i + 1]);
                    i++;
                }
                else if (command_word[i] == "password")
                {
                    user[user_id - 2].set_password(command_word[i + 1]);
                    i++;                
                }
                else if (command_word[i] == "email")
                {
                    user[user_id - 2].set_email(command_word[i + 1]);
                    i++;                
                }
                else if (command_word[i] == "age")
                {
                    user[user_id - 2].set_age(command_word[i + 1]);
                    i++;                
                }
                else if (command_word[i] == "publisher" || command_word[i] == "[publisher")
                {
                    if (command_word[i + 1] == "true")
                        user[user_id - 2].set_publisher(true);
                    else
                        user[user_id - 2].set_publisher(true);  
                    i++;                
                }
                else
                    throw BadCommand();
            } 
        }
        else if (command_word[1] == "purchased")
        {
            user.push_back(User(user_id));
            user_id++;
            for (int i = 3; i < command_word.size(); i++)
            {
                if (command_word[i] == "username")
                {
                    user[user_id - 2].set_username(command_word[i + 1]);
                    i++;
                }
                else if (command_word[i] == "password")
                {
                    user[user_id - 2].set_password(command_word[i + 1]);
                    i++;                
                }
                else if (command_word[i] == "email")
                {
                    user[user_id - 2].set_email(command_word[i + 1]);
                    i++;                
                }
                else if (command_word[i] == "age")
                {
                    user[user_id - 2].set_age(command_word[i + 1]);
                    i++;                
                }
                else if (command_word[i] == "publisher" || command_word[i] == "[publisher")
                {
                    if (command_word[i + 1] == "true")
                        user[user_id - 2].set_publisher(true);
                    else
                        user[user_id - 2].set_publisher(true);  
                    i++;                
                }
                else
                    throw BadCommand();
            } 
        }
        else if (command_word[1] == "notifications")
        {
            user.push_back(User(user_id));
            user_id++;
            for (int i = 3; i < command_word.size(); i++)
            {
                if (command_word[i] == "username")
                {
                    user[user_id - 2].set_username(command_word[i + 1]);
                    i++;
                }
                else if (command_word[i] == "password")
                {
                    user[user_id - 2].set_password(command_word[i + 1]);
                    i++;                
                }
                else if (command_word[i] == "email")
                {
                    user[user_id - 2].set_email(command_word[i + 1]);
                    i++;                
                }
                else if (command_word[i] == "age")
                {
                    user[user_id - 2].set_age(command_word[i + 1]);
                    i++;                
                }
                else if (command_word[i] == "publisher" || command_word[i] == "[publisher")
                {
                    if (command_word[i + 1] == "true")
                        user[user_id - 2].set_publisher(true);
                    else
                        user[user_id - 2].set_publisher(true);  
                    i++;                
                }
                else
                    throw BadCommand();
            } 
        }
        else if (command_word[1] == "followers")
        {
            user.push_back(User(user_id));
            user_id++;
            for (int i = 3; i < command_word.size(); i++)
            {
                if (command_word[i] == "username")
                {
                    user[user_id - 2].set_username(command_word[i + 1]);
                    i++;
                }
                else if (command_word[i] == "password")
                {
                    user[user_id - 2].set_password(command_word[i + 1]);
                    i++;                
                }
                else if (command_word[i] == "email")
                {
                    user[user_id - 2].set_email(command_word[i + 1]);
                    i++;                
                }
                else if (command_word[i] == "age")
                {
                    user[user_id - 2].set_age(command_word[i + 1]);
                    i++;                
                }
                else if (command_word[i] == "publisher" || command_word[i] == "[publisher")
                {
                    if (command_word[i + 1] == "true")
                        user[user_id - 2].set_publisher(true);
                    else
                        user[user_id - 2].set_publisher(true);  
                    i++;                
                }
                else
                    throw BadCommand();
            } 
        }
        else if (command_word[1] == "buy")
        {
            user.push_back(User(user_id));
            user_id++;
            for (int i = 3; i < command_word.size(); i++)
            {
                if (command_word[i] == "username")
                {
                    user[user_id - 2].set_username(command_word[i + 1]);
                    i++;
                }
                else if (command_word[i] == "password")
                {
                    user[user_id - 2].set_password(command_word[i + 1]);
                    i++;                
                }
                else if (command_word[i] == "email")
                {
                    user[user_id - 2].set_email(command_word[i + 1]);
                    i++;                
                }
                else if (command_word[i] == "age")
                {
                    user[user_id - 2].set_age(command_word[i + 1]);
                    i++;                
                }
                else if (command_word[i] == "publisher" || command_word[i] == "[publisher")
                {
                    if (command_word[i + 1] == "true")
                        user[user_id - 2].set_publisher(true);
                    else
                        user[user_id - 2].set_publisher(true);  
                    i++;
                }
                else
                    throw BadCommand();
            } 
        }
        else if (command_word[1] == "rate")
        {
            user.push_back(User(user_id));
            user_id++;
            for (int i = 3; i < command_word.size(); i++)
            {
                if (command_word[i] == "username")
                {
                    user[user_id - 2].set_username(command_word[i + 1]);
                    i++;
                }
                else if (command_word[i] == "password")
                {
                    user[user_id - 2].set_password(command_word[i + 1]);
                    i++;                
                }
                else if (command_word[i] == "email")
                {
                    user[user_id - 2].set_email(command_word[i + 1]);
                    i++;                
                }
                else if (command_word[i] == "age")
                {
                    user[user_id - 2].set_age(command_word[i + 1]);
                    i++;                
                }
                else if (command_word[i] == "publisher" || command_word[i] == "[publisher")
                {
                    if (command_word[i + 1] == "true")
                        user[user_id - 2].set_publisher(true);
                    else
                        user[user_id - 2].set_publisher(true);  
                    i++;                
                }
                else
                    throw BadCommand();
            } 
        }
        else if (command_word[1] == "comments")
        {
            user.push_back(User(user_id));
            user_id++;
            for (int i = 3; i < command_word.size(); i++)
            {
                if (command_word[i] == "username")
                {
                    user[user_id - 2].set_username(command_word[i + 1]);
                    i++;
                }
                else if (command_word[i] == "password")
                {
                    user[user_id - 2].set_password(command_word[i + 1]);
                    i++;                
                }
                else if (command_word[i] == "email")
                {
                    user[user_id - 2].set_email(command_word[i + 1]);
                    i++;                
                }
                else if (command_word[i] == "age")
                {
                    user[user_id - 2].set_age(command_word[i + 1]);
                    i++;
                }
                else if (command_word[i] == "publisher" || command_word[i] == "[publisher")
                {
                    if (command_word[i + 1] == "true")
                        user[user_id - 2].set_publisher(true);
                    else
                        user[user_id - 2].set_publisher(true);  
                    i++;                
                }
                else
                    throw BadCommand();
            } 
        }
        else
            throw WrongInput();
    }
    else if (command_word[0] == "DELETE")
    {
        if (command_word[1] == "films")
        {
            user.push_back(User(user_id));
            user_id++;
            for (int i = 3; i < command_word.size(); i++)
            {
                if (command_word[i] == "username")
                {
                    user[user_id - 2].set_username(command_word[i + 1]);
                    i++;
                }
                else if (command_word[i] == "password")
                {
                    user[user_id - 2].set_password(command_word[i + 1]);
                    i++;                
                }
                else if (command_word[i] == "email")
                {
                    user[user_id - 2].set_email(command_word[i + 1]);
                    i++;                
                }
                else if (command_word[i] == "age")
                {
                    user[user_id - 2].set_age(command_word[i + 1]);
                    i++;                
                }
                else if (command_word[i] == "publisher" || command_word[i] == "[publisher")
                {
                    if (command_word[i + 1] == "true")
                        user[user_id - 2].set_publisher(true);
                    else
                        user[user_id - 2].set_publisher(true);  
                    i++;                
                }
                else
                    throw BadCommand();
            } 
        }
        else if (command_word[1] == "comments")
        {
            user.push_back(User(user_id));
            user_id++;
            for (int i = 3; i < command_word.size(); i++)
            {
                if (command_word[i] == "username")
                {
                    user[user_id - 2].set_username(command_word[i + 1]);
                    i++;
                }
                else if (command_word[i] == "password")
                {
                    user[user_id - 2].set_password(command_word[i + 1]);
                    i++;                
                }
                else if (command_word[i] == "email")
                {
                    user[user_id - 2].set_email(command_word[i + 1]);
                    i++;                
                }
                else if (command_word[i] == "age")
                {
                    user[user_id - 2].set_age(command_word[i + 1]);
                    i++;                
                }
                else if (command_word[i] == "publisher" || command_word[i] == "[publisher")
                {
                    if (command_word[i + 1] == "true")
                        user[user_id - 2].set_publisher(true);
                    else
                        user[user_id - 2].set_publisher(true);  
                    i++;                
                }
                else
                    throw BadCommand();
            } 
        }
        else
            throw WrongInput();
    }
    else
        throw WrongInput();

}
void Interface::print_data()
{
    for (int i = 0; i < user.size(); i++)
    {
        cout << user[i].get_id() << endl;
        cout << user[i].get_username() << endl;
        cout << user[i].get_password() << endl;
        cout << user[i].get_email() << endl;
        cout << user[i].get_age() << endl;
        cout << (user[i].get_publisher() == false ? "false" : "true") << endl;
    }
    
}



int main()
{
    while (true)
    {
        try
        {
            Interface ui;
            ui.read_data();
            ui.set_data();
            ui.print_data();
        }
        catch(exception e)
        {
            std::cerr << e.what() << '\n';
        }
    }    
    
}

