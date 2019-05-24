#include "Interface.h"

using namespace std;

long long Interface::hash(string pass)
{
    const int mod = 1e9 + 7;
    long long ans = 0;
    for(int i = 0 ;i< pass.size();i++)
        ans = ((ans * 313) + pass[i]) % mod;
    return ans;
}
void Interface::read_data()
{
    getline(cin, command);
    istringstream iss(command);
    string sub;
    while (iss >> sub)
        command_word.push_back(sub);
}
void Interface::clear_commandword()
{
    command_word.clear();
}
void Interface::is_logedin()
{
    if (logedin_user_index < 0)
        throw PermissionError();
}
void Interface::is_publisher(int index)
{
    is_logedin();
    if (!(user[index].get_publisher()))
        throw PermissionError();
}
void Interface::check_user_exsitant(string username, string password)
{
    bool user_exists = false;
    for (int i = 0; i < user.size(); i++)
    {
        if(user[i].get_username() == username 
            && user[i].get_password() == password)
        {
            logedin_user_index = i;
            user_exists = true;
            break;
        }
    }
    if (!user_exists)
        throw WrongInput();
}
void Interface::check_user_exsitant(int user_id)
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
void Interface::find_film_index(vector<Film> film_vector, int film_id)
{
    for (int i = 0; i < film_vector.size(); i++)
    {
        if(film_vector[i].get_id() == film_id)
        {
            selected_film_index = i;
            break;
        }
    }
}
void Interface::find_logedin_user_index(int user_id)
{
    for (int i = 0; i < user.size(); i++)
    {
        if(user[i].get_id() == film_id)
        {
            logedin_user_index = i;
            break;
        }
    }
}
void Interface::check_film_exsitant(int film_id)
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
void Interface::check_user_film_exsitant(int user_index, int film_id)
{
    bool user_film_exists = false;
    for (int i = 0; i < (user[user_index].user_film).size(); i++)
    {
        if ((user[user_index].user_film)[i].get_id() == film_id)
        {
            selected_film_index = i;
            user_film_exists = true;
            break;
        }
    }
    if (!user_film_exists)
        throw PermissionError();
}
void Interface::check_user_film_comment_exsitant(int user_index, int film_id, int comment_id)
{
    bool user_film_comment_exists = false;
    for (int i = 0; i < (((user[user_index].user_film)[film_id - 1]).film_comment).size(); i++)
    {
        if (((((user[user_index].user_film)[film_id - 1]).film_comment)[i]).get_id() == comment_id)
        {
            user_film_comment_exists = true;
            break;
        }
    }
    if (!user_film_comment_exists)
        throw PermissionError();
}
void Interface::print_followers()
{
    cout << "List of Followers" << endl;
    cout << "#" << ". " << "User Id" << " | " << "User Username" << " | " << "User Email" << endl;
    for (int i = 0; i < (user[logedin_user_index].user_follower).size(); i++)
        cout << i + 1 << ". " << ((user[logedin_user_index].user_follower)[i])->get_id() << " | " << ((user[logedin_user_index].user_follower)[i])->get_username() 
             << " | " << ((user[logedin_user_index].user_follower)[i])->get_email() << endl;
}
void Interface::print_films(vector<Film> film_vector, string name = "", string min_rate = "0"
    , string min_year = "0", string price = "0", string max_year = "3000", string director = "")
{
    cout << "#" << ". " << "Film Id" << " | " << "Film name" << " | " << "Film Length" << " | " 
        << "Film price" << " | " << "Rate" << " | " << "Production Year" << " | " << "Film Director" << endl;
    for (int i = 0; i < film_vector.size(); i++)
    {
        if ((stoi(min_rate) <= film_vector[i].get_rate()) && (stoi(min_year) < stoi(film_vector[i].get_year()))
            && (stoi(max_year) > stoi(film_vector[i].get_year())) && (stoi(price) < stoi(film_vector[i].get_price())))
            {
            cout << i + 1 << ". " << film_vector[i].get_id() << " | " << film_vector[i].get_name() 
                 << " | " << film_vector[i].get_length() << " | " << film_vector[i].get_price()
                 << " | " << film_vector[i].get_rate() << " | " << film_vector[i].get_year()
                 << " | " << film_vector[i].get_director() << endl;
            }
    }      
}
void Interface::print_comments(Film film, vector<Comment> comment_vector)
{
    for (int i = 0; i < film.film_comment.size(); i++)
    {
        cout << comment_vector[i].get_id() << ". " << comment_vector[i].get_comment() << endl;
        for (int j = 0; j < comment_vector[i].get_reply_size(); j++)
            cout << comment_vector[i].get_reply(j) << endl;    
    }
}
void Interface::sortfilmsbyrate()
{
    for (int i = 0; i < film.size(); i++)
        film_byrate.push_back(film[i]);
    for (int i = 0; i < film_byrate.size(); i++)
        for (int j = i; j < film_byrate.size();j++)
        {
            if (film_byrate[i].get_rate() < film_byrate[j].get_rate())
            {
                Film temp = film_byrate[i];
                film_byrate[j] = film_byrate[i];
                film_byrate[j] = temp;
            }
            if (film_byrate[i].get_rate() == film_byrate[j].get_rate())
            {
                if (film_byrate[i].get_id() < film_byrate[j].get_id())
                {
                    Film temp = film_byrate[i];
                    film_byrate[j] = film_byrate[i];
                    film_byrate[j] = temp;
                }
                else
                {
                    Film temp = film_byrate[j];
                    film_byrate[i] = film_byrate[j];
                    film_byrate[i] = temp;
                }
            }
        }
}
void Interface::check_command()
{
    if (command_word[0] == "POST")
    {
        if (command_word[1] == "signup")
        {
            User newuser = User(user_id);
            for (int i = 3; i < command_word.size(); i += 2)
            {
                if (command_word[i] == "username")
                    newuser.set_username(command_word[i + 1]);
                else if (command_word[i] == "password")
                    newuser.set_password(to_string(hash(command_word[i + 1])));
                else if (command_word[i] == "email")
                    newuser.set_email(command_word[i + 1]);
                else if (command_word[i] == "age")
                    newuser.set_age(command_word[i + 1]);
                else if (command_word[i] == "publisher")
                    if (command_word[i + 1] == "true")
                        newuser.set_publisher(true);  
                else
                    throw BadCommand();
            }
            if (newuser.get_username() == "" || newuser.get_password() == "" 
                    || newuser.get_email() == "" || newuser.get_age() == "")
                throw WrongInput();
            user.push_back(newuser);
            logedin_user_index = user_id - 1;
            user_id++;
            cout << "OK" << endl;
        }
        else if (command_word[1] == "login")
        {
            string temp_username, temp_password;
            for (int i = 3; i < command_word.size(); i += 2)
            {
                if (command_word[i] == "username")
                    temp_username = command_word[i + 1];
                else if (command_word[i] == "password")
                    temp_password = to_string(hash(command_word[i + 1]));
                else
                    throw WrongInput();
            }
            check_user_exsitant(temp_username, temp_password);
            // for (int i = 0; i < user.size(); i++)
            // {
            //     if(user[i].get_username() == temp_username 
            //         && user[i].get_password() == temp_password)
            //     {
            //         logedin_user_index = i;
            //         break;
            //     }
            // }
            cout << "OK" << endl;
        }
        else if (command_word[1] == "films")
        {
            is_publisher(logedin_user_index);
            Film newfilm(film_id);
            newfilm.set_id(film_id);
            for (int i = 3; i < command_word.size(); i += 2)
            {
                if (command_word[i] == "name")
                    newfilm.set_name(command_word[i + 1]);
                else if (command_word[i] == "year")
                    newfilm.set_year(command_word[i + 1]);
                else if (command_word[i] == "length")
                    newfilm.set_length(command_word[i + 1]);
                else if (command_word[i] == "price")
                    newfilm.set_price(command_word[i + 1]);
                else if (command_word[i] == "summary")
                    newfilm.set_summary(command_word[i + 1]);
                else if (command_word[i] == "director")
                    newfilm.set_director(command_word[i + 1]);
                else
                    throw WrongInput();
            }
            if (newfilm.get_name() == "" || newfilm.get_year() == "" 
                    || newfilm.get_length() == "" || newfilm.get_price() == ""
                    || newfilm.get_summary() == "" || newfilm.get_director() == "")
                throw WrongInput();
            film.push_back(newfilm);            
            user[logedin_user_index].set_user_film_data(film[film_id - 1]);
            film_id++;
            // string noti = "Publisher " + user[logedin_user_index].get_username() + " with id " + to_string(user[logedin_user_index].get_id()) + "register new film";
            // for (int i = 0; i < user.size(); i++)
            // {
            //     //user[i].notification.push_back(noti);
            // }
            cout << "OK" << endl;
        }
        else if (command_word[1] == "money")//**********************************************************
        {
            if (command_word.size() == 2)
            {
                is_publisher(logedin_user_index);
            }
            else if (command_word[3] == "amount")
                user[logedin_user_index].set_balance(stoi(command_word[4]));
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
                    selected_film_index = stoi(command_word[i + 1]) - 1;
                    check_user_film_exsitant(logedin_user_index, selected_film_index + 1);                    
                }
                else if (command_word[i] == "comment_id")
                {
                    selected_comment_index = stoi(command_word[i + 1]) - 1;
                    check_user_film_comment_exsitant(logedin_user_index, selected_film_index + 1, selected_comment_index + 1);
                }
                else if (command_word[i] == "content")
                {
                    (((((user[logedin_user_index]).user_film)[selected_film_index]).film_comment)[selected_comment_index]).set_reply(command_word[i + 1]);
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
                followed_userid = stoi(command_word[4]);
            else
                throw BadCommand();
            check_user_exsitant(followed_userid);
            user[logedin_user_index].user_following.push_back(&user[followed_userid - 1]);
            cout << "OK" << endl;
        }
        else if (command_word[1] == "buy")//**********************************************************
        {
            int bought_filmid;
            if (command_word[3] == "film_id")
                bought_filmid = stoi(command_word[4]);
            else
                throw BadCommand();
            check_film_exsitant(bought_filmid);
            user[logedin_user_index].set_balance(-stoi(film[bought_filmid - 1].get_price()));
            network_cash += stoi(film[bought_filmid - 1].get_price());
            user[logedin_user_index].user_bought_film.push_back(film[bought_filmid - 1]);
            cout << "OK" << endl;
        }
        else if (command_word[1] == "rate")
        {
            int selected_filmid, score;
            for (int i = 3; i < command_word.size(); i += 2)
            {
                if (command_word[i] == "film_id")
                    selected_filmid = stoi(command_word[i + 1]);
                else if (command_word[i] == "score")
                    score = stoi(command_word[i + 1]);                    
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
            string content;
            for (int i = 3; i < command_word.size(); i += 2)
            {
                if (command_word[i] == "film_id")
                    selected_filmid = stoi(command_word[i + 1]);
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
            int selected_film_id;
            if (command_word[3] == "film_id")
                selected_film_id = stoi(command_word[4]);
            else
                throw WrongInput();
            check_user_film_exsitant(logedin_user_index, selected_film_id);
            for (int i = 5; i < command_word.size(); i += 2)
            {
                if (command_word[i] == "name")
                {
                    film[selected_film_index].set_name(command_word[i + 1]);
                    user[logedin_user_index].user_film[selected_film_index].set_name(command_word[i + 1]);
                }
                else if (command_word[i] == "year")
                {
                    film[selected_film_index].set_year(command_word[i + 1]);
                    user[logedin_user_index].user_film[selected_film_index].set_year(command_word[i + 1]);
                }
                else if (command_word[i] == "length")
                {
                    film[selected_film_index].set_length(command_word[i + 1]);
                    user[logedin_user_index].user_film[selected_film_index].set_length(command_word[i + 1]);
                }
                else if (command_word[i] == "summary")
                {
                    film[selected_film_index].set_summary(command_word[i + 1]);
                    user[logedin_user_index].user_film[selected_film_index].set_summary(command_word[i + 1]);
                }
                else if (command_word[i] == "director")
                {
                    film[selected_film_index].set_director(command_word[i + 1]);
                    user[logedin_user_index].user_film[selected_film_index].set_director(command_word[i + 1]);
                }
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
            print_followers();
        }
        else if (command_word[1] == "published")
        {
            is_publisher(logedin_user_index);
            string name = "", min_rate = "0", min_year = "0", price = "0", max_year = "3000", director = "";
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
            print_films(user[logedin_user_index].user_film, name, min_rate, min_year, price, max_year, director);
        }
        else if (command_word[1] == "films")
        {
            if (command_word.size() == 5)
            {
                int selected_film_index;
                if (command_word[3] == "film_id")
                    selected_film_index = stoi(command_word[4]) - 1;
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
                print_comments(film[selected_film_index], film[selected_film_index].film_comment);
                cout << endl << "Recommendation Film" << endl;
                sortfilmsbyrate();
                cout << "#" << ". " << "Film Id" << " | " << "Film name" << " | " << "Film Length" << " | " 
                    << "Film price" << " | " << "Rate" << " | " << "Production Year" << " | " << "Film Director" << endl;
                for (int i = 0; i < 4; i++)
                    cout << i + 1 << ". " << film_byrate[i].get_id() << " | " << film_byrate[i].get_name() 
                        << " | " << film_byrate[i].get_length() << " | " << film_byrate[i].get_price()
                        << " | " << film_byrate[i].get_rate() << " | " << film_byrate[i].get_year()
                        << " | " << film_byrate[i].get_director() << endl;
                film_byrate.clear();
            }
            else
            {
            string name = "", min_rate = "0", min_year = "0", price = "0", max_year = "3000", director = "";
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
            print_films(film, name, min_rate, min_year, price, max_year, director);
            }
        }
        else if (command_word[1] == "purchased")
        {
            string name = "", min_rate = "0", min_year = "0", price = "0", max_year = "3000", director = "";
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
            print_films(user[logedin_user_index].user_bought_film, name, min_rate, min_year, price, max_year, director);
        }
        else if (command_word[1] == "notifications")
        {
            if (command_word.size() == 2)
            {
                for (int i = (user[logedin_user_index].notification).size() - 1; i >= 0; i--)
                {
                    cout << i + 1 << ". " << /*(user[logedin_user_index].notification)[i] <<*/ endl;
                }
            }
            else
            {
                if (command_word[2] == "read" && command_word[4] == "limit")
                {
                    for (int i = (user[logedin_user_index].notification).size() - 1; i >= (user[logedin_user_index].notification).size() - stoi(command_word[5]); i--)
                    {
                        cout << i + 1 << ". " << /*(user[logedin_user_index].notification)[i] <<*/ endl;
                    }
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
            is_publisher(logedin_user_index);
            int selected_film_id;
            if (command_word[3] == "film_id")
                selected_film_id = stoi(command_word[4]) - 1;
            else
                throw WrongInput();
            check_user_film_exsitant(logedin_user_index, selected_film_id);
            find_film_index(film, selected_film_id);
            film.erase(film.begin() + selected_film_index);
            find_film_index(user[logedin_user_index].user_film, selected_film_id);
            user[logedin_user_index].user_film.erase(user[logedin_user_index].user_film.begin() + selected_film_index);
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
                    selected_film_index = stoi(command_word[i + 1]) - 1;
                    check_user_film_exsitant(logedin_user_index, selected_film_index + 1);
                }
                else if (command_word[i] == "comment_id")
                {
                    selected_comment_index = stoi(command_word[i + 1]) - 1;
                    check_user_film_comment_exsitant(logedin_user_index, selected_film_index + 1, selected_comment_index + 1);
                }
                else
                    throw BadCommand();
            }
            (((user[logedin_user_index].user_film)[selected_film_index]).film_comment).erase
            ((((user[logedin_user_index].user_film)[selected_film_index]).film_comment).begin() + selected_comment_index);
            cout << "OK" << endl;
        }
        else
            throw WrongInput();
    }
    else
        throw WrongInput();
    command_word.clear();
}