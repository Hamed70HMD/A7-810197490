#ifndef FILM_H
#define FILM_H

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <exception>

class Film
{
private:
    int id;
    std::string name = "";
    std::string year = "";
    std::string lenght = "";
    std::string price = "";
    std::string summary = "";
    std::string director = "";

public:
    Film(int _id);
    
    void set_name(std::string _name);
    void set_year(std::string _year);
    void set_lenght(std::string _length);
    void set_price(std::string _price);
    void set_summary(std::string _summary);
    void set_director(std::string _director);

    std::string set_name();
    std::string set_year();
    std::string set_lenght();
    std::string set_price();
    std::string set_summary();
    std::string set_director();
};


#endif
