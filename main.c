
#include "headers/function.h"

char *ERROR_MEMORY = "SET UP THE MEMORY PLEASE !";
char *ERROR_QUEUE = "SET UP THE QUEUE PLEASE ! ";
//char *ERROR_W = "SHIT'S NOT READY YET!";
char *MENU_MAIN ="MAIN MENU:";
char *MENU_FIT="FIT MENU:";
char *MENU_INS="INSERTION MENU: ";
char *choices[] = {
        "Set Up the Memory",
        "Display Memory",
        "Creat and Enqueue the initial <waiting state> Process in the queue",
        "Display Processes queue",
        "Choose Allocation method",
        "Load process into memory",
};
char *Fit[] = {
        "First Fit",
        "Best Fit",
        "Worst Fit",
};
char *Insert[]={
        "inserer un seule processus",
        "Tout inserer"
};
int main(void) {
    int highlight;
    int choix, fitChoix,x,y;
    Memo (*fitFuncPointer)(Memo, process)=NULL;
    initscr();
    noecho();
    cbreak();
    refresh();
    getmaxyx(stdscr,x,y);
    //  start_color();
    //afficheAlarme(ERROR_MEMORY);
    getch();
    Memo maMemoire = NULL;
    FILE *a;
    File f;
    f.h = NULL;
    f.t = NULL;
    process p;
    // affichemen(2);
    do {
        choix = afficheMen(2, choices, SIZE_CHOICES,MENU_MAIN);
        initscr();
        switch (choix) {
            case 0   : {
                maMemoire = Creat_Ram();
                afficheAlarme("MEMORY SETUP",0,10);
                sleep(1);
                break;
            }
            case 1: {
                if (maMemoire) {
                    start_color();
                    Affiche_Ram(maMemoire, 2);
                    getch();
                    break;
                }
                else {
                    afficheAlarme(ERROR_MEMORY,0,13);
                    sleep(1);
                    break;
                }
                case 2: {
                    a = fopen("FILE0.txt", "r");
                    f = Creat_File(a);
                    break;
                }
                case 3: {
                    if(Filevide(f))
                    {afficheAlarme(ERROR_QUEUE,0,10);sleep(1);}
                    else {
                        affiche_File(f, 2);
                        getch();
                    }
                    break;
                }
                case 4: {
                    fitChoix   = afficheMen(2, Fit, SIZE_FIT,MENU_FIT);
                    switch (fitChoix) {
                        case 0: {
                            fitFuncPointer = &(Firstfit);
                            break;
                        }
                        case 1: {
                            fitFuncPointer = &(Bestfit);
                            break;
                        }
                        case 2: {
                            fitFuncPointer = &(Worstfit);
                            break;
                        }
                        default: break;
                    }
                    break;
                }
                case 5: {
                    if (maMemoire && f.h && fitFuncPointer) {
                        switch(afficheMen(2,Insert,SIZE_INS,MENU_INS))
                        {
                            case 0: {p = Defiler(&f);insertProc(fitFuncPointer(maMemoire, p), p);break;}
                            case 1:{while(!Filevide(f)){p=Defiler(&f);insertProc(fitFuncPointer(maMemoire, p), p);}break;}
                            default: break;
                        }

                    } else
                    {
                        if(!maMemoire) afficheAlarme(ERROR_MEMORY,0,13);
                        if(!f.h) afficheAlarme(ERROR_QUEUE,0,16);
                        if(!fitFuncPointer) afficheAlarme("FITFUNC !!! ",0,19);
                        refresh();
                        sleep(1);
                    }
                    break;
                }
            }
        }
        //getch();

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
