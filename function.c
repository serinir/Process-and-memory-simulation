//
// Created by khiro on 02/12/18.
//

#include "headers/function.h"

void Enfiler(FILE f,partition x){
  process *nv;
  nv=(process*)calloc(1,sizeof(process));
  nv->id=f.t->id++;
  nv->time=;
  nv->delay=;
  nv->size=x.size;
  nv->next=f.t;
  f.t=nv;
}

void Defiler(FILE f,partition x,int d){
  x.size=f.h->size;
  d=f.h->delay;
  f.h=f.h->next;
}

int Filevide(FILE f){
  if(F.h==NULL) return 1;
  return 0;
}

int  Tetefile(FILE f){
  if(Filevide(f)!=0)
    return f.h->size;
  return 0;
}
//just a prototype !!
