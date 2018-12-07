//
// Created by el_hazred on 28/11/18.
//

#include "headers/function.h"

//----------FONCTIONS DE LA FILE---------------//
void Enfiler(File *f,process x){
  elmFile *p;
  p=(elmFile*)calloc(1,sizeof(elmFile));
  p->data=x;
  p->next=NULL;
  if(f.h==NULL){
    *f.h=p;
    *f.t=p;
  }
  else{
    (*f.t)->next=p;
    *f.t=p;
  }
}

void Defiler(File *f,process *x){
  *x=(*f.h)->data;
  elmFile *p;
  p=*f.h;
  *f.h=(*f.h)->next;
  free(p);
}

int Filevide(File f){
  if(f.h==NULL) return 1;
  return 0;
}

elmFile  Tetefile(file f){
    return (f.h)->data;
}
//------------------FONCTION DE LA PILE--------------//
memo creat_Partitions(int nombre_de_partitions)
{
    memo l,p;
    int temp;
    l=malloc(sizeof(partition));
    p=l;
    //l'adress de debut de la premiere partition est egal a 0
    p->data.start=0;
    // la variable temp va sommer la taille de chaque partition
    //et la mettre dans l'adress de debut de a prochaine partition
    scanf("%d",&l->data.size);
    temp=p->data.size;

    while(nombre_de_partitions--)
    {
        p->next=malloc(sizeof(partition));
        p=p->next;
        p->data.start=temp;
        puts("donnée la taille de chaque paritions en kb");
        do
        {
            scanf("%d",&p->data.size);
            if(p->data.size>1024000)
                puts("La taille d'une partition ne peut pas dépasser 1024Mo");
            else if(p->data.size<0)
                puts("La taille d'une partition ne peut pas etre inferieur a 0kb");
        }while(p->data.size>1024000 || p->data.size<0);
        temp+=p->data.size;
    }
    p->next=NULL;
    return l;
}
