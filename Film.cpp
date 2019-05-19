#include "Film.h"

Film::Film(int _id) : id(_id) {}

void Film::set_name(std::string _name) { name = _name; }
void Film::set_year(std::string _year) { year = _year; }
void Film::set_lenght(std::string _length) { lenght = _length; }
void Film::set_price(std::string _price) { price = _price; }
void Film::set_summary(std::string _summary) { summary = _summary; }
void Film::set_director(std::string _director) { director = _director; }

std::string Film::get_name() { return name; }
std::string Film::get_year() { return year; }
std::string Film::get_lenght() { return lenght; }
std::string Film::get_price() { return price; }
std::string Film::get_summary() { return summary; }
std::string Film::get_director() { return director; }