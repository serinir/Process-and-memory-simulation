#include <unistd.h>
#include "headers/function.h"
char *ERROR_MEMORY="SET UP THE MEMORY PLEASE !";
char *ERROR_QUEUE="SET UP THE QUEUE PLEASE ! ";
char *ERROR_W="SHIT'S NOT READY YET!";
int main(void)
{
    int highlight;
    int choix;
    initscr();
    noecho();
    cbreak();
    refresh();
    //  start_color();
    //afficheAlarme(ERROR_MEMORY);
    getch();
    Memo maMemoire = NULL;
    FILE *a = fopen("FILE0.txt", "r");
    File f;
    f.h = NULL;
    f.t = NULL;
    process p;
    // affichemen(2);
    do {
        choix = affichemen(2);
        initscr();
        switch (choix) {
            case 0   : {
                maMemoire = Creat_Ram();
                mvprintw(25,25,"Memory READY");
                break;
            }
            case 1: {
                if (maMemoire)
                {start_color();Affiche_Ram(maMemoire, 2);break;}
                else {
                    afficheAlarme(ERROR_MEMORY);
                    break;
                }
                case 2: {
                    f = Creat_File(a);
                    break;
                }
                case 3: {
                    afficheAlarme(ERROR_W);
                    break;
                }
                case 4: {
                    afficheAlarme(ERROR_W);
                    break;
                }
                case 5: {
                    if(f.h)
                    {p = Defiler(&f);
                        insertProc(Bestfit(maMemoire, p), p);}else afficheAlarme(ERROR_QUEUE);
                    break;
                }
            }
        }
        sleep(1);
        delAlarme();
        refresh();
        checkUsed(maMemoire);
    } while (choix != 8);
//    Affiche_Ram(maMemoire, 2);
//    sleep(1);
//    insertProc(Firstfit(maMemoire, p), p);
//    Affiche_Ram(maMemoire, 8);
//    sleep(1);
//    gestionDeMemoire(&maMemoire);
//    Affiche_Ram(maMemoire, 16);
//    sleep(2);
//    checkUsed(maMemoire);
//    Affiche_Ram(maMemoire, 20);
//    time_t t = time(NULL);


    getch();
    endwin();
    return 0;
}
