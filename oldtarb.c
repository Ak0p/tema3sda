// /*--- tarb.c --- operatii cu arbori binari --*/
// #include "tarb.h"

// TArb InitA()         /* initializare arbore */
// {
// 	return NULL;
// }

// TArb ConstrNod(TInfo x, TArb s, TArb d)/* -> adresa nod (cu informatia x, 
// 				fiu stanga s, fiu dreapta d) sau NULL in caz de eroare */
// {
// 	TArb aux = (TArb)malloc (sizeof(TNod));  /* incearca alocare spatiu */
// 	if (!aux) return NULL;                   /* spatiu insuficient */
// 	aux->info = x; aux->st = s; aux->dr = d; /* actualizeaza campurile nodului */

// 	return aux;                              /* intoarce adresa nodului */
// }

// TArb ConstrFr(TInfo x)     /* -> adresa frunza cu informatia x, sau
// 					NULL daca nu exista spatiu */
// {
// 	TArb aux = (TArb)malloc (sizeof(TNod));
// 	if (!aux) return NULL;
// 	aux->info = x; aux->st = aux->dr = NULL;

// 	return aux;
// }

// void distruge(TArb r) 	/* functie auxiliara - distruge toate nodurile */
// {
// 	if (!r) return;
// 	distruge (r->st);     /* distruge subarborele stang */
// 	distruge (r->dr);     /* distruge subarborele drept */
// 	free (r);             /* distruge nodul radacina */
// }

// void DistrArb(TArb *a) /* distruge toate nodurile arborelui de la adresa a */
// {
// 	if (!(*a)) return;       /* arbore deja vid */
// 	distruge (*a);           /* distruge toate nodurile */
// 	*a = NULL;               /* arborele este vid */
// }

// int NrNoduri(TArb r)        /* numarul de noduri din arborele r -*/
// {
// 	if (!r) return 0;          /* arbore vid => 0 noduri */
// 	return 1 + NrNoduri(r->st) + NrNoduri(r->dr);
// }

// int NrNiv(TArb r)           /* numar niveluri (0 pentru arbore vid) */
// {
// 	int ns, nd;
// 	if (!r) return 0;
// 	ns = NrNiv(r->st); nd = NrNiv(r->dr);
// 	return 1 + (ns >= nd ? ns : nd);
// }
