
#include "headers/function.h"

char *ERROR_MEMORY = "SET UP THE MEMORY PLEASE !";
char *ERROR_QUEUE = "SET UP THE QUEUE PLEASE ! ";
char *ERROR_W = "SHIT'S NOT READY YET!";
char *MENU_MAIN ="MAIN MENU:";
char *MENU_FIT="FIT MENU:";
char *MENU_INS="INSERTION MENU: ";
char *choices[] = {
        "SetUp the Memory",
        "Display Memory",
        "Set up queue",
        "Display Processes queue",
        "Choose Allocation method",
        "Load process into memory",
        "Setup Pile",
        "Display Pile"
};
char *Fit[] = {
        "First Fit",
        "Best Fit",
        "Worst Fit",
};
char *Insert[]={
        "inserer un seule processus",
        "Tout inserer",
        "Iserer depuis la pile"

};
int main(void) {
    int highlight;
    int choix, fitChoix;
    Pile s=NULL;
    Memo (*fitFuncPointer)(Memo, process)=NULL;
    initscr();
    noecho();
    cbreak();
    refresh();

    //  start_color();
    //afficheAlarme(ERROR_MEMORY);
    getch();
    Memo maMemoire = NULL;
    FILE *a;
    File f={NULL,NULL};
    process p;
    // affichemen(2);
    do {
        choix = afficheMen(2, choices, SIZE_CHOICES,MENU_MAIN);
        initscr();
        switch (choix) {
            case 0   : {
                maMemoire = Creat_Ram();
                afficheAlarme("MEMORY SETUP",0,10);
                getch();
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
                    sleep(2);
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
                        affiche_File(f, 0);
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
                        switch(afficheMen(2,Insert,SIZE_INS,MENU_INS))
                        {
                            case 0: {
                                    if(!f.h ) afficheAlarme(ERROR_QUEUE,0,16);
                                    if(!maMemoire) afficheAlarme(ERROR_MEMORY,0,13);
                                    if(!fitFuncPointer) afficheAlarme("FITFUNC !!! ",0,19);
                                        if(!f.h || !maMemoire || !fitFuncPointer)
                                        {getch();afficheAlarme("khrraaa",0,16);break;}
                                    p = Defiler(&f);
                                    if(!insertProc(fitFuncPointer(maMemoire, p), p)) Enfiler(&f,p);
                                    break;}
                            case 1:{
                                if(!f.h ) afficheAlarme(ERROR_QUEUE,0,16);
                                if(!maMemoire) afficheAlarme(ERROR_MEMORY,0,13);
                                if(!fitFuncPointer) afficheAlarme("FITFUNC !!! ",0,19);

                                if(!f.h || !maMemoire || !fitFuncPointer)
                                {getch();break;}
                                partOne(&f,fitFuncPointer,maMemoire);
                                break;}
                            case 2:{
                                if(!s ) afficheAlarme("SETUP PILE !",0,16);
                                if(!maMemoire) afficheAlarme(ERROR_MEMORY,0,13);
                                if(!fitFuncPointer) afficheAlarme("FITFUNC !!! ",0,19);

                                if(!s|| !maMemoire || !fitFuncPointer)
                                {getch();break;}
                                partTwo(&s,fitFuncPointer,maMemoire);
                                break;}

                            default: break;
                        }

                    break;
                }
                case 6: {s=Creat_Pile(3);afficheAlarme("Pile setup",0,16);getch();break;}
                case 7: {if(!s){afficheAlarme("SETUP PILE!",0,16);getch();break;}else affichePile(&s);getch();break;}
            }
            default: break;
        }
        //getch();
        delAlarme();
        refresh();
        if(maMemoire)
        {checkUsed(maMemoire);
            gestionDeMemoire(&maMemoire);}
    } while (choix !=-1 );


    getch();
    endwin();
    return 0;
}
