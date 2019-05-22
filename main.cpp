#include "MyExceptions.h"
#include "Film.h"
#include "User.h"
#include "Comment.h"
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <exception>

using namespace std;

class Interface
{
private:
    int user_id = 1;
    int film_id = 1;
    int comment_id = 1;
    int network_cash = 0;
    int logedin_user_index = -1;

    std::string command;
    std::vector<std::string> command_word;

    std::vector<User> user;
    std::vector<Film> film;
public:
    void read_data();
    void check_command();
    void print_data();
    void clear_commandword()
    {
        command_word.clear();
    }
    void is_publisher(int index);
    void check_user_exsitant(std::string username, std::string password)
    {
        bool user_exists = false;
        for (int i = 0; i < user.size(); i++)
        {
            if(user[i].get_username() == username 
                && user[i].get_password() == std::to_string(hash(password)))
            {
                user_exists = true;
                break;
            }
        }
        if (!user_exists)
            throw WrongInput();
    }
    void check_user_exsitant(int user_id)
    {
        bool user_exists = false;
        for (int i = 0; i < user.size(); i++)
        {
            if(user[i].get_id() == user_id)
            {
                user_exists = true;
                break;
            }
        }
        if (!user_exists)
        {
            command_word.clear();
            throw WrongInput();
        }
    }
    void check_film_exsitant(int film_id)
    {
        bool film_exists = false;
        for (int i = 0; i < film.size(); i++)
        {
            if(film[i].get_id() == film_id)
            {
                film_exists = true;
                break;
            }
        }
        if (!film_exists)
            throw WrongInput();
    }
    void check_user_film_exsitant(int user_index, int film_id)
    {
        bool user_film_exists = false;
        for (int i = 0; i < (user[user_index].user_film).size(); i++)
        {
            if ((user[user_index].user_film)[i]->get_id() == film_id)
            {
                user_film_exists = true;
                break;
            }
        }
        if (!user_film_exists)
        {
            command_word.clear();
            throw PermissionError();
        }
    }
    void check_user_film_comment_exsitant(int user_index, int film_id, int comment_id)
    {
        bool user_film_comment_exists = false;
        for (int i = 0; i < (((user[user_index].user_film)[film_id - 1])->film_comment).size(); i++)
        {
            if (((((user[user_index].user_film)[film_id - 1])->film_comment)[i]).get_id() == comment_id)
            {
                user_film_comment_exists = true;
                break;
            }
        }
        if (!user_film_comment_exists)
            throw PermissionError();
    }

    long long hash(std::string pass)
    {
        const int mod = 1e9 + 7;
        long long ans = 0;
        for(int i = 0 ;i< pass.size();i++)
            ans = ((ans * 313) + pass[i]) % mod;
        return ans;
    }
};
void Interface::is_publisher(int index)
{
    if (!(user[index].get_publisher()))
        throw PermissionError();
}
void Interface::read_data()
{
    getline(cin, command);
    istringstream iss(command);
    std::string sub;
    while (iss >> sub)
        command_word.push_back(sub);
}
void Interface::check_command()
{
    if (command_word[0] == "POST")
    {
        if (command_word[1] == "signup")
        {
            user.push_back(User(user_id));
            for (int i = 3; i < command_word.size(); i += 2)
            {
                if (command_word[i] == "username")
                    user[user_id - 1].set_username(command_word[i + 1]);
                else if (command_word[i] == "password")
                    user[user_id - 1].set_password(std::to_string(hash(command_word[i + 1])));
                else if (command_word[i] == "email")
                    user[user_id - 1].set_email(command_word[i + 1]);
                else if (command_word[i] == "age")
                    user[user_id - 1].set_age(command_word[i + 1]);
                else if (command_word[i] == "publisher")
                    if (command_word[i + 1] == "true")
                        user[user_id - 1].set_publisher(true);  
                else
                    throw BadCommand();
            }
            if (user[user_id - 1].get_username() == "" || user[user_id - 1].get_password() == "" 
                    || user[user_id - 1].get_email() == "" || user[user_id - 1].get_age() == "")
                throw WrongInput();
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
            for (int i = 3; i < command_word.size(); i += 2)
            {
                if (command_word[i] == "username")
                    temp_username = command_word[i + 1];
                else if (command_word[i] == "password")
                    temp_password = std::to_string(hash(command_word[i + 1]));
                else
                    throw WrongInput();
            }
            check_user_exsitant(temp_username, temp_password);
            for (int i = 0; i < user.size(); i++)
            {
                if(user[i].get_username() == temp_username 
                    && user[i].get_password() == std::to_string(hash(temp_password)))
                    logedin_user_index = i;
            }
            cout << "OK" << endl;
        }
        else if (command_word[1] == "films")
        {
            is_publisher(logedin_user_index);
            film.push_back(Film(film_id));
            for (int i = 3; i < command_word.size(); i += 2)
            {
                if (command_word[i] == "name")
                    film[film_id - 1].set_name(command_word[i + 1]);
                else if (command_word[i] == "year")
                    film[film_id - 1].set_year(command_word[i + 1]);
                else if (command_word[i] == "length")
                    film[film_id - 1].set_length(command_word[i + 1]);
                else if (command_word[i] == "price")
                    film[film_id - 1].set_price(command_word[i + 1]);
                else if (command_word[i] == "summary")
                    film[film_id - 1].set_summary(command_word[i + 1]);
                else if (command_word[i] == "director")
                    film[film_id - 1].set_director(command_word[i + 1]);
                else
                    throw BadCommand();
            }
            if (film[film_id - 1].get_name() == "" || film[film_id - 1].get_year() == "" 
                    || film[film_id - 1].get_length() == "" || film[film_id - 1].get_price() == ""
                    || film[film_id - 1].get_summary() == "" || film[film_id - 1].get_director() == "")
                throw WrongInput();
            else
            {
                (user[logedin_user_index].user_film).push_back(&film[film_id - 1]);
                film_id++;
                cout << "OK" << endl;
            }
        }
        else if (command_word[1] == "money")//**********************************************************
        {
            if (command_word.size() == 2)
            {
                is_publisher(logedin_user_index);
                /* code */
            }
            else if (command_word[3] == "amount")
            {
                user[logedin_user_index].set_balance(std::stoi(command_word[4]));
            }
            else
                throw BadCommand();
            cout << "OK" << endl;
        }
        else if (command_word[1] == "replies")
        {
            is_publisher(logedin_user_index);
            int selected_film_index, selected_comment_index;
            for (int i = 3; i < command_word.size(); i += 2)
            {
                if (command_word[i] == "film_id")
                {
                    selected_film_index = std::stoi(command_word[i + 1]) - 1;
                    check_user_film_exsitant(logedin_user_index, selected_film_index + 1);                    
                }
                else if (command_word[i] == "comment_id")
                {
                    selected_comment_index = std::stoi(command_word[i + 1]) - 1;
                    check_user_film_comment_exsitant(logedin_user_index, selected_film_index + 1, selected_comment_index + 1);
                }
                else if (command_word[i] == "content")
                {
                    (((((user[logedin_user_index]).user_film)[selected_film_index])->film_comment)[selected_comment_index]).set_reply(command_word[i + 1]);
                }
                else
                    throw BadCommand();
            }
            cout << "OK" << endl;
        }
        else if (command_word[1] == "followers")
        {
            int followed_userid;
            if (command_word[3] == "user_id")
                followed_userid = std::stoi(command_word[4]);
            else
                throw BadCommand();
            check_user_exsitant(followed_userid);
            user[logedin_user_index].user_following.push_back(&user[followed_userid - 1]);
            cout << "OK" << endl;
        }
        else if (command_word[1] == "buy")
        {
            int bought_filmid;
            if (command_word[3] == "film_id")
                bought_filmid = std::stoi(command_word[4]);
            else
                throw BadCommand();
            check_film_exsitant(bought_filmid);
            user[logedin_user_index].set_balance(-std::stoi(film[bought_filmid - 1].get_price()));
            network_cash += std::stoi(film[bought_filmid - 1].get_price());
            user[logedin_user_index].user_bought_film.push_back(film[bought_filmid - 1]);
            cout << "OK" << endl;
        }
        else if (command_word[1] == "rate")
        {
            int selected_filmid, score;
            for (int i = 3; i < command_word.size(); i += 2)
            {
                if (command_word[i] == "film_id")
                    selected_filmid = std::stoi(command_word[i + 1]);
                else if (command_word[i] == "score")
                    score = std::stoi(command_word[i + 1]);                    
                else
                    throw BadCommand();
            }
            check_film_exsitant(selected_filmid);
            film[selected_filmid - 1].set_rate(score);
            cout << "OK" << endl;
        }
        else if (command_word[1] == "comments")
        {
            int selected_filmid;
            std::string content;
            for (int i = 3; i < command_word.size(); i += 2)
            {
                if (command_word[i] == "film_id")
                    selected_filmid = std::stoi(command_word[i + 1]);
                else if (command_word[i] == "content")
                    content = command_word[i + 1];                    
                else
                    throw BadCommand();
            }
            check_film_exsitant(selected_filmid);
            film[selected_filmid - 1].film_comment.push_back(Comment(comment_id, content));
            comment_id++;
            cout << "OK" << endl;
        }
        else
            throw BadCommand();
    }
    else if (command_word[0] == "PUT")
    {
        if (command_word[1] == "films")
        {
            int selected_film_index;
            if (command_word[3] == "film_id")
                selected_film_index = std::stoi(command_word[4]) - 1;
            else
                throw WrongInput();
            check_user_film_exsitant(logedin_user_index, std::stoi(command_word[4]));
            for (int i = 5; i < command_word.size(); i += 2)
            {
                if (command_word[i] == "name")
                    film[selected_film_index].set_name(command_word[i + 1]);
                else if (command_word[i] == "year")
                    film[selected_film_index].set_year(command_word[i + 1]);
                else if (command_word[i] == "length")
                    film[selected_film_index].set_length(command_word[i + 1]);
                else if (command_word[i] == "summary")
                    film[selected_film_index].set_summary(command_word[i + 1]);
                else if (command_word[i] == "director")
                    film[selected_film_index].set_director(command_word[i + 1]);
                else
                    throw BadCommand();
            }
            cout << "OK" << endl;
        }
        else
            throw WrongInput();
    }
    else if (command_word[0] == "GET")
    {
        if (command_word[1] == "followers")
        {
            cout << "#" << ". " << "User Id" << " | " << "User Username" << " | " << "User Email" << endl;
            for (int i = 0; i < (user[logedin_user_index].user_follower).size(); i++)
            {
                cout << i + 1 << ". " << ((user[logedin_user_index].user_follower)[i])->get_id() << " | " << ((user[logedin_user_index].user_follower)[i])->get_username() 
                     << " | " << ((user[logedin_user_index].user_follower)[i])->get_email() << endl;
            }
        }
        else if (command_word[1] == "published")
        {
            is_publisher(logedin_user_index);
            std::string name, min_rate , min_year, price, max_year, director;
            for (int i = 3; i < command_word.size(); i += 2)
            {
                if (command_word[i] == "name")
                    name = command_word[i + 1];
                else if (command_word[i] == "min_rate")
                    min_rate = command_word[i + 1];
                else if (command_word[i] == "min_year")
                    min_year = command_word[i + 1];
                else if (command_word[i] == "price")
                    price = command_word[i + 1];
                else if (command_word[i] == "max_year")
                    max_year = command_word[i + 1];
                else if (command_word[i] == "director")
                    director = command_word[i + 1];
                else
                    throw BadCommand();
            }
            cout << "#" << ". " << "Film Id" << " | " << "Film name" << " | " << "Film Length" << " | " 
                << "Film price" << " | " << "Rate" << " | " << "Production Year" << " | " << " Film Director" << endl;
            for (int i = 0, n = 0; i < (user[logedin_user_index].user_film).size(); i++)
            {
                cout << n + 1 << ". " << ((user[logedin_user_index].user_film)[i])->get_id() << " | " << ((user[logedin_user_index].user_film)[i])->get_name() 
                     << " | " << ((user[logedin_user_index].user_film)[i])->get_length() << " | " << ((user[logedin_user_index].user_film)[i])->get_price()
                     << " | " << ((user[logedin_user_index].user_film)[i])->get_rate() << " | " << ((user[logedin_user_index].user_film)[i])->get_year()
                     << " | " << ((user[logedin_user_index].user_film)[i])->get_director() << endl;    
            }
        }
        else if (command_word[1] == "films")
        {
            if (command_word.size() == 5)
            {
                int selected_film_index;
                if (command_word[3] == "film_id")
                    selected_film_index = std::stoi(command_word[4]) - 1;
                else
                    throw WrongInput();
                check_film_exsitant(selected_film_index + 1);
                cout << "Details of Film " << film[selected_film_index].get_name() << endl;
                cout << "Id = " << film[selected_film_index].get_id() << endl;
                cout << "Director = " << film[selected_film_index].get_director() << endl;
                cout << "Length = " << film[selected_film_index].get_length() << endl;
                cout << "Year = " << film[selected_film_index].get_year() << endl;
                cout << "Summary = " << film[selected_film_index].get_summary() << endl;
                cout << "Rate = " << film[selected_film_index].get_rate() << endl;
                cout << "Price = " << film[selected_film_index].get_price() << endl;
                cout << endl << "Comments" << endl;
                for (int i = 0; i < film[selected_film_index].film_comment.size(); i++)
                {
                    cout << (film[selected_film_index].film_comment[i]).get_id() << ". " << (film[selected_film_index].film_comment[i]).get_comment() << endl;
                    for (int j = 0; j < (film[selected_film_index].film_comment[i]).get_reply_size(); j++)
                        cout << (film[selected_film_index].film_comment[i]).get_reply(j) << endl;    
                }
                cout << endl << "Recommendation Film" << endl;
                cout << "#" << ". " << "Film Id" << " | " << "Film Name" << " | " << "Film Length" << " | " << "Film Director" << endl;
                for (int i = 0; i < 4; i++)
                {
                    cout << "#" << ". " << "Film Id" << " | " << "Film Name" << " | " << "Film Length" << " | " << "Film Director" << endl;
                }          
            }
            else
            {
                std::string name, min_rate, min_year, price, max_year, director;
                for (int i = 3; i < command_word.size(); i += 2)
                {
                    if (command_word[i] == "name")
                        name = command_word[i + 1];
                    else if (command_word[i] == "min_rate")
                        min_rate = command_word[i + 1];
                    else if (command_word[i] == "min_year")
                        min_year = command_word[i + 1];
                    else if (command_word[i] == "price")
                        price = command_word[i + 1];
                    else if (command_word[i] == "max_year")
                        max_year = command_word[i + 1];
                    else if (command_word[i] == "director")
                        director = command_word[i + 1];
                    else
                        throw BadCommand();
                }
                cout << "#" << ". " << "Film Id" << " | " << "Film name" << " | " << "Film Length" << " | " 
                    << "Film price" << " | " << "Rate" << " | " << "Production Year" << " | " << " Film Director" << endl;
                for (int i = 0; i < film.size(); i++)
                {
                    cout << i + 1 << ". " << film[i].get_id() << " | " << film[i].get_name() 
                         << " | " << film[i].get_length() << " | " << film[i].get_price()
                         << " | " << film[i].get_rate() << " | " << film[i].get_year()
                         << " | " << film[i].get_director() << endl;    
                }
            }
        }
        else if (command_word[1] == "purchased")
        {
            for (int i = 3; i < command_word.size(); i += 2)
            {
                std::string name, price, min_year, max_year, director;
                if (command_word[i] == "name")
                {
                    name = command_word[i + 1];
                }
                else if (command_word[i] == "price")
                {
                    price = command_word[i + 1];
                }
                else if (command_word[i] == "min_year")
                {
                    min_year = command_word[i + 1];
                }
                else if (command_word[i] == "max_year")
                {
                    max_year = command_word[i + 1];
                }
                else if (command_word[i] == "director")
                {
                    director = command_word[i + 1];
                }
                else
                {
                    command_word.clear();
                    throw BadCommand();
                }
            }
            cout << "#" << ". " << "Film Id" << "  |  " << "Film name" << "  |  " << "Film Length" << "  |  " << "Film price" << "  |  " << "Rate" << "  |  " << "Production Year" << "  |  " << " Film Director" << endl;
            for (int i = 0, n = 0; i < (user[logedin_user_index].user_bought_film).size(); i++)
            {
                cout << n + 1 << ". " << ((user[logedin_user_index].user_bought_film)[i]).get_id() << "  |  " << ((user[logedin_user_index].user_bought_film)[i]).get_name() 
                     << "  |  " << ((user[logedin_user_index].user_bought_film)[i]).get_length() << "  |  " << ((user[logedin_user_index].user_bought_film)[i]).get_price()
                     << "  |  " << ((user[logedin_user_index].user_bought_film)[i]).get_rate() << "  |  " << ((user[logedin_user_index].user_bought_film)[i]).get_year()
                     << "  |  " << ((user[logedin_user_index].user_bought_film)[i]).get_director() << endl;    
            }
        }
        else if (command_word[1] == "notifications")
        {
            if (command_word.size() == 2)
            {
                for (int i = (user[logedin_user_index].notification).size() - 1; i >= 0; i--)
                {
                    cout << i + 1 << ". " << (user[logedin_user_index].notification)[i] << endl;
                }
            }
            else
            {
                if (command_word[2] == "read" && command_word[4] == "limit")
                {
                    for (int i = (user[logedin_user_index].notification).size() - 1; i >= (user[logedin_user_index].notification).size() - std::stoi(command_word[5]); i--)
                    {
                        cout << i + 1 << ". " << (user[logedin_user_index].notification)[i] << endl;
                    }
                }
                else
                {
                    command_word.clear();
                    throw BadCommand();
                }
            }
        }
        else
        {
            command_word.clear();
            throw WrongInput();
        }
    }
    else if (command_word[0] == "DELETE")
    {
        if (command_word[1] == "films")
        {
            is_publisher(logedin_user_index);
            int selected_film_index;
            if (command_word[3] == "film_id")
                selected_film_index = std::stoi(command_word[4]) - 1;
            else
                throw WrongInput();
            check_user_film_exsitant(logedin_user_index, selected_film_index + 1);
            film.erase(film.begin() + selected_film_index);
            cout << "OK" << endl;
        }
        else if (command_word[1] == "comments")
        {
            is_publisher(logedin_user_index);
            int selected_film_index, selected_comment_index;
            for (int i = 3; i < command_word.size(); i += 2)
            {
                if (command_word[i] == "film_id")
                {
                    selected_film_index = std::stoi(command_word[i + 1]) - 1;
                    check_user_film_exsitant(logedin_user_index, selected_film_index + 1);
                }
                else if (command_word[i] == "comment_id")
                {
                    selected_comment_index = std::stoi(command_word[i + 1]) - 1;
                    check_user_film_comment_exsitant(logedin_user_index, selected_film_index + 1, selected_comment_index + 1);
                }
                else
                    throw BadCommand();
            }
            (((user[logedin_user_index].user_film)[selected_film_index])->film_comment).erase
            ((((user[logedin_user_index].user_film)[selected_film_index])->film_comment).begin() + selected_comment_index);
            cout << "OK" << endl;
        }
        else
            throw WrongInput();
    }
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
    for (int i = 0; i < film.size(); i++)
    {
        cout << film[i].get_name() << endl;
        cout << film[i].get_year() << endl;
        cout << film[i].get_length() << endl;
        cout << film[i].get_price() << endl;
        cout << film[i].get_summary() << endl;
        cout << film[i].get_director() << endl;
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
            ui.check_command();
            // ui.print_data();
        }
        catch(exception &e)
        {
            ui.clear_commandword();
            std::cerr << e.what() << '\n';
        }
    }
}
/*
POST signup ? username Vahid password vahid email vahid@gmail.com age 10 

POST signup ? username Hamed_HMD password hamed email hamed@gmail.com age 20 publisher true

POST signup ? username Reza password reza email reza@gmail.com age 40 publisher true

POST login ? username Vahid password vahid

POST login ? username Hamed_HMD password hamed

POST login ? username Reza password reza

POST films ? name yahyahyah year 2005 length 120 price 12000 summary khafane director jamal

POST films ? name kharkari year 2018 length 60 price 5000 summary daghoone director karim

PUT films ? film_id 1 name areeeeeeeee

DELETE films ? film_id 1

*/