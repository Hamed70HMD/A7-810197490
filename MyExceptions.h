#ifndef MYEXCEPTIONS_H
#define MYEXCEPTIONS_H

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <exception>

class BadCommand : public std::exception
{
public:
    virtual const char* what() const throw()
    {
        return "Not Found";
    }
};

class WrongInput : public std::exception
{
public:
    virtual const char* what() const throw()
    {
        return "Bad Request";
    }
};

class PermissionError : public std::exception
{
public:
    virtual const char* what() const throw()
    {
        return "Permission Denied";
    }
};

#endif
