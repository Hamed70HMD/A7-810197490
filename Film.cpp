#include "Film.h"

Film::Film(int _id) : id(_id) {}

void Film::set_name(std::string _name) { name = _name; }
void Film::set_year(std::string _year) { year = _year; }
void Film::set_lenght(std::string _length) { lenght = _length; }
void Film::set_price(std::string _price) { price = _price; }
void Film::set_summary(std::string _summary) { summary = _summary; }
void Film::set_director(std::string _director) { director = _director; }

std::string Film::set_name() { return name; }
std::string Film::set_year() { return year; }
std::string Film::set_lenght() { return lenght; }
std::string Film::set_price() { return price; }
std::string Film::set_summary() { return summary; }
std::string Film::set_director() { return director; }