#include "headers/function.h"

//----------------FONCTIONS DE LISTE------------//
void newNode(Memo *l, int size) {
    Memo p = *l, q;
    int start;
    if (size > 0) {
        if (!*l) {
            *l = malloc(sizeof(partition));
            (*l)->data.size = size;
            (*l)->data.state = 'F';
            (*l)->data.start = 0;
            (*l)->next = NULL;
        } else {
            while (p) {
                q = p;
                start = p->data.start + p->data.size;
                p = p->next;
            }
            q->next = malloc(sizeof(partition));
            q = q->next;
            q->data.size = size;
            q->data.state = 'F';
            q->data.start = start;
            q->next = NULL;
        }
    }
}

//----------FONCTIONS DE LA FILE---------------//
void Enfiler(File *f, process x) {
    elmFile *p;
    p = (elmFile *) calloc(1, sizeof(elmFile));
    p->data = x;
    p->next = NULL;
    if (f->h == NULL) {
        f->h = p;
        f->t = p;
    } else {
        (f->t)->next = p;
        f->t = p;
    }
}

process Defiler(File *f) {

    process x = (f->h)->data;
    elmFile *p;
    p = f->h;
    f->h = (f->h)->next;
    free(p);
    return x;
}

int Filevide(File f) {
    if (f.h == NULL) return 1;
    return 0;
}

process Tetefile(File f) {
    return (f.h)->data;
}

void Mettre_on_queue(File *f) { //may need it
    process x;
    x = Defiler(f);
    Enfiler(f, x);
}

//-------------FONCTIONS DE LA PILE--------------//
void Empiler(Pile *p, File f) {
    Pile q = (elmPile *) calloc(1, sizeof(elmPile));
    q->f = f;
    q->suiv = *p;
    *p = q;
}

void Depiler(Pile *p, File *f) {
    Pile q = *p;
    *f = (*p)->f;
    *p = (*p)->suiv;
    free(q);
}

int Pilevide(Pile p) {
    if (p == NULL) return 1;
    return 0;
}

//------------------CREATION DE LA RAM--------------//
Memo Creat_Ram() {
    Memo l = NULL, p = NULL, q = NULL;
    partition x;
    int taille = 0;

    FILE *f = NULL;
    f = fopen("MEMO.txt", "r");

    if (f) {
        while (fscanf(f, "%d %d %c", &x.start, &x.size, &x.state) != EOF && taille < 100000000) {
            taille += x.size; //la taille de la ram

            if (!l) {//first partition
                l = (Memo) calloc(1, sizeof(partition));
                l->data = x;
                p = l;
                q = l;
            } else {
                q = (Memo) calloc(1, sizeof(partition));
                q->data = x;
                p->next = q;
                p = q;
            }
        }
        q->next = NULL;
        fclose(f);
    } else {
        puts("Impossible d'ouvrir le fichier MEMO.txt");
    }
    return l;
}

void gestionDeMemoire(Memo *p) {
    Memo *q = &(*p), end = *q, oldend;
// on itere j'usquau dernier element de la liste
    while (end->next)
        end = end->next;
    oldend = end;
    //a chaque partition libre qu'on trouve on la met a la fin et elle devien la nouvelle fin;
    while ((*q)) {
        if ((*q) != oldend) {
            if ((*q)->data.state == 'F' && (*q)->next) {
                end->next = *q;
                *q = (*q)->next;
                end = end->next;
                end->next = NULL;
            } else if ((*q)->next)
                q = &((*q)->next);
        } else { break; }
    }

}

void checkUsed(Memo src) {
    Memo temp = src;

    while (temp) {
        if (temp->data.state == 'U' && temp->data.proc.time <= time(NULL))
            temp->data.state = 'F';
        temp = temp->next;
    }
}

//-------CREATION DE LA FILE-------//
File Creat_File(FILE *h) {
    File f = {0};
    process x;
    while (fscanf(h, "%d %d %d %d", &x.id, &x.time, &x.delay, &x.size) != EOF) {
        Enfiler(&f, x);
    }

    return f;
}

//---------CREATION DE LA PILE------//
Pile Creat_Pile(int nbr_de_file) {//nombre de fichier
    char fname[20];
    int i;
    FILE *f = NULL;
    Pile p = NULL;
    for (i = 0; i < nbr_de_file; i++) {
        sprintf(fname, "FILE%d.txt", i);
        f = fopen(fname, "r");
        if (f) {
            Empiler(&p, Creat_File(f));
            fclose(f);
        } else {
            printf("Impossible d'ouvrir le fichier FILE%d.txt\n", i);
        }
    }

    return p;
}
//--------FIT FONCTIONS-----------//

Memo Firstfit(Memo M, process p) {
    while (M && (M->data.state == 'U' || M->data.size < p.size)) {
        M = M->next;
    }
    return M;
}

Memo Bestfit(Memo M, process p) {
    Memo r = Firstfit(M, p);
    M = r;
    while (M) {
        if (M->data.state == 'F' && M->data.size >= p.size && M->data.size < r->data.size) {
            r = M;
        }
        M = M->next;
    }
    return r;
}

Memo Worstfit(Memo M, process p) {
    Memo r = Firstfit(M, p);
    M = r;
    while (M) {
        if (M->data.state == 'F' && M->data.size >= p.size && M->data.size > r->data.size) {
            r = M;
        }
        M = M->next;
    }
    return r;
}

int insertProc(Memo dest, process p) {
    int diff;
    if (dest) {
        if (dest->data.state != 'F')
            puts("erreur adress renvoyer non libre");
        else {
            dest->data.state = 'U';
            dest->data.proc = p;
            dest->data.proc.time += time(NULL);
            diff = dest->data.size - p.size;
            dest->data.size = p.size;
            newNode(&dest, diff);
        }
        return 1;
    }
    return 0;
}
//-------FONCTIONS GRAPHICS -------//
void Affiche_Ram(Memo l, int t) {
    WINDOW *win;
    Memo p = l;
    int i = 0;
    while (p) {
        init_pair(1, COLOR_GREEN, COLOR_GREEN);
        init_pair(2, COLOR_RED, COLOR_RED);
        win = newwin(2, 2, 10 + t, i * 2 + 5 * i);

        box(win, 1, 1);
        if (p->data.state == 'F')
            wbkgd(win, COLOR_PAIR(1));
        else
            wbkgd(win, COLOR_PAIR(2));

        wrefresh(win);
        i++;
        p = p->next;
    }
}

void printMen(WINDOW *m, int j, char *choices[], int taille,char* menuMsg) {
    box(m, 0, 0);
    wattron(m, A_BOLD | A_ITALIC);
    mvwprintw(m, 1, 1, "%s",menuMsg);
    wattroff(m, A_BOLD | A_ITALIC);
    for (int i = 2; i <= taille + 1; i++) {
        if (i == j) {
            wattron(m, A_REVERSE);
            mvwprintw(m, i, 1, "%s", choices[i - 2]);
            wattroff(m, A_REVERSE);
        } else mvwprintw(m, i, 1, "%s", choices[i - 2]);
    }
    wrefresh(m);
}

void supwin(WINDOW *win, int n) {
    wborder(win, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');

    for (size_t i = 0; i <= n; i++) {
        mvwprintw(win, 1 + i, 1, "                                                                                           ");
    }
    wrefresh(win);
    delwin(win);
}

int afficheMen(int a, char *choices[], int taille,char* menuMsg) {
    int cho = 0, highlight = a;
    char c;
    WINDOW *n = newwin(taille + 3, 70, 0, 0);
    keypad(n, TRUE);
    printMen(n, highlight, choices, taille,menuMsg);
    while (1) {
        c = wgetch(n);
        switch (c) {
            case 3 :
                if (highlight == 2)
                    highlight = taille + 1;
                else --highlight;
                break;
            case 2:
                if (highlight == taille + 1)
                    highlight = 2;
                else ++highlight;
                break;

            case 10:
                cho = highlight;
                break;
            case 127:
                    cho=1;
                    break;
            default :
                mvprintw(10, 0, "Charcter pressed is = %3d Hopefully it can be printed as '%c'", c, c);
                refresh();
                break;
        }
        printMen(n, highlight, choices, taille,menuMsg);
        if (cho != 0)
            break;

    }
    supwin(n, taille + 1);
    return cho - 2;
}
void afficheAlarme(char *s,int x,int y) {
    WINDOW *win = newwin(3, 30, y, x);
    box(win, 0, 0);
    wattron(win, A_BOLD | A_ITALIC);
    mvwprintw(win, 1, 1, "%s", s);
    wattroff(win, A_BOLD | A_ITALIC);
    wrefresh(win);
}
void delAlarme() {
    for (size_t i = 9; i <= 20; i++) {
        mvprintw(1 + i, 0, "                                                                                         ");
    }
}
