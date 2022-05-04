#ifndef HEAP_H
#define HEAP_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define SIZE 32 // max size
#define MAX_SIZE 100 // max number of nodes in the heap

typedef unsigned int uint; // alias to unsigned integer
typedef struct bid Bid; // alias to bid structure
typedef struct heap Heap; // alias to heap

struct bid {
    float price;
    uint timestamp; // bid keys
    uint quantity;
    char customer_name[SIZE]; // bid value
};

struct heap {
    uint size; // total number of nodes in the tree
    uint min_price;
    Bid* arrBids[MAX_SIZE];
};


/**************************************
 * METHODS
 *************************************/ 

bool approxEqual(float x, float y) {
    float diff = x - y;
    diff = (diff < 0)?-diff:diff;
    return (diff < 1e-3);
}


uint getLeftChildIndex(const uint parent_index) {
    return (2 * parent_index + 1);
}

uint getRightChildIndex(const uint parent_index) {
    return (2 * parent_index + 2);
}

uint getParentIndex(const uint child_index) {
    return (child_index - 1)/2;
}

void swap(Heap* pQueue, uint a_index, uint b_index) {
    Bid* tmp = pQueue->arrBids[a_index];
    pQueue->arrBids[a_index] = pQueue->arrBids[b_index];
    pQueue->arrBids[b_index] = tmp;
}

Bid* initBid(uint price, uint timestamp, uint quantity, char* cust_name) {
    Bid* new_bid = (Bid*)malloc(sizeof(Bid));
    strcpy(new_bid->customer_name, cust_name);
    new_bid->price = price;
    new_bid->timestamp = timestamp;
    new_bid->quantity = quantity;
    return new_bid;
}

Heap* initHeap(void) {
    Heap* new_pqueue = (Heap*)malloc(sizeof(Heap));
    new_pqueue->size = 0;
    new_pqueue->min_price = 0;
    return new_pqueue;
}

bool isFull(Heap* pQueue) {
    return (pQueue->size == MAX_SIZE);
}

bool isEmpty(Heap* pQueue) {
    return (pQueue->size == 0);
}


void heapifyUtil(Heap* pQueue, uint start_index) {
    // propagate the smallest element to the top
    if(getLeftChildIndex(start_index) > pQueue->size && 
        getRightChildIndex(start_index) > pQueue->size)
        return;

    uint left_child_index = getLeftChildIndex(start_index);
    uint right_child_index = getRightChildIndex(start_index);
    uint max_entry_index = start_index;
    Bid* max_entry_bid = pQueue->arrBids[start_index];
    
    if(left_child_index <= pQueue->size &&
        pQueue->arrBids[left_child_index]->price >= max_entry_bid->price) {
        if(approxEqual(max_entry_bid->price, pQueue->arrBids[left_child_index]->price)) {
                if(pQueue->arrBids[left_child_index]->timestamp < max_entry_bid->timestamp) {
                    max_entry_bid = pQueue->arrBids[left_child_index];
                    max_entry_index = left_child_index;
                }
        }
        else {
            max_entry_bid = pQueue->arrBids[left_child_index];
            max_entry_index = left_child_index;
        }
    }

    if(right_child_index <= pQueue->size &&
        pQueue->arrBids[right_child_index]->price >= max_entry_bid->price) {
        if(approxEqual(max_entry_bid->price, pQueue->arrBids[right_child_index]->price)) {
                if(pQueue->arrBids[right_child_index]->timestamp < max_entry_bid->timestamp) {
                    max_entry_bid = pQueue->arrBids[right_child_index];
                    max_entry_index = right_child_index;
                }
        }
        else {
            max_entry_bid = pQueue->arrBids[right_child_index];
            max_entry_index = right_child_index;
        }
    }

    if(max_entry_index != start_index) {
        swap(pQueue, start_index, max_entry_index);
    }
}

void heapifyUp(Heap* pQueue) {
    for(uint i = (pQueue->size)/2; i > 0; --i) 
        heapifyUtil(pQueue, i);
}

void heapifyDown(Heap* pQueue) {
    for(uint i = 0; i < (pQueue->size)/2; ++i) 
        heapifyUtil(pQueue, i);
}

void insertBid(Heap* pQueue, Bid* entry) {
    if(pQueue->size == 0) {
        printf("Full Priority Queue!\n");
        return;
    }

    pQueue->arrBids[++pQueue->size] = entry;
    heapifyUp(pQueue);
}


Bid* removeMax(Heap* pQueue) { // return and remove entry with the maximum key
    if(pQueue->size == 0) {
        printf("Empty Priority Queue!\n");
        return NULL;
    }

    Bid* to_remove = pQueue->arrBids[0];
    if(to_remove->quantity > 1) 
        --pQueue->arrBids[0]->quantity; // if there are more than 1 item of the same type
    else { // only one entry of type present so delete and heapify
        pQueue->arrBids[0] = pQueue->arrBids[pQueue->size];
        --pQueue->size;
        heapifyDown(pQueue);
    }

    return to_remove;
}

Bid* getMax(Heap* pQueue) { // return entry with the maximum key
    if(pQueue->size != 0) 
        return *(pQueue->arrBids); 
    else {
        printf("empty Priority Queue! \n");
        return NULL;
    }
    // return (pQueue->arrBids)[0];
}

#endif // HEAP_H