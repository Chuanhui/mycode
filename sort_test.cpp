/*
 * (C) 2007-2010 Taobao Inc.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 *
 *
 * Version: 0.1: sort_test.cpp,v 0.1 2012/05/12 16:15:03 chuanhui Exp $
 *
 * Authors:
 *   chuanhui <rizhao.ych@taobao.com>
 *     - some work details if you want
 *
 */
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "sorter.h"

#define int_type int32_t
//#define int_type int64_t;
#define NUM (250L * 1000L * 1000L)
inline int compare (const void * a, const void * b){
  return ( *(int_type*)a - *(int_type*)b );
}

int main (void){
  int i;
  int_type data;
  double duration;
  clock_t start, finish;
  srand((unsigned int)time(0));
  int_type* store = new int_type[NUM];
  for (i = 0; i != NUM; i++){
    data = rand();
    store[i] = data;
  }
  start = clock();
  //qsort(store, NUM, sizeof(int_type) ,compare);
  //std::sort(store, store + NUM);
  sorter_t<int_type> sorter;
  sorter.qsort(store, store + NUM);
  finish = clock();
  duration = (double)(finish - start) / CLOCKS_PER_SEC;
  fprintf(stderr, "duration:%lf\n", duration);
  //cout << "duration:" << duration << endl;
  delete[] store;
  return 0;
}


