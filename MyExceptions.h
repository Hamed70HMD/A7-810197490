#ifndef MYEXCEPTIONS_H
#define MYEXCEPTIONS_H

#include <iostream>
#include <exception>

class BadCommand : std::exception
{
public:
    virtual const char* what() const throw()
    {
        return "Not Found";
    }
};

class WrongInput : std::exception
{
public:
    virtual const char* what() const throw()
    {
        return "Bad Request";
    }
};

class PermissionError : std::exception
{
public:
    virtual const char* what() const throw()
    {
        return "Permission Denied";
    }
};

#endif
