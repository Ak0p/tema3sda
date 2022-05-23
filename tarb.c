/*BĂROIU Andrei - 312CB */
#include "tarb.h"

TADir ConstrDir(char *nume) {
  TADir dir = (TADir)calloc(1, sizeof(TDir));
  dir->nume = (char *)calloc(strlen(nume) + 1, sizeof(char));
  memcpy(dir->nume, nume, strlen(nume) + 1);
  dir->parinte = NULL;
  dir->dirs = NULL;
  dir->st = NULL;
  dir->dr = NULL;
  return dir;
}

TAFile ConstrFisier(char *nume) {
  TAFile fisier = (TAFile)calloc(1, sizeof(TFile));
  fisier->nume = (char *)calloc(strlen(nume) + 1, sizeof(char));
  memcpy(fisier->nume, nume, strlen(nume) + 1);
  return fisier;
}

int IsFile(TAFile arbore, char *nume) {
  if (!arbore) return 0;
  if (strcmp(arbore->nume, nume) > 0) {
    if (arbore->st) return IsFile(arbore->st, nume);
  } else if (strcmp(arbore->nume, nume) < 0) {
    if (arbore->dr) return IsFile(arbore->dr, nume);
  } else {
    return 1;
  }
  return 0;
}

int IsDir(TADir arbore, char *nume) {
  if (!arbore) return 0;
  if (strcmp(arbore->nume, nume) > 0) {
    if (arbore->st) return IsDir(arbore->st, nume);
  } else if (strcmp(arbore->nume, nume) < 0) {
    if (arbore->dr) return IsDir(arbore->dr, nume);
  } else {
    return 1;
  }
  return 0;
}

int insert_Dir(TADir *a, char *nume, TADir parinte) {
  TADir aux, p, n;
  if (*a == NULL) {
    *a = ConstrDir(nume);
    if (!*a) {
      // printf("1\n");
      return 0;
    }
    (*a)->parinte = parinte;
    return 1;
  }
  n = *a;
  while (n) {
    p = n;
    if (strcmp(n->nume, nume) == 0) {
      // printf("Aci\n");
      return 0;
    }
    if (strcmp(n->nume, nume) > 0)
      n = n->st;
    else
      n = n->dr;
  }
  aux = ConstrDir(nume);
  if (!aux) {
    // printf("3\n");
    return 0;
  }
  aux->parinte = parinte;

  if (strcmp(p->nume, nume) > 0)
    p->st = aux;
  else
    p->dr = aux;
  return 1;
}

int insert_Fisier(TAFile *a, char *nume, TADir parinte) {
  TAFile aux, p, n;
  if (*a == NULL) {
    *a = ConstrFisier(nume);
    if (!*a) {
      // printf("1\n");
      return 0;
    }
    (*a)->parinte = parinte;
    return 1;
  }
  n = *a;
  while (n) {
    p = n;
    if (strcmp(n->nume, nume) == 0) {
      // printf("Aci\n");
      return 0;
    }

    if (strcmp(n->nume, nume) > 0)
      n = n->st;
    else
      n = n->dr;
  }
  aux = ConstrFisier(nume);
  if (!aux) {
    // printf("3\n");
    return 0;
  }
  aux->parinte = parinte;

  if (strcmp(p->nume, nume) > 0)
    p->st = aux;
  else
    p->dr = aux;
  return 1;
}

TADir GetDPos(TADir arbore, char *nume) {
  if (!arbore) return NULL;
  if (strcmp(arbore->nume, nume) > 0)
    return GetDPos(arbore->st, nume);
  else if (strcmp(arbore->nume, nume) < 0)
    return GetDPos(arbore->dr, nume);
  return arbore;
}

TAFile GetFPos(TAFile arbore, char *nume) {
  if (!arbore) return NULL;
  if (strcmp(arbore->nume, nume) > 0)
    return GetFPos(arbore->st, nume);
  else if (strcmp(arbore->nume, nume) < 0)
    return GetFPos(arbore->dr, nume);
  return arbore;
}

TAFile GetFMin(TAFile arbore) {
  if (!arbore) return NULL;
  if (!arbore->st) return arbore;
  return GetFMin(arbore->st);
}

TADir GetDMin(TADir arbore) {
  if (!arbore) return NULL;
  if (!arbore->st) return arbore;
  return GetDMin(arbore->st);
}
