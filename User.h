#ifndef USER_H
#define USER_H

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <exception>

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

    std::vector<int> user_published_film;

    long long hash(std::string s);
};

#endif
