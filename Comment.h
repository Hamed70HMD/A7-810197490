#ifndef COMMENT_H
#define COMMENT_H

#include <iostream>
#include <string>
#include <vector>
#include <exception>

class Comment
{
private:
    int id;
    std::string comment;
    std::vector<std::string> reply;
public:
    Comment(int _id, std::string _comment);
    void set_reply(std::string _reply);
    int get_id();
    std::string get_comment();
    std::string get_reply(int index);
    int get_reply_size();
};

#endif 
