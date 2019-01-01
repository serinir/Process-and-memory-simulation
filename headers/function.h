//
// Created by el_hazred on 28/11/18.
//

#ifndef MEMORY_FUNCTION_H
#define MEMORY_FUNCTION_H
#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include <time.h>

//---------DECLARATIONS DES STRUCTURES---------//
//structure proccessus
typedef struct process
{
    int id;
    int time;
    int delay;
    int size;
}process;
typedef struct partition
{
    process proc;
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


//structure de l'element de la file
typedef struct elmFile
{
    process data;
    struct elmFile *next;
}elmFile;
//structure de la file
typedef struct File
{
    elmFile *h,*t;
}File;
//tructure element de pile
typedef struct elmPile{
  File f;
  struct elmPile *suiv;
}elmPile;
typedef elmPile *Pile;

//----------PROTOTYPES DES FONCTIONS---------//
//FILE
void Enfiler(File *f,process x);
process Defiler(File *f);
int Filevide(File f);
process Tetefile(File f);
void Mettre_on_queue(File *f);
File Creat_File(FILE *h);

//PILE
void Empiler(Pile *p,File f);
void Depiler(Pile *p,File *f);
int Pilevide(Pile p);
Pile Creat_Pile(int nbr_de_file);
//MEMO
Memo Firstfit(Memo M,process p);
Memo Bestfit(Memo M,process p);
Memo Worstfit(Memo M,process p);
Memo creat_Partitions(int nombre_de_partitions);
Memo Creat_Ram();
void Affiche_Ram(Memo l,int t);
void gestionDeMemoire(Memo *p);
#endif //MEMORY_FUNCTION_H
