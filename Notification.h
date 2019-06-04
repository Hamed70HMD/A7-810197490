#ifndef NOTIFICATION_H
#define NOTIFICATION_H

#include <iostream>
#include <string>

class Notification
{
private:
    std::string content;
    bool seen;
public: 
    Notification(std::string _content, bool _seen);
};

#endif
