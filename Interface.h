#ifndef INTERFACE_H
#define INTERFACE_H

#include "MyExceptions.h"
#include "User.h"
#include "Film.h"
#include "Comment.h"
#include "Notification.h"
#include <sstream>

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
    std::vector<Film> film_byrate;
public:
    void read_data();
    void check_command();
    void clear_commandword();
    void is_logedin();
    void is_publisher(int index);
    void check_user_exsitant(std::string username, std::string password);
    void check_user_exsitant(int user_id);
    void check_film_exsitant(int film_id);
    void check_user_film_exsitant(int user_index, int film_id);
    void check_user_film_comment_exsitant(int user_index, int film_id, int comment_id);
    long long hash(std::string pass);
    void print_followers();
    void print_films(std::vector<Film> film_vector, std::string name, std::string min_rate
        , std::string min_year, std::string price, std::string max_year, std::string director);
    void print_films(std::vector<Film*> film_vector, std::string name, std::string min_rate
        , std::string min_year, std::string price, std::string max_year, std::string director);
    void print_comments(Film film, std::vector<Comment> comment_vector);
    void sortfilmsbyrate();
};

#endif