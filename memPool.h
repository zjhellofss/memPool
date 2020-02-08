//
// Created by fushenshen on 2020/2/8.
//

#ifndef MEMPOOL_MEMPOOL_H
#define MEMPOOL_MEMPOOL_H

#include <cstdio>

class MemBlock;

//内存池
class MemPool
{
public:
    MemPool() = delete;

    MemPool(size_t blockNum, size_t blockSize);


    void init();

    virtual ~MemPool();

    void *allocMem(size_t size);

    void freeMem(void *mem);

    size_t getBlockSize() const;

private:
    size_t blockNum = 0; //内存单元的数量
    size_t blockSize = 0;//内存单元的大小
    unsigned char *addr = nullptr;//内存池的指针
    MemBlock *cur = nullptr;

};

#endif //MEMPOOL_MEMPOOL_H
