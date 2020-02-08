//
// Created by fushenshen on 2020/2/9.
//

#include "alloc.h"
#include "memHandler.h"

void *operator new(size_t size)
{
    MemHandler *handler = MemHandler::get();
    void *mem = handler->allocMem(size);
    assert(mem != nullptr);
    return mem;
}

void operator delete(void *mem)
{
    assert(mem != nullptr);
    MemHandler *handler = MemHandler::get();
    handler->freeMem(mem);
}