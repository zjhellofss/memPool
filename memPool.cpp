//
// Created by fushenshen on 2020/2/8.
//

#include <cstdlib>
#include <cassert>
#include <iostream>
#include "memPool.h"
#include "memBlock.h"

#include <mutex>

std::mutex addrLock;

MemPool::MemPool(size_t blockNum, size_t blockSize) : blockNum(blockNum), blockSize(blockSize)
{


}

MemPool::~MemPool()
{
    if (this->addr != nullptr)
    {
        delete this->addr;
        this->addr = nullptr;
    }
}

void MemPool::init()
{
    if (this->addr)
    {
        return;
    }
    //blockSize的大小为可用内存+memBlock之和
    size_t bufSize = this->blockNum * (sizeof(MemBlock) + this->blockSize);
    this->addr = static_cast<unsigned char *>(malloc(bufSize));
    this->cur = reinterpret_cast<MemBlock *>(this->addr);
    this->cur->init(this);
    //串联为一个链表
    MemBlock *tmpBlock = this->cur;
    addrLock.lock();
    for (int i = 0; i < this->blockNum - 1; ++i)
    {
        //blockSize 为内存池每个格子的大小
        auto *nextTmp = reinterpret_cast<MemBlock *>((unsigned char *) tmpBlock +
                                                     (this->blockSize + sizeof(MemBlock)));
        nextTmp->init(this);
        tmpBlock->setNext(nextTmp);
        tmpBlock = nextTmp;
    }
    //设置尾哨兵
    if (tmpBlock != nullptr)
    {
        tmpBlock->setNext(nullptr);
    }
    addrLock.unlock();
}


void *MemPool::allocMem(size_t size)
{
    if (!this->addr)
    {
        this->init();
    }
    MemBlock *mem = nullptr;
    if (!this->cur)
    {
        mem = static_cast<MemBlock *>(malloc(sizeof(MemBlock) + size));
        assert(mem != nullptr);
        //标注系统不做管理的内存
        mem->init(this, 0xea9f2);
    }
    else
    {
        addrLock.lock();
        //返回头部
        mem = this->cur;
        //头部指向下一个位置
        this->cur = this->cur->getNext();
        addrLock.unlock();
        mem->init(this);
        mem->addRef();//引用次数加1
    }
    return (unsigned char *) mem + sizeof(MemBlock);
}

void MemPool::freeMem(void *mem)
{
    assert(mem != nullptr);
    auto *block = reinterpret_cast<MemBlock *>((unsigned char *) mem - sizeof(MemBlock));
    int id = block->getId();
    switch (id)
    {
        case 0x4d716:
        {
            //还回到内存池中
            block->recRef();
            block->setNext(this->cur);
            this->cur = block;
            break;
        }

        case 0xea9f2:
        {
            free(block);
            break;
        }
        default:
        {
            //trigger a fatal error
            assert(1 == 0);
            break;
        }
    }

}

size_t MemPool::getBlockSize() const
{
    return blockSize;
}

size_t MemPool::getBlockNum() const
{
    return blockNum;
}

void MemPool::setBlockNum(size_t blockNum)
{
    MemPool::blockNum = blockNum;
}

void MemPool::setBlockSize(size_t blockSize)
{
    MemPool::blockSize = blockSize;
}





