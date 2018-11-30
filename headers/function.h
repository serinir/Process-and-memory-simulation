//
// Created by el_hazred on 28/11/18.
//

#ifndef MEMORY_FUNCTION_H
#define MEMORY_FUNCTION_H
#include <stdio.h>
#include <stdlib.h>
typedef struct partition
{
    int start;
    int size;
    char  state; // F pour libre "Free" ET U pour utilisé "Used"
    struct partition *next;
}partition;

typedef struct process
{
    int id;
    int time;
    int delay;
    int size;
    struct process *next;
}process;


typedef struct File
{
    process* h,t;
}File;

#endif //MEMORY_FUNCTION_H
