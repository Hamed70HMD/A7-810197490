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
    int film_id = 1;
    int logedin_user_index;
    std::string command;
    std::vector<std::string> command_word;
    std::vector<User> user;
    std::vector<Film> film;
public:
    void read_data();
    void set_data();
    void print_data();
    void print_users();
};

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
            user.push_back(User(user_id));
            for (int i = 3; i < command_word.size(); i += 2)
            {
                if (command_word[i] == "username")
                {
                    user[user_id - 1].set_username(command_word[i + 1]);
                }
                else if (command_word[i] == "password")
                {
                    user[user_id - 1].set_password(std::to_string(user[i].hash(command_word[i + 1])));
                }
                else if (command_word[i] == "email")
                {
                    user[user_id - 1].set_email(command_word[i + 1]);
                }
                else if (command_word[i] == "age")
                {
                    user[user_id - 1].set_age(command_word[i + 1]);
                }
                else if (command_word[i] == "publisher")
                {
                    if (command_word[i + 1] == "true")
                        user[user_id - 1].set_publisher(true);  
                }
                else
                {
                    throw BadCommand();
                }
            }
            if (user[user_id - 1].get_username() == "" || user[user_id - 1].get_password() == "" 
                    || user[user_id - 1].get_email() == "" || user[user_id - 1].get_age() == "")
            {
                throw WrongInput();
            }
            else
            {
                logedin_user_index = user_id - 1;
                user_id++;
                cout << "OK" << endl;
            }     
        }
        else if (command_word[1] == "login")
        {
            std::string temp_username, temp_password;
            for (int i = 3; i < 7; i += 2)
            {
                if (command_word[i] == "username")
                {
                    temp_username = command_word[i + 1];
                }
                else if (command_word[i] == "password")
                {
                    temp_password = std::to_string(user[i].hash(command_word[i + 1]));
                }
                else
                {
                    throw WrongInput();
                }
            }
            bool is_done = false;
            for (int i = 0; i < user.size(); i++)
            {
                if(user[i].get_username() == temp_username 
                    && user[i].get_password() == std::to_string(user[i].hash(temp_password)))
                {
                    logedin_user_index = i;
                    cout << "OK" << endl;
                    is_done = true;
                    break;
                }
            }
            if (!is_done)
            {
                throw WrongInput();
            }
        }
        else if (command_word[1] == "films")
        {
            film.push_back(Film(film_id));
            for (int i = 3; i < command_word.size(); i += 2)
            {
                if (command_word[i] == "name")
                {
                    film[film_id - 1].set_name(command_word[i + 1]);
                }
                else if (command_word[i] == "year")
                {
                    film[film_id - 1].set_year(command_word[i + 1]);
                }
                else if (command_word[i] == "lenght")
                {
                    film[film_id - 1].set_lenght(command_word[i + 1]);
                }
                else if (command_word[i] == "price")
                {
                    film[film_id - 1].set_price(command_word[i + 1]);
                }
                else if (command_word[i] == "summary")
                {
                    film[film_id - 1].set_summary(command_word[i + 1]);
                }
                else if (command_word[i] == "director")
                {
                    film[film_id - 1].set_director(command_word[i + 1]);
                }
                else
                {
                    throw BadCommand();
                }
            }
            if (user[film_id - 1].set_name() == "" || user[film_id - 1].set_year() == "" 
                    || user[film_id - 1].set_lenght() == "" || user[film_id - 1].set_price() == ""
                    || user[film_id - 1].set_summary() == "" || user[film_id - 1].set_director() == "")
            {
                throw WrongInput();
            }
            else
            {
                film_id++;
                cout << "OK" << endl;
            }
        }/*
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
    }*/
    else
        throw WrongInput();

    command_word.clear();
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
        cout << ((user[i].get_publisher() == false) ? "false" : "true") << endl;
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
            //ui.print_data();
        }
        catch(exception &e)
        {
            std::cerr << e.what() << '\n';
        }
    }
}
// POST signup ? username Vahid password vahid email vahid@gmail.com age 10 

// POST signup ? username Hamed_HMD password hamed email hamed@gmail.com age 20 publisher true

// POST login ? username Vahid password vahid