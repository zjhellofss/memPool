//
// Created by fushenshen on 2020/2/8.
//

#include <cstdlib>
#include <cassert>
#include "memHandler.h"
#include "memBlock.h"

MemHandler::~MemHandler()
{
    for (int i = 0; i < this->poolVec.size(); ++i)
    {
        void *mem = this->poolVec[i];
        if (mem != nullptr)
        {
            free(mem);
            mem = nullptr;
        }
    }
}


MemHandler *MemHandler::memHandler = nullptr;

MemHandler *MemHandler::get()
{
    if (!MemHandler::memHandler)
    {
        MemHandler::memHandler = static_cast<MemHandler *>(malloc(sizeof(MemHandler)));
    }
    memHandler->init(5000, 8, 4096);
    return memHandler;
}


MemHandler::MemHandler(int num)
{

}

void *MemHandler::allocMem(size_t size)
{
    MemPool *curPool = nullptr;
    int len = this->poolVec.size();
    for (int i = 0; i < len; ++i)
    {
        if (this->poolVec[i]->getBlockSize() >= size)
        {
            void *mem = this->poolVec[i]->allocMem(size);
            assert(mem != nullptr);
            return mem;
        }
    }
    return malloc(size);
}

void MemHandler::freeMem(void *mem)
{
    auto *block = reinterpret_cast<MemBlock *>((unsigned char *) mem - sizeof(MemBlock));
    int magicId = block->getId();
    if (magicId != 0x4d716 && magicId != 0xea9f2)
    {
        free(mem);
    }
    else
    {
        int size = block->getSize();
        int len = this->poolVec.size();
        for (int i = 0; i < len; ++i)
        {
            if (this->poolVec[i]->getBlockSize() >= size)
            {
                this->poolVec[i]->freeMem(mem);
                break;
            }
        }
    }
}

void MemHandler::init(int num, int minSize, int maxSize)
{
    this->minSize = minSize;
    this->maxSize = maxSize;
    std::vector<int> tmp;

    for (int i = minSize; i < maxSize; i *= 2)
    {
        auto *pool = static_cast<MemPool *>(malloc(sizeof(MemPool)));
        pool->setBlockNum(num);
        pool->setBlockSize(i);
        this->poolVec.push_back(pool);
    }
}


