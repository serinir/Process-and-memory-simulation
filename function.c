//
// Created by el_hazred on 28/11/18.
//

#include "headers/function.h"


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
