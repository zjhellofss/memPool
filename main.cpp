#include <iostream>
#include "memHandler.h"

using std::cout;
using std::endl;


int __test()
{
    MemHandler *handler = MemHandler::get();
    int *val = static_cast<int *>(handler->allocMem(510));
    int *tmp = val;
    for (int i = 0; i < 4; ++i)
    {
        *(tmp + i) = 4;
    }
    handler->freeMem(val);
    //剩余个数应该为1
    return 0;
}
