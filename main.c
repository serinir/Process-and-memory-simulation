
#include <unistd.h>
#include "headers/function.h"
int main(void)
{
//    File mesProcess;
//    FILE *maFILE=fopen("FILE0.txt","r+");
   Memo maMemoire=NULL;
    maMemoire=Creat_Ram();


    initscr();
    noecho();
    nocbreak();
    refresh();
    start_color();
    Affiche_Ram(maMemoire,2);
    sleep(1);
    gestionDeMemoire(&maMemoire);
    Affiche_Ram(maMemoire,8);
    getch();
    endwin();
    return 0;
}