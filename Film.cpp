#include "Film.h"

using namespace std;
 
Film::Film(int _id) { id = _id; }
void Film::set_id(int _id) { id = _id; }
void Film::set_publisherid(int _publisher_id) { publisher_id = _publisher_id; }
void Film::set_name(string _name) { name = _name; }
void Film::set_year(string _year)
{
    if (stoi(_year) < 1)
        throw WrongInput();
    year = _year;
}
void Film::set_length(string _length)
{
    if (stoi(_length) < 1)
        throw WrongInput();
    length = _length;
}
void Film::set_price(string _price)
{
    if (stoi(_price) < 0)
        throw WrongInput();
    price = _price;
}
void Film::set_summary(string _summary) { summary = _summary; }
void Film::set_director(string _director) { director = _director; }
void Film::set_rate(int _rate)
{
    rate += _rate;
    if (rate > 10)
        rate = 10;    
}
int Film::get_id() { return id; }
int Film::get_publisherid() { return publisher_id; }
string Film::get_name() { return name; }
string Film::get_year() { return year; }
string Film::get_length() { return length; }
string Film::get_price() { return price; }
string Film::get_summary() { return summary; }
string Film::get_director() { return director; }
int Film::get_rate() { return rate; }
