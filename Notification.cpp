#include "Notification.h"

using namespace std;

Notification::Notification(string _content, bool _seen = false)
{
    content = _content; 
    seen = _seen;
}
