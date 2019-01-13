//
// Created by el_hazred on 28/11/18.
//

#ifndef MEMORY_FUNCTION_H
#define MEMORY_FUNCTION_H
#define SIZE_CHOICES 6
#define SIZE_FIT 3
#define SIZE_INS 2
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curses.h>
#include <time.h>
#include <unistd.h>

//---------DECLARATIONS DES STRUCTURES---------//
//structure proccessus
typedef struct process {
    int id;
    int time;
    int delay;
    int size;
} process;
typedef struct partition {
    process proc;
    int start;
    int size;
    char state; // F pour libre "Free" ET U pour utilisé "Used"
} partition;
//liste chainée des partitions
typedef struct elmMemo//element du memoire
{
    partition data;
    struct elmMemo *next;
} elmMemo;
typedef elmMemo *Memo;


//structure de l'element de la file
typedef struct elmFile {
    process data;
    struct elmFile *next;
} elmFile;
//structure de la file
typedef struct File {
    elmFile *h, *t;
} File;
//tructure element de pile
typedef struct elmPile {
    File f;
    struct elmPile *suiv;
} elmPile;
typedef elmPile *Pile;

//----------PROTOTYPES DES FONCTIONS---------//
//FILE
void Enfiler(File *f, process x);

process Defiler(File *f);

int Filevide(File f);

process Tetefile(File f);

void Mettre_on_queue(File *f);

File Creat_File(FILE *h);

//PILE
void Empiler(Pile *p, File f);

void Depiler(Pile *p, File *f);

int Pilevide(Pile p);

Pile Creat_Pile(int nbr_de_file);

//MEMO
void newNode(Memo *l, int size);

Memo Firstfit(Memo M, process p);

Memo Bestfit(Memo M, process p);

Memo Worstfit(Memo M, process p);

Memo Creat_Ram();

void Affiche_Ram(Memo l, int t);

void gestionDeMemoire(Memo *p);

int insertProc(Memo src, process p);

void checkUsed(Memo src);

//GRAPHIQUE
int afficheMen(int a, char *choices[], int taille,char* menuMsg);

void supwin(WINDOW *win, int n);

void printMen(WINDOW *m, int j, char *choices[], int taille,char* menuMsg);

void afficheAlarme(char *s,int x,int y);

void delAlarme();

#endif //MEMORY_FUNCTION_H
