#ifndef NOTIFICATION_H
#define NOTIFICATION_H

#include "MyExceptions.h"
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <exception>

class Notification
{
private:
    std::string content;
    bool seen;
public:
    Comment(std::string _content, bool _seen = false);
};


#endif
