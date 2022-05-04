/*

  Author: Josias Moukpe
  Email: jmoukpe2016@my.fit.edu
  Course: cse2010
  Section: 14 
  Description: System to manage financial bids

 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "Heap.h"
#include "Queries.h"
#include "TNList.h"

/*
  Description of the function, parameter, and return value (if any)
 */

int main(int argc, char** argv) {
  
  FILE* fp = fopen(argv[1], "r"); // pointer the input data and query files
  
  if(fp == NULL) { // exits with failure if program fails to open data file
    printf("\nError: failed to open input file.\n");
    exit(EXIT_FAILURE);
  }

  // Reading file inputs
  size_t len = 0; // keeps track of the length of the lines
  char* input_line = NULL;  // the input line charracter array  
  TNList* cmds = NULL;
  Heap* bids = initHeap();
 
  while(getline(&input_line, &len, fp) != EOF) {
    //printf("%s\n", input_line);
    cmds = parseWords(input_line);
    processQuery(bids, cmds);
  }
  
  fclose(fp);
  return EXIT_SUCCESS;
  
}

