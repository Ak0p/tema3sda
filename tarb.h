/*--- tarb.h ---*/
#include <ctype.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// #ifndef ARBORE_BINAR
// #define ARBORE_BINAR

// typedef int TInfo;
// typedef struct nod {
// 	TInfo info;
// 	struct nod *st, *dr;
// } TNod, *TArb, **AArb;

typedef struct dir {
  char* nume;
  struct dir* parinte;
  struct dir* dirs;
  struct dir* st;
  struct dir* dr;
  struct file* files;
} TDir, *TADir, **ADir;

typedef struct file {
  char* nume;
  struct dir* parinte;
  struct file* st;
  struct file* dr;
} TFile, *TAFile, **AFile;

TADir ConstrDir(char*);
TAFile ConstrFisier(char*);
TADir GetDPos(TADir, char*);
TAFile GetFPos(TAFile, char*);
TAFile GetFMin(TAFile);
TADir GetDMin(TADir);
int insert_Dir(TADir*, char*, TADir);
int insert_Fisier(TAFile*, char*, TADir);
int Is_Dir(TADir, char*);
int Is_File(TAFile, char*);

// /*-- Operatii elementare --*/
// TArb InitA();           /* initializare arbore */
// TArb ConstrNod(TInfo x, TArb s, TArb d);
//      /* -> adresa nod (cu info x, fiu stanga s, fiu dreapta d)
// 		   sau NULL daca nu exista spatiu */
// TArb ConstrFr(TInfo x);
//      /* -> adresa frunza cu informatia x, sau NULL daca nu exista spatiu */
// void DistrArb(AArb);    /* distruge arbore */
// int NrNoduri(TArb);     /* numar noduri */
// int NrNiv(TArb);        /* numar niveluri (0 pentru arbore vid) */

// /*-- Operatii suplimentare --*/
// void AfiArb(TArb r);
// 	  /*- afiseaza arborele r -*/
// int Inserare_ABC(TArb* a, int x);
// 	  /*- insereaza x in arborele binar de cautare a -*/
// #endif

// #ifndef _random_
// #define _random_
// #define random(n) (rand() % (n))
// #define randomize() (srand((unsigned int)time(NULL)))
// #endif
