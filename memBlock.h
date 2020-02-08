//
// Created by fushenshen on 2020/2/8.
//

#ifndef MEMPOOL_MEMBLOCK_H
#define MEMPOOL_MEMBLOCK_H

class MemPool;

//内存池的块
class MemBlock
{
public:
    MemBlock();

    virtual ~MemBlock();

    void init(MemPool *pool);

    void init(MemPool *, int magicNumber);

    MemBlock *getNext() const;

    void setNext(MemBlock *next);

    void addRef();

    void recRef();

    int getId() const;

    int getSize() const;


private:
    //magic number
    int id;
    int refTime;//该内存块被引用的次数
    int size;//内存块的大小
    MemPool *pool;//所属的内存池
    MemBlock *next;
};

#endif //MEMPOOL_MEMBLOCK_H
