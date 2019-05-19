#include "User.h"

User::User(int _id) { id = _id; }

void User::set_username(std::string _username) { username = _username; }
void User::set_password(std::string _password) { password = std::to_string(hash(_password)); }
void User::set_email(std::string _email) { email = _email; }
void User::set_age(std::string _age) { age = _age; }
void User::set_publisher(bool _publisher) { publisher = _publisher; }

int User::get_id() { return id; }
std::string User::get_username() { return username; }
std::string User::get_password() { return password; }
std::string User::get_email() { return email; }
std::string User::get_age() { return age; }
bool User::get_publisher() { return publisher; }

long long User::hash(std::string pass)
{
    const int mod = 1e9 + 7;
    long long ans = 0;
    for(int i = 0 ;i< pass.size();i++)
        ans = ((ans * 313) + pass[i]) % mod;
    return ans;
}