#include "MyExceptions.h"
#include "Film.h"
#include "User.h"
#include "Comment.h"
#include "Interface.h"

using namespace std;

int main()
{
    Interface ui;
    while (true)
    {
        try
        {
            ui.read_data();
            ui.check_command();
        }
        catch(exception &e)
        {
            ui.clear_commandword();
            std::cerr << e.what() << '\n';
        }
    }
}