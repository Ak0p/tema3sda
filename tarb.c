/*--- tarb.c --- operatii cu arbori binari --*/
#include "tarb.h"

TADir InitD()         /* initializare arbore */
{
	TADir dir = (TADir)calloc(1, sizeof(TDir));
	char *nume = (char*)calloc(5, sizeof(char));
	nume = "root";
	return dir;
}


// TADir ConstrDNod(char *nume, TArb s, TArb d)/* -> adresa nod (cu informatia x, 
// 				fiu stanga s, fiu dreapta d) sau NULL in caz de eroare */
// {
// 	TArb aux = (TArb)malloc (sizeof(TNod));  /* incearca alocare spatiu */
// 	if (!aux) return NULL;                   /* spatiu insuficient */
// 	aux->info = x; aux->st = s; aux->dr = d; /* actualizeaza campurile nodului */

// 	return aux;                              /* intoarce adresa nodului */
// }

TADir ConstrDir(char *nume) {
	TADir dir = (TADir)calloc(1, sizeof(TDir));
	dir->nume = (char*)calloc(strlen(nume) + 1, sizeof(char));
	memcpy(dir->nume, nume, strlen(nume) + 1);
	dir->parinte = NULL;
	dir->dirs = NULL;
	dir->st = NULL;
	dir->dr = NULL;
	return dir;
}

TAFile ConstrFisier(char *nume) {
	TAFile fisier = (TAFile)calloc(1, sizeof(TFile));
	fisier->nume = (char*)calloc(strlen(nume) + 1, sizeof(char));
	memcpy(fisier->nume, nume, strlen(nume) + 1);
	fisier->parinte = NULL;
	fisier->st = NULL;
	fisier->dr = NULL;
	return fisier;
}


TADir *GetDPos(TADir arbore, char *nume, int *leftright) {
	TADir p = arbore;
	while (p) {
		if (strcmp(p->nume, nume) > 0) { 
			*leftright = 0;
			if (p->st)
				return GetDPos(p->st, nume, leftright);
		} else if (strcmp(p->nume, nume) < 0) {
			*leftright = 1;
			if (p->dr)
				return GetDPos(p->dr, nume, leftright);
		} else {
			*leftright = -2;
			return NULL;
		}
	}
	return arbore;
}


TAFile *GetFPos(TAFile arbore, char *nume, int *leftright) {
	TAFile p = arbore;
	while (p) {
		if (strcmp(p->nume, nume) > 0) { 
			*leftright = 0;
			if (p->st)
				return GetFPos(p->st, nume, leftright);
		} else if (strcmp(p->nume, nume) < 0) {
			*leftright = 1;
			if (p->dr)
				return GetFos(p->dr, nume, leftright);
		} else {
			*leftright = -2;
				return NULL;
		}
	}
		return arbore;
}
	


int insertDir(TADir parinte, TADir copil) {
	int leftright = -1;
	TADir pozitie = GetDPos(parinte, copil->nume, &leftright);
	switch (leftright) {
		case 0:
			pozitie->st = copil;
			copil->parinte = parinte;
			break;
		case 1:
			pozitie->dr = copil;
			copil->parinte = parinte;
			break;
		case -2:
			return 0;
			break;
		default:
			return -1;
	}
	return 1;
}

int insertFisier(TAFile parinte, TAFile copil) {
	int leftright = -1;
	TAFile pozitie = GetFPos(parinte, copil->nume, &leftright);
	switch (leftright) {
		case 0:
			pozitie->st = copil;
			copil->parinte = parinte;
			break;
		case 1:
			pozitie->dr = copil;
			copil->parinte = parinte;
			break;
		case -2:
			return 0;
			break;
		default:
			return -1;
	}
	return 1;
}


// TArb ConstrFr(TInfo x)     /* -> adresa frunza cu informatia x, sau
// 					NULL daca nu exista spatiu */
// {
// 	TArb aux = (TArb)malloc(sizeof(TNod));
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
