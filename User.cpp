#include "User.h"

using namespace std;

User::User(int _id) { id = _id; }

void User::set_username(std::string _username) { username = _username; }
void User::set_password(std::string _password) { password = _password; }
void User::set_email(std::string _email)
{
    if (_email.find('@')==string::npos)
        throw WrongInput();
    email = _email;
}
void User::set_age(std::string _age)
{
    if (std::stoi(_age) < 1)
        throw WrongInput();
    age = _age;
}
void User::set_publisher(bool _publisher) { publisher = _publisher; }
void User::set_balance(int _amount)
{
    if (_amount < 1)
        throw WrongInput();
    balance += _amount;
}

int User::get_id() { return id; }
std::string User::get_username() { return username; }
std::string User::get_password() { return password; }
std::string User::get_email() { return email; }
std::string User::get_age() { return age; }
bool User::get_publisher() { return publisher; }