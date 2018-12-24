#include <stdio.h>
#include <stdlib.h>
#include "headers/function.h"
int main(void)
{
//    File mesProcess;
//    FILE *maFILE=fopen("FILE0.txt","r+");
    Pile maMemoire=NULL;
    maMemoire=Creat_Pile(3);
    Affiche_Ram(maMemoire);


    return 0;
}