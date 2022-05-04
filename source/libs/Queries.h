#ifndef QUERIES_H
#define QUERIES_H 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "TNList.h"
#include "Heap.h"


/*******************************
 * METHODS
 ******************************/

void EnterBid(Heap* pQueue, uint time, char* name, float price, uint quantity) {
    Bid* new_bid = initBid(price, time, 1, name);
    insertBid(pQueue, new_bid);
}

void UpdateMinimumAcceptablePrice(Heap* pQueue, uint time, float price) {
    pQueue->min_price = price;
    printf("\n");
}

void SellOneItem(Heap* pQueue, uint time) {
    if(getMax(pQueue)->price >= pQueue->min_price) {
        Bid* tmp = removeMax(pQueue);
        printf("%s %0.2f\n", tmp->customer_name, tmp->price);
    }
    else {
        printf("HightestBiddingPriceIsToLow\n");
    }
}

void DisplayHighestBid(Heap* pQueue, uint time) {
    Bid* tmp = getMax(pQueue);
    printf("%s %d %0.2f %d\n", 
        tmp->customer_name,
        tmp->timestamp, 
        tmp->price, 
        tmp->quantity
        );
}

void processQuery(Heap* pQueue, TNList* query_list) {
    /*
    *   Executes the right query on the Taxonomy tree
    */ 

    if(!strcmp(getAt(query_list, 0), "UpdateMinimumAcceptablePrice")) {
        UpdateMinimumAcceptablePrice(pQueue, 
            atoi(getAt(query_list, 1)), 
            atof(getAt(query_list, 2))
            );
    }
    else 
    if(!strcmp(getAt(query_list, 0), "EnterBid")) {
        EnterBid(pQueue, 
            atoi(getAt(query_list, 1)), 
            getAt(query_list, 2), 
            atof(getAt(query_list, 3)), 
            atoi(getAt(query_list, 4))
            );
    }
    else 
    if(!strcmp(getAt(query_list, 0), "DisplayHighestBid")) {
        DisplayHighestBid(pQueue, atoi(getAt(query_list, 1)));
    }
    else 
    if(!strcmp(getAt(query_list, 0), "SellOneItem")) {
        SellOneItem(pQueue, atoi(getAt(query_list, 1)));
    }
    else printf("Invalid command!\n");
}

#endif // QUERIES_H