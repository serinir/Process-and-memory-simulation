//
// Created by el_hazred on 28/11/18.
//

#ifndef MEMORY_FUNCTION_H
#define MEMORY_FUNCTION_H
#include <stdio.h>
#include <stdlib.h>
//---------DECLARATIONS DES STRUCTURES---------//
typedef struct partition
{
    int start;
    int size;
    char  state; // F pour libre "Free" ET U pour utilisé "Used"
}partition;
//liste chainée des partitions
typedef struct elmMemo//element du memoire
{
    partition data;
    struct elmMemo* next;
}elmMemo;
typedef elmMemo *Memo;

//structure proccessus
typedef struct process
{
    int id;
    int time;
    int delay;
}process;
//structure de l'element de la file
typedef struct elmFile
{
    process data;
    struct elmFile *next;
}elmFile;
//structure de la file
typedef struct File
{
    elementFile* h,t;
}File;
//----------PROTOTYPES DES FONCTIONS---------//
//FILE
void Enfiler(File *f,process x);
void Defiler(File *f,process *x);
int Filevide(File f);
elmFile Tetefile(file f);
//PILE
memo creat_Partitions(int nombre_de_partitions);
#endif //MEMORY_FUNCTION_H
