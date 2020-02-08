//
// Created by fushenshen on 2020/2/9.
//

#ifndef MEMPOOL_ALLOC_H
#define MEMPOOL_ALLOC_H

#include <cstdio>

void *operator new(size_t size);

void operator delete(void *mem);


#endif //MEMPOOL_ALLOC_H
