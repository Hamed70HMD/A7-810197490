#include "MyExceptions.h"
#include "Film.h"
#include "User.h"
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <fstream>
#include <cstdlib>

using namespace std;

class Interface
{
private:
    int user_id = 1;
    int film_id;
    int logedin_user_index;
    std::string command;
    std::vector<std::string> command_word;
    std::vector<User*> user;
    std::vector<Film> film;
public:
    Interface();
    void read_data();
    void set_data();
    void print_data();
    void print_users();
    void set(int num){user_id = num;}
};

Interface::Interface()
{
    //  user_id = 1;
    //  film_id = 1;
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
    if (command_word[2] != "?")
    {
        throw BadCommand();
    }
    if (command_word[0] == "POST")
    {
        if (command_word[1] == "signup")
        {
            user.push_back(new User(user_id));
            logedin_user_index == user_id - 1;
            for (int i = 3; i < command_word.size(); i += 2)
            {
                if (command_word[i] == "username")
                {
                    user[user_id - 1]->set_username(command_word[i + 1]);
                }
                else if (command_word[i] == "password")
                {
                    user[user_id - 1]->set_password(command_word[i + 1]);
                }
                else if (command_word[i] == "email")
                {
                    user[user_id - 1]->set_email(command_word[i + 1]);
                }
                else if (command_word[i] == "age")
                {
                    user[user_id - 1]->set_age(command_word[i + 1]);
                }
                else if (command_word[i] == "publisher")
                {
                    if (command_word[i + 1] == "true")
                        user[user_id - 1]->set_publisher(true);
                    else
                        user[user_id - 1]->set_publisher(false);  
                }
                else
                {
                    cout << "ine1";
                    //throw BadCommand();
                }
            }
            if (user[user_id - 1]->get_username() == "" || user[user_id - 1]->get_password() == "" 
                    || user[user_id - 1]->get_email() == "" || user[user_id - 1]->get_age() == "")
            {
                cout << "ine2";
                throw WrongInput();
            }
            else
            {
                user_id++;
                cout << "OK" << endl;
            }     
        }/*
        else if (command_word[1] == "login")
        {
            std::string temp_username, temp_password;
            for (int i = 3; i < 7; i+=2)
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
            film.push_back(Film(film_id));
            for (int i = 3; i < command_word.size(); i++)
            {
                if (command_word[i] == "name")
                {
                    film[film_id - 1].set_name(command_word[i + 1]);
                    i++;
                }
                else if (command_word[i] == "year")
                {
                    film[film_id - 1].set_year(command_word[i + 1]);
                    i++;
                }
                else if (command_word[i] == "lenght")
                {
                    film[film_id - 1].set_lenght(command_word[i + 1]);
                    i++;                
                }
                else if (command_word[i] == "price")
                {
                    film[film_id - 1].set_price(command_word[i + 1]);
                    i++;
                }
                else if (command_word[i] == "summary")
                {
                    film[film_id - 1].set_summary(command_word[i + 1]);
                    i++;
                }
                else if (command_word[i] == "director")
                {
                    film[film_id - 1].set_director(command_word[i + 1]);
                    i++;
                }
                else
                {
                    cout << "second";
                    throw BadCommand();
                }
            }
            if (film[film_id - 1].set_name() == "" || film[film_id - 1].set_year() == "" 
                    || film[film_id - 1].set_lenght() == "" || film[film_id - 1].set_price() == ""
                    || film[film_id - 1].set_summary() == "" || film[film_id - 1].set_director() == "")
            {
                throw WrongInput();
            }
            else
            {
                film_id++;
                cout << "OK" << endl;
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
                else
                    throw BadCommand();
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
                    if (command_word[i + 1] == "true" || command_word[i + 1] == "true]")
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
        }*/
        else
        {
            cout << "ine3";
            throw BadCommand();
        }
    }/*
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
*/
}
void Interface::print_data()
{
    for (int i = 0; i < user.size(); i++)
    {
        cout << user[i]->get_username() << endl;
        cout << user[i]->get_password() << endl;
        cout << user[i]->get_email() << endl;
        cout << user[i]->get_age() << endl;
        cout << ((user[i]->get_publisher() == false) ? "false" : "true") << endl;
    } 
}



int main()
{
    Interface ui;
    while (true)
    {
        try
        {
            ui.read_data();
            ui.set_data();
            ui.print_data();
        }
        catch(exception &e)
        {
            std::cerr << e.what() << '\n';
        }
    }    
    
}

