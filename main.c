#include <unistd.h>
#include "headers/function.h"

char *ERROR_MEMORY = "SET UP THE MEMORY PLEASE !";
char *ERROR_QUEUE = "SET UP THE QUEUE PLEASE ! ";
char *ERROR_W = "SHIT'S NOT READY YET!";
char *choices[] = {
        "Set Up the Memory",
        "Display Memory",
        "Creat and Enqueue the initial <waiting state> Process in the queue",
        "Display Processes queue",
        "Choose Allocation methode",
        "Load process into memmory",
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
        choix = affichemen(2, choices, SIZE_CHOICES);
        initscr();
        switch (choix) {
            case 0   : {
                maMemoire = Creat_Ram();
                break;
            }
            case 1: {
                if (maMemoire) {
                    start_color();
                    Affiche_Ram(maMemoire, 2);
                    break;
                }
                else {
                    afficheAlarme(ERROR_MEMORY,0,13);
                    break;
                }
                case 2: {
                    a = fopen("FILE0.txt", "r");
                    f = Creat_File(a);
                    break;
                }
                case 3: {
                    afficheAlarme(ERROR_W,0,10);
                    break;
                }
                case 4: {
                    fitChoix = affichemen(2, Fit, SIZE_FIT);
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
                    }
                    break;
                }
                case 5: {
                    if (maMemoire && f.h && fitFuncPointer) {
                        switch(affichemen(2,Insert,SIZE_INS))
                        {
                            case 0: {p = Defiler(&f);insertProc(fitFuncPointer(maMemoire, p), p);break;}
                            case 1:{while(!Filevide(f)){p=Defiler(&f);insertProc(fitFuncPointer(maMemoire, p), p);}break;}
                        }

                    } else
                    {
                        if(!maMemoire) afficheAlarme(ERROR_MEMORY,0,13);
                        if(!f.h) afficheAlarme(ERROR_QUEUE,0,16);
                        if(!fitFuncPointer) afficheAlarme("FITFUNC !!! ",0,19);
                        refresh();
                    }
                    break;
                }
            }
        }
        getch();
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
