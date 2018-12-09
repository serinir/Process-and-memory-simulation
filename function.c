//
// Created by khiro on 07/12/18.
//

#include "headers/function.h"

//----------FONCTIONS DE LA FILE---------------//
void Enfiler(File *f,process x){
  elmFile *p;
  p=(elmFile*)calloc(1,sizeof(elmFile));
  p->data=x;
  p->next=NULL;
  if(f->h==NULL){
     f->h=p;
     f->t=p;
  }
  else{
    (f->t)->next=p;
    f->t=p;
  }
}

void Defiler(File *f,process *x){
  *x=(f->h)->data;
  elmFile *p;
  p=f->h;
  f->h=(f->h)->next;
  free(p);
}

int Filevide(File f){
  if(f.h==NULL) return 1;
  return 0;
}

process  Tetefile(File f){
    return (f.h)->data;
}
//------------------FONCTION DE LA PILE--------------//
  Memo creat_Partitions(int nombre_de_partitions)
  {
      Memo l,p;
      l=malloc(sizeof(partition));
      p=l;
      
      //l'adress de debut de la premiere partition est egal a 0
      p->data.start=0;
      // la variable temp va sommer la taille de chaque partition
      //et la mettre dans l'adress de debut de a prochaine partition
      scanf("%d",&l->data.size);
      int temp=p->data.size;

      while(--nombre_de_partitions)
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
          if(nombre_de_partitions%2==0)
            p->data.state='F';
          else
            p->data.state='U';

          temp+=p->data.size;

      }
      p->next=NULL;
      return l;
  }
  //-------FONCTIONS GRAPHICS -------//
  void affiche_partitions(Memo l,int n)
  {
    WINDOW *win;
    
    Memo p=l;
    int i=0;
    while(p)
    {
      init_pair(1,COLOR_GREEN,COLOR_WHITE);
      init_pair(2,COLOR_RED,COLOR_WHITE);

      win=newwin(2,2,i*2,2);
      
      box(win,0,0);
      if(p->data.state=='F')
      wbkgd(win,COLOR_PAIR(1));
      else
      wbkgd(win,COLOR_PAIR(2));

      wrefresh(win);
      i++;
      p=p->next;
    }

  }
