#include "Film.h"

using namespace std;

Film::Film(int _id) { id = _id; }

void Film::set_name(std::string _name) { name = _name; }
void Film::set_year(std::string _year)
{
    if (std::stoi(_year) < 1)
        throw WrongInput();
    year = _year;
}
void Film::set_length(std::string _length)
{
    if (std::stoi(_length) < 1)
        throw WrongInput();
    length = _length;
}
void Film::set_price(std::string _price)
{
    if (std::stoi(_price) < 0)
        throw WrongInput();
    price = _price;
}
void Film::set_summary(std::string _summary) { summary = _summary; }
void Film::set_director(std::string _director) { director = _director; }
void Film::set_rate(int _rate)
{
    rate += _rate;
    if (rate > 10)
        rate = 10;    
}

int Film::get_id() { return id; }
std::string Film::get_name() { return name; }
std::string Film::get_year() { return year; }
std::string Film::get_length() { return length; }
std::string Film::get_price() { return price; }
std::string Film::get_summary() { return summary; }
std::string Film::get_director() { return director; }
int Film::get_rate() { return rate; }