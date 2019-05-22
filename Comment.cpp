#include "Comment.h"

using namespace std;

Comment::Comment(int _id, std::string _comment)
{
    id = _id;
    comment = _comment;
}
    
void Comment::set_reply(std::string _reply)
{
    reply.push_back(_reply);
}
    

int Comment::get_id() { return id; }
std::string Comment::get_comment() { return comment; }
std::string Comment::get_reply(int index) { return reply[index]; }
int Comment::get_reply_size() { return reply.size(); }
