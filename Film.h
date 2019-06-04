#ifndef FILM_H
#define FILM_H
 
#include <iostream>
#include <string>
#include <vector>
#include <exception>
#include "MyExceptions.h"
#include "Comment.h"

class Film
{
private:
    int id;
    int publisher_id;
    std::string name = "";
    std::string year = "";
    std::string length = "";
    std::string price = "";
    std::string summary = "";
    std::string director = "";
    int rate = 0;
public:
    Film(int _id);
    void set_id(int _id);
    void set_publisherid(int _publisher_id);
    void set_name(std::string _name);
    void set_year(std::string _year);
    void set_length(std::string _length);
    void set_price(std::string _price);
    void set_summary(std::string _summary);
    void set_director(std::string _director);
    void set_rate(int _rate);
    int get_id();
    int get_publisherid();
    std::string get_name();
    std::string get_year();
    std::string get_length();
    std::string get_price();
    std::string get_summary();
    std::string get_director();
    int get_rate();
    std::vector<Comment> film_comment;
};

#endif
