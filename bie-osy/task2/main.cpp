#ifndef __PROGTEST__

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cstdint>
#include <cassert>
#include <cmath>
#include <iostream>

using namespace std;
#endif /* __PROGTEST__ */


struct Node {
    uint32_t size;
    bool isFull;
    Node *next;
    Node *prev;
};


void *heapStart;
void *heapEnd;
uint32_t heapSize;
uint32_t numAllocs;

const uint8_t blockCount = 27;
Node blocks[blockCount];
constexpr size_t NODE_SIZE = sizeof(Node);


void addBlock(Node *node) {
    
    uint32_t size = node->size;
    size_t i = 0;

    for (; size >>= 1 ;  ++i);
       
    i -= 5;
    
    node->prev = &blocks[i];
    node->next = blocks[i].next;
    blocks[i].next = blocks[i].next->prev = node;
    
}

void removeBlock(Node *node) {

    if (node) {
        node->next->prev = node->prev;
        node->prev->next = node->next;
    }
}

Node* getBlock(const uint32_t& size) {

    uint32_t sizeToFind = 1 << 5;

    for (; sizeToFind < size; sizeToFind <<= 1);

    size_t i = 0;
    for (; i < blockCount; ++i) {

        if (blocks[i].size >= sizeToFind && (&blocks[i] != blocks[i].next))
            break;
    }

    if (i < blockCount) {
        Node *node = blocks[i].next;
        removeBlock(node);

        while (node->size > sizeToFind) {
            uint32_t half = node->size >> 1;
            
            Node *new_node = reinterpret_cast<Node*>(reinterpret_cast<uint8_t*>(node) + half);
            new_node->size = half;
            addBlock(new_node);
            node->size = half;
        }
        return node;
    }
    return nullptr;
}

Node* getBuddy(Node *node) {
    auto buddyLoc = ((uint64_t)node - (uint64_t)heapStart) ^ node->size;

    auto *buddy = reinterpret_cast<Node*>(reinterpret_cast<uint8_t*>(heapStart) + buddyLoc);

    if (buddy >= heapStart &&
    buddy < heapEnd)
        return buddy;

    return nullptr;
}

int nearestPowerOfTwo(int n)
{
    int v = n;

    v--;
    v |= v >> 1;
    v |= v >> 2;
    v |= v >> 4;
    v |= v >> 8;
    v |= v >> 16;
    v++;

    v = v >> 1;

    return v;
}
bool isPowerOfTwo(uint32_t n)
{
   if(n==0)
   return false;
  
   return (ceil(log2(n)) == floor(log2(n)));
}


void HeapInit(void *memPool, int memSize) {

    heapSize = 32;
    
    while (heapSize << 1 <= (uint32_t) memSize)
        heapSize <<= 1;
    
    for (size_t i = 0; i < blockCount; ++i) {
        blocks[i].size = 1 << (i + 5);
        blocks[i].next = blocks[i].prev = &blocks[i];
    }

    heapStart = reinterpret_cast<uint32_t*> (memPool);


    Node *node = reinterpret_cast<Node *> (heapStart);
    node->size = heapSize;
    addBlock(node);
    
    auto sizeLeft = memSize - heapSize;
    auto newNodeSize = 0;
    auto prevNodeSize = node->size;
    while (sizeLeft >= 32) {
        if (isPowerOfTwo(sizeLeft)) {
            auto *new_node =  reinterpret_cast<Node *> (reinterpret_cast<uint8_t *>(heapStart) + prevNodeSize);
                new_node->size = sizeLeft;
                addBlock(new_node);
                heapSize += sizeLeft;
                break;

        } else {
            newNodeSize = nearestPowerOfTwo(sizeLeft);
            auto *new_node =  reinterpret_cast<Node *> (reinterpret_cast<uint8_t *>(heapStart) + prevNodeSize);
            new_node->size = newNodeSize;
            addBlock(new_node);
            prevNodeSize += newNodeSize;
            sizeLeft -= newNodeSize;
            heapSize += newNodeSize;
        }

    }
    
        heapEnd = reinterpret_cast<uint32_t*>(reinterpret_cast<uint8_t *>(heapStart) + heapSize);
    
}

void *HeapAlloc(int size) {

    if (size == 0)
        return nullptr;
    
    uint32_t blockSize = size + NODE_SIZE;
    Node *node = getBlock(blockSize);

    if (node) {
        node->isFull = true;
        numAllocs++;
        return reinterpret_cast<uint8_t*>(node) + NODE_SIZE;
    }

    return nullptr;
}


bool HeapFree(void *blk) {

    Node* node = reinterpret_cast<Node*>(
            reinterpret_cast<uint8_t*>(blk) - NODE_SIZE);

    if (blk >= heapStart && blk <= heapEnd) {
        if (node->isFull) {
            
            node->isFull = false;
            while (node->size < heapSize) {
               
                Node *buddy = getBuddy(node);

                if (!buddy)
                    break;
                if (buddy->size != node->size)
                    break;
                if (buddy->isFull)
                    break;

                removeBlock(buddy);

                if (buddy < node)
                    node = buddy;

                node->size <<= 1;
            }

            addBlock(node);
            numAllocs--;
            return true;
        }
    }
    return false;
}

void HeapDone(int *pendingBlk) {
    *pendingBlk = numAllocs;
    numAllocs = 0;
}

#ifndef __PROGTEST__

int main(void) {
    uint8_t *p0, *p1, *p2, *p3, *p4;
    int pendingBlk;
    static uint8_t memPool[3 * 1048576];


    HeapInit(memPool, 2097152);
    assert((p0 = (uint8_t *) HeapAlloc(512000)) != NULL);
    memset(p0, 0, 512000);
    assert((p1 = (uint8_t *) HeapAlloc(511000)) != NULL);
    memset(p1, 0, 511000);
    assert((p2 = (uint8_t *) HeapAlloc(26000)) != NULL);
    memset(p2, 0, 26000);
    HeapDone(&pendingBlk);
    assert(pendingBlk == 3);

    HeapInit(memPool, 2097152);
    assert((p0 = (uint8_t*)HeapAlloc(1000000)) != NULL);
    memset(p0, 0, 1000000);
    assert((p1 = (uint8_t*)HeapAlloc(250000)) != NULL);
    memset(p1, 0, 250000);
    assert((p2 = (uint8_t*)HeapAlloc(250000)) != NULL);
    memset(p2, 0, 250000);
    assert((p3 = (uint8_t*)HeapAlloc(250000)) != NULL);
    memset(p3, 0, 250000);
    assert((p4 = (uint8_t*)HeapAlloc(50000)) != NULL);
    memset(p4, 0, 50000);
    assert(HeapFree(p2));
    assert(HeapFree(p4));
    assert(HeapFree(p3));
    assert(HeapFree(p1));
    assert((p1 = (uint8_t *) HeapAlloc(500000)) != NULL);
    memset(p1, 0, 500000);
    assert(HeapFree(p0));
    assert(HeapFree(p1));
    HeapDone(&pendingBlk);
    assert(pendingBlk == 0);

     HeapInit(memPool, 2359296);
     assert((p0 = (uint8_t *)HeapAlloc(1000000)) != NULL);
     memset(p0, 0, 1000000);
     assert((p1 = (uint8_t *)HeapAlloc(500000)) != NULL);
     memset(p1, 0, 500000);
     assert((p2 = (uint8_t *)HeapAlloc(500000)) != NULL);
     memset(p2, 0, 500000);
     assert((p3 = (uint8_t *)HeapAlloc(500000)) == NULL);
     assert(HeapFree(p2));
     assert((p2 = (uint8_t *)HeapAlloc(300000)) != NULL);
     memset(p2, 0, 300000);
     assert(HeapFree(p0));
     assert(HeapFree(p1));
     HeapDone(&pendingBlk);
     assert(pendingBlk == 1);

     HeapInit(memPool, 2359296);
     assert((p0 = (uint8_t *)HeapAlloc(1000000)) != NULL);
     memset(p0, 0, 1000000);
     assert(!HeapFree(p0 + 1000));
     HeapDone(&pendingBlk);
     assert(pendingBlk == 1);

    return 0;
}

#endif /* __PROGTEST__ */
