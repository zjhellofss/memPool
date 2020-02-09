#include <iostream>
#include "memHandler.h"

using std::cout;
using std::endl;


int __test1()
{

    auto t1 = std::chrono::high_resolution_clock::now();
    auto handler = MemHandler::get();
    char *arr[1000];
    for (int i = 0; i < 1000; ++i)
    {
        arr[i] = static_cast<char *>(handler->allocMem((i * 10 + rand()) % 4097 + 11));
        strcpy(arr[i], "hello world");
    }
    for (int i = 0; i < 1000; ++i)
    {
        cout << arr[i] << endl;
    }
    for (int i = 0; i < 1000; ++i)
    {
        if (arr[i])
        {
            //
            handler->freeMem(arr[i]);
        }
    }

    auto t2 = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1);
    cout << "用时: " << duration.count() << "ms" << endl;
    return 0;
}

int __test2()
{
    auto t1 = std::chrono::high_resolution_clock::now();
    char *arr[1000];
    for (int i = 0; i < 1000; ++i)
    {
        arr[i] = new char[(i * 10 + rand()) % 4097];
    }
    for (int i = 0; i < 1000; ++i)
    {
        if (arr[i])
        {
            //
            delete arr[i];
        }
    }
    auto t2 = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1);
    cout << "用时: " << duration.count() << "ms" << endl;
}

int __main2()
{
    __test1();
//    __test2();
    return 0;
}