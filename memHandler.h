//
// Created by fushenshen on 2020/2/8.
//

#ifndef MEMPOOL_MEMHANDLER_H
#define MEMPOOL_MEMHANDLER_H

#include <cstdio>
#include <vector>
#include "memPool.h"

class MemBlock;

//内存池的管理类
class MemHandler
{
public:
    virtual ~MemHandler();

    explicit MemHandler(int num);


    void *allocMem(size_t size);

    void freeMem(void *mem);

    static MemHandler *get();


private:
    void init(int num, int minSize, int maxSize);

private:
    int minSize;
    int maxSize;
    std::vector<MemPool *> poolVec;
    static MemHandler *memHandler;


};

#endif //MEMPOOL_MEMHANDLER_H
