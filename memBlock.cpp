//
// Created by fushenshen on 2020/2/8.
//

#include <cassert>
#include "memBlock.h"
#include "memPool.h"

MemBlock::MemBlock()
{}

MemBlock::~MemBlock()
{

}

void MemBlock::init(MemPool *pool)
{
    //magic number
    this->id = 0x4d716;
    this->refTime = 0;
    this->pool = pool;
    this->next = nullptr;
    this->size = pool->getBlockSize();
}

MemBlock *MemBlock::getNext() const
{
    return next;
}

void MemBlock::setNext(MemBlock *next)
{
    MemBlock::next = next;
}

void MemBlock::addRef()
{
    this->refTime += 1;
}

int MemBlock::getId() const
{
    return id;
}

void MemBlock::recRef()
{
    assert(this->refTime > 0);
    this->refTime--;
}

void MemBlock::init(MemPool *memPool, int magicNumber)
{
    this->init(memPool);
    this->id = magicNumber;
}

int MemBlock::getSize() const
{
    return size;
}
