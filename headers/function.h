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

}partition;
//liste chainée des partitions
typedef struct element
{
    partition data;
    struct element* next;
}element;

typedef element *liste;
//structure proccessus
typedef struct process
{
    int id;
    int time;
    int delay;
}process;
//structure de l'element de la file
typedef struct elementFile
{
    process data;
    struct elementFile *next;
}elementFile;
//structure de la file
typedef struct File
{
    elementFile* h,t;
}File;

#endif //MEMORY_FUNCTION_H
