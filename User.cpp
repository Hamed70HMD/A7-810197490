#include "User.h"

using namespace std;

User::User(int _id) { id = _id; }
void User::set_username(string _username) { username = _username; }
void User::set_password(string _password) { password = _password; }
void User::set_email(string _email) 
{
    if (_email.find('@')==string::npos || _email.find('.')==string::npos)
        throw WrongInput();
    email = _email;
}
void User::set_age(string _age)
{
    if (stoi(_age) < 1)
        throw WrongInput();
    age = _age;
}
void User::set_publisher(bool _publisher) { publisher = _publisher; }
void User::set_balance(int _amount)
{
    balance += _amount;
}
int User::get_id() { return id; }
int User::get_balance() { return balance; }
string User::get_username() { return username; }
string User::get_password() { return password; }
string User::get_email() { return email; }
string User::get_age() { return age; }
bool User::get_publisher() { return publisher; }

void User::set_user_film_data(Film film)
{
    user_film.push_back(Film(film.get_id()));
    user_film[film_index].set_name(film.get_name());
    user_film[film_index].set_year(film.get_year());
    user_film[film_index].set_length(film.get_length());
    user_film[film_index].set_price(film.get_price());
    user_film[film_index].set_summary(film.get_summary());
    user_film[film_index].set_director(film.get_director());
    film_index++;
}
