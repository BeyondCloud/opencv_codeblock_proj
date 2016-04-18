#include "KeyboardCtrl.h"
#include "iostream"
#include <conio.h>
#include "Filter.h"

using namespace std;
KeyboardCtrl::KeyboardCtrl(Filter &src)
{
    filter = src;
    cout<<"How to use:"<<endl<<"Press e to exit";
}
bool KeyboardCtrl::listenKey()
{
        if (_kbhit() )
    {
        switch (_getch())
        {
            case 'e':
                return false;
            break;
            case 's':
                filter.setsubtract_tar();
            break;
        }
    }
    return true;
}

