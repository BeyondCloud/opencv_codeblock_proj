#ifndef KeyboardCtrl_H
#define KeyboardCtrl_H
#include "Filter.h"
using namespace std;
class KeyboardCtrl
{
    public:
        KeyboardCtrl(Filter &);
        bool listenKey();
        Filter filter;
};

#endif
