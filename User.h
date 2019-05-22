#ifndef USER_H
#define USER_H

#include <iostream>
#include <string>
#include <vector>
#include "MyExceptions.h"
#include "Film.h"


class User
{
private:
    int id;
    std::string username = "";
    std::string password = "";
    std::string email = "";
    std::string age = "";
    bool publisher = false;
    int balance = 0;

public:
    User(int _id);
    
    void set_username(std::string _username);
    void set_password(std::string _password);
    void set_email(std::string _email);
    void set_age(std::string _age);
    void set_publisher(bool _publisher);
    void set_balance(int _amount);

    int get_id();
    std::string get_username();
    std::string get_password();
    std::string get_email();
    std::string get_age();
    bool get_publisher();
    
    std::vector<Film*> user_film;
    std::vector<User*> user_follower;
    std::vector<User*> user_following;
    std::vector<Film> user_bought_film;
    std::vector<std::string> notification;
};

#endif
