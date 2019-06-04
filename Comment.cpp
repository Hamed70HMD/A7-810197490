#include "Comment.h"

using namespace std;

Comment::Comment(int _id, string _comment)
{
    id = _id;
    comment = _comment;
}
void Comment::set_reply(string _reply)
{
    reply.push_back(_reply);
}
int Comment::get_id() { return id; }
string Comment::get_comment() { return comment; }
string Comment::get_reply(int index) { return reply[index]; }
int Comment::get_reply_size() { return reply.size(); }   
