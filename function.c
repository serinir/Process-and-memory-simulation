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

void Mettre_on_queue(File *f){ //may need it 
  process x;
  Defiler(f,&x);
  Enfiler(f,x);
}

//-------------FONCTIONS DE LA PILE--------------//
void Empiler(Pile *p,File f){
  Pile q=(elmPile*)calloc(1,sizeof(elmPile));
  q->f=f;
  q->suiv=*p;
  *p=q;
}

void Depiler(Pile *p,File *f){
  Pile q=*p;
  *f=(*p)->f;
  *p=(*p)->suiv;
  free(q);
}

int Pilevide(Pile p){
  if(p==NULL) return 1;
  return 0;
}
//------------------CREATION DE LA RAM--------------//
Memo Creat_Ram()
{
    Memo l=NULL,p=NULL,q=NULL;
    partition x;
    int temp=0;

    FILE *f=NULL;
    f=fopen("MEMO.txt","r");

    if(f){
      while(fscanf(f,"%d %d %c",&x.start,&x.size,&x.state)!=EOF && temp<100000000){
        temp+=x.size; //la taille de la ram

        if(!l){//first partition
          l=(Memo)calloc(1,sizeof(partition));
          l->data=x;
          p=l; q=l;
        }
        else{
          q=(Memo)calloc(1,sizeof(partition));
          q->data=x;
          p->next=q;
          p=q;
        }
      }

      q->next=NULL;
      fclose(f);
    }
    else{
      puts("Impossible d'ouvrir le fichier MEMO.txt");
    }
    return l;
}

   //-------CREATION DE LA FILE-------//
File Creat_File(FILE *h){
  File f={0};
  process x;
    while(fscanf(h,"%d %d %d %d",&x.id,&x.time,&x.delay,&x.size)!=EOF){
      Enfiler(&f,x);
    }

  return f;
}

  //---------CREATION DE LA PILE------//
Pile Creat_Pile(int nbr_de_file){//nombre de fichier
  char fname[20];
  int i;
  FILE *f=NULL;
  Pile p=NULL;
  for(i=0;i<nbr_de_file;i++){
    sprintf(fname,"PILE/FILE%d.txt",i);
    f=fopen(fname,"r");
    if(f){
      Empiler(&p,Creat_File(f));
      fclose(f);
    }
    else{
      printf("Impossible d'ouvrir le fichier FILE%d.txt\n",i);
    }
  }
  
  return p;
}
  //--------FIT FONCTIONS-----------//

Memo Firstfit(Memo M,process p)
{
  while(M && (M->data.state=='U' || M->data.size<p.size) ){
    M=M->next;
  }
  return M;
}

Memo Bestfit(Memo M,process p){
  Memo r=Firstfit(M,p);
  M=r;
  while(M){
    if(M->data.state=='F' && M->data.size>=p.size && M->data.size<r->data.size){
      r=M;
    }
    M=M->next;
  }
  return r;
}

Memo Worstfit(Memo M,process p){
  Memo r=Firstfit(M,p);
  M=r;
  while(M){
    if(M->data.state=='F' && M->data.size>=p.size && M->data.size>r->data.size){
      r=M;
    }
    M=M->next;
  }
  return r;
}
  //-------FONCTIONS GRAPHICS -------//
  void Affiche_Ram(Memo l,int n)
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

