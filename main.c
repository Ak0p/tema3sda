/*BĂROIU Andrei - 312CB*/

#include "tarb.h"
#define wordSize 50
#define lineSize 100
#define words 10

TADir InitD() { /* initializare arbore */
  TADir dir = (TADir)calloc(1, sizeof(TDir));
  char *nume = (char *)calloc(5, sizeof(char));
  strcat(nume, "root");
  dir->nume = nume;
  return dir;
}

void touch(TADir *actDir, char *nume) {
  TAFile *p = &((*actDir)->files);
  if (IsDir(((*actDir)->dirs), nume) == 1) {
    printf("Directory %s already exists!\n", nume);
    return;
  }
  int ret_val = insert_Fisier(p, nume, *actDir);
  switch (ret_val) {
    case 1:
      return;
    case 0:
      printf("File %s already exists!\n", nume);
      return;
  }
}

void mkdir(TADir *actDir, char *nume) {
  TADir *p = &((*actDir)->dirs);
  if (IsFile(((*actDir)->files), nume) == 1) {
    printf("File %s already exists!\n", nume);
    return;
  }
  int ret_val = insert_Dir(p, nume, *actDir);
  switch (ret_val) {
    case 1:
      return;
    case 0:
      printf("Directory %s already exists!\n", nume);
      return;
  }
}

void Afi_Dir(TADir dir) {
  if (dir->st) Afi_Dir(dir->st);
  if (dir) printf("%s ", dir->nume);
  if (dir->dr) Afi_Dir(dir->dr);
}

void Afi_Fisier(TAFile file) {
  if (file->st) Afi_Fisier(file->st);
  if (file) printf("%s ", file->nume);
  if (file->dr) Afi_Fisier(file->dr);
}

void ls(TADir dir) {
  if (dir->dirs) {
    Afi_Dir(dir->dirs);
  }

  if (dir->files) {
    Afi_Fisier(dir->files);
  }

  printf("\n");
}

TAFile rm(TAFile fisier, char *nume) {
  if (!fisier) return NULL;
  TAFile aux = fisier;
  if (strcmp(fisier->nume, nume) == 0) {
    if (!(fisier->dr) && !(fisier->st)) {
      free(fisier->nume);
      free(fisier);
      fisier = NULL;
    } else if (!(fisier->dr) && (fisier->st)) {
      fisier = fisier->st;
      free(aux->nume);
      free(aux);
    } else if ((fisier->dr) && !(fisier->st)) {
      fisier = fisier->dr;
      free(aux->nume);
      free(aux);
    } else {
      aux = GetFMin(fisier->dr);
      free(fisier->nume);
      fisier->nume = (char *)calloc(strlen(aux->nume) + 1, sizeof(char));
      memcpy(fisier->nume, aux->nume, strlen(aux->nume) + 1);
      fisier->dr = rm(fisier->dr, aux->nume);
    }
  } else if (strcmp(fisier->nume, nume) < 0) {
    fisier->dr = rm(fisier->dr, nume);
  } else {
    fisier->st = rm(fisier->st, nume);
  }
  aux = NULL;
  return fisier;
}

TADir rmdir(TADir dir, char *nume) {
  if (!dir) return NULL;
  TADir aux = dir;
  if (strcmp(dir->nume, nume) == 0) {
    if (!(dir->dr) && !(dir->st)) {
      free(dir->nume);
      free(dir);
      dir = NULL;
    } else if (!(dir->dr) && (dir->st)) {
      dir = dir->st;
      free(aux->nume);
      free(aux);
    } else if ((dir->dr) && !(dir->st)) {
      dir = dir->dr;
      free(aux->nume);
      free(aux);
    } else {
      aux = GetDMin(dir->dr);
      free(dir->nume);
      dir->nume = (char *)calloc(strlen(aux->nume) + 1, sizeof(char));
      strcpy(dir->nume, aux->nume);
      dir->dr = rmdir(dir->dr, aux->nume);
    }
  } else if (strcmp(dir->nume, nume) < 0)
    dir->dr = rmdir(dir->dr, nume);
  else {
    dir->st = rmdir(dir->st, nume);
  }
  return dir;
}

void pwd(TADir curr_dir) {
  if (!curr_dir)
    return;
  else {
    pwd(curr_dir->parinte);
    printf("/%s", curr_dir->nume);
  }
}

TADir cd(TADir curr_dir, char *nume) {
  if (strcmp(nume, "..") == 0) {
    if (curr_dir->parinte != NULL) return curr_dir->parinte;
    return curr_dir;
  }
  if (IsDir(curr_dir->dirs, nume) == 0) {
    printf("Directory not found!\n");
    return curr_dir;
  }
  return GetDPos(curr_dir->dirs, nume);
}

TADir find(TADir nod, TADir mark, char *nume, char mod) {
  if (!nod) return NULL;
  // printf(">>>D %s %s\n", nod->nume, nume);
  switch (mod) {
    case 'd': {
      if (strcmp(nod->nume, nume) == 0) {
        mark = nod;
        return mark;
      }
      mark = find(nod->st, mark, nume, mod);
      if (mark) return mark;
      mark = find(nod->dr, mark, nume, mod);
      if (mark) return mark;
      mark = find(nod->dirs, mark, nume, mod);
      return mark;
    }
    case 'f': {
      if (IsFile(nod->files, nume)) {
        mark = nod;
        return mark;
      }
      mark = find(nod->st, mark, nume, mod);
      if (mark) {
        return mark;
      }
      mark = find(nod->dr, mark, nume, mod);
      if (mark) {
        return mark;
      }
      mark = find(nod->dirs, mark, nume, mod);
      return mark;
    }
  }
  return NULL;
}

int main() {
  TADir root = InitD();
  TADir curr_dir = root;

  // parsare

  while (1) {
    char *line = (char *)calloc(lineSize, sizeof(char));
    char **word = (char **)calloc(words, sizeof(char *));
    int wordCount = 0;
    if (!fgets(line, lineSize, stdin)) {
      free(word);
      free(line);
      break;
    }
    if (strrchr(line, '\n')) *strrchr(line, '\n') = '\0';

    word[wordCount] = strtok(line, " ");
    while (word[wordCount]) {
      wordCount++;
      word[wordCount] = strtok(NULL, " ");
    }

    if (strcmp(word[0], "touch") == 0) {
      touch(&curr_dir, word[1]);
    }

    if (strcmp(word[0], "mkdir") == 0) {
      mkdir(&curr_dir, word[1]);
    }

    if (strcmp(word[0], "ls") == 0) {
      ls(curr_dir);
    }

    if (strcmp(word[0], "rm") == 0) {
      if (!curr_dir->files) {
        printf("File %s doesn't exist!\n", word[1]);
        continue;
      }
      if (IsFile(curr_dir->files, word[1]) == 0) {
        printf("File %s doesn't exist!\n", word[1]);
        continue;
      }
      curr_dir->files = rm(curr_dir->files, word[1]);
    }

    if (strcmp(word[0], "rmdir") == 0) {
      if (!curr_dir->dirs) {
        printf("Directory %s doesn't exist!\n", word[1]);
        continue;
      }
      if (IsDir(curr_dir->dirs, word[1]) == 0) {
        printf("Directory %s doesn't exist!\n", word[1]);
        continue;
      }

      curr_dir->dirs = rmdir(curr_dir->dirs, word[1]);
    }

    if (strcmp(word[0], "cd") == 0) {
      curr_dir = cd(curr_dir, word[1]);
    }

    if (strcmp(word[0], "pwd") == 0) {
      pwd(curr_dir);
      printf("\n");
    }

    if (strcmp(word[0], "find") == 0) {
      TADir mark = NULL;

      mark = find(root, mark, word[2], word[1][1]);
      if (mark) {
        switch (word[1][1]) {
          case 'f': {
            printf("File %s found!\n", word[2]);
            break;
          }
          case 'd': {
            printf("Directory %s found!\n", word[2]);
            break;
          }
        }
        pwd(mark);
        printf("\n");
      }

      else {
        switch (word[1][1]) {
          case 'f': {
            printf("File %s not found!\n", word[2]);
            break;
          }
          case 'd': {
            printf("Directory %s not found!\n", word[2]);
            break;
          }
          default:
            printf("Mod invalid de utilizare\n");
        }
      }
    }

    if (strcmp(word[0], "quit") == 0) {
      free(root->nume);
      free(root);
      free(word);
      free(line);
      return 0;
    }

    free(word);
    free(line);
  }
  return 0;
}
