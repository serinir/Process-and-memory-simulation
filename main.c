
#include <unistd.h>
#include "headers/function.h"
int main(void)
{
// initscr();
// noecho();
// nocbreak();
// refresh();
// start_color();

   Memo maMemoire=NULL;
   maMemoire=Creat_Ram();
   FILE *a=fopen("../FILE0.txt","r");
   File f=Creat_File(a);
   process p=Defiler(&f);

   //   Affiche_Ram(maMemoire,2);
//    sleep(1);
insertProc(Firstfit(maMemoire,p),p);
//    Affiche_Ram(maMemoire,8);
//   sleep(1);
  gestionDeMemoire(&maMemoire);
//    Affiche_Ram(maMemoire,16);
//  sleep(2);
    checkUsed(maMemoire);
//    Affiche_Ram(maMemoire,20);
//   time_t t=time(NULL);


//    getch();
//    endwin();
    return 0;
}