#include "tarb.h"
#define wordSize 50
#define lineSize 100
#define words 10

void touch(TADir *actDir, char *nume) {
  // printf ("touch\n");
  TAFile *p = &((*actDir)->files);  // TAFile *p =&((*actDir->files));  ASA
  if (Is_Dir(((*actDir)->dirs), nume) == 1) {
    printf("Directory %s already exists!\n", nume);
    return;
  }
  int ret_val = insert_Fisier(p, nume, *actDir);
  // printf ("rv %d\n", ret_val);
  switch (ret_val) {
    case 1:
      // printf("Siuii\n");
      return;
    case 0:
      printf("File %s already exists!\n", nume);
      return;
  }
  // printf ("Aici\n");
}

void mkdir(TADir *actDir, char *nume) {
  TADir *p = &((*actDir)->dirs);
  // printf ("%s\n", nume);
  if (Is_File(((*actDir)->files), nume) == 1) {
    printf("File %s already exists!\n", nume);
    return;
  }

  int ret_val = insert_Dir(p, nume, *actDir);
  // printf ("rv %d\n", ret_val);

  switch (ret_val) {
    case 1:
      // printf("Siuii\n");
      return;
    case 0:
      printf("Directory %s already exists!\n", nume);
      return;
  }
  //  printf ("Aci\n");
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
  // if (!(dir->dirs->dr) && !(dir->dirs->st) && !(dir->files->st) &&
  // !(dir->files->dr)) {
  //   printf("\n");
  //   return;
  // }
  if (dir->dirs) {
    // printf("DA dir\n");
    Afi_Dir(dir->dirs);
  }

  if (dir->files) {
    // printf("DA files\n");
    Afi_Fisier(dir->files);
  }

  printf("\n");
}

TADir InitD() /* initializare arbore */
{
  TADir dir = (TADir)calloc(1, sizeof(TDir));
  char *nume = (char *)calloc(5, sizeof(char));
  strcat(nume, "root");
  dir->nume = nume;
  return dir;
}

TAFile rm(TAFile fisier, char *nume) {
  if (!fisier) return NULL;
  if (strcmp(fisier->nume, nume) > 0)
    fisier->st = rm(fisier->st, nume);
  else if (strcmp(fisier->nume, nume) < 0)
    fisier->dr = rm(fisier->dr, nume);
  else {
    if (!(fisier->dr) && !(fisier->st)) {
      // printf("1\n");
      free(fisier->nume);
      free(fisier);
      fisier = NULL;

    } else if (!(fisier->dr) && (fisier->st)) {
      // printf("2\n");
      TAFile aux = fisier;
      fisier = fisier->st;
      free(aux->nume);
      free(aux);

    } else if ((fisier->dr) && !(fisier->st)) {
      // printf("3\n");
      TAFile aux = fisier;
      fisier = fisier->dr;
      free(aux->nume);
      free(aux);

    } else {
      // printf("4\n");
      TAFile aux = GetFMin(fisier->dr);
      // printf("aux %s||fisier %s\n", aux->nume, fisier->nume);
      free(fisier->nume);
      fisier->nume = (char *)calloc(strlen(aux->nume) + 1, sizeof(char));
      strcpy(fisier->nume, aux->nume);
      // printf("aux %s||fisier %s\n", aux->nume, fisier->nume);
      fisier->dr = rm(fisier->dr, aux->nume);
    }
  }
  return fisier;
}
TADir rmdir(TADir dir, char *nume) {
  if (!dir) return NULL;
  if (strcmp(dir->nume, nume) > 0)
    dir->st = rmdir(dir->st, nume);
  else if (strcmp(dir->nume, nume) < 0)
    dir->dr = rmdir(dir->dr, nume);
  else {
    if (!(dir->dr) && !(dir->st)) {
      // printf("1\n");
      free(dir->nume);
      free(dir);
      dir = NULL;

    } else if (!(dir->dr) && (dir->st)) {
      // printf("2\n");
      TADir aux = dir;
      dir = dir->st;
      free(aux->nume);
      free(aux);

    } else if ((dir->dr) && !(dir->st)) {
      // printf("3\n");
      TADir aux = dir;
      dir = dir->dr;
      free(aux->nume);
      free(aux);

    } else {
      // printf("4\n");
      TADir aux = GetDMin(dir->dr);
      // printf("aux %s||fisier %s\n", aux->nume, fisier->nume);
      free(dir->nume);
      dir->nume = (char *)calloc(strlen(aux->nume) + 1, sizeof(char));
      strcpy(dir->nume, aux->nume);
      // printf("aux %s||fisier %s\n", aux->nume, fisier->nume);
      dir->dr = rmdir(dir->dr, aux->nume);
    }
  }
  return dir;
}

void pwd(TADir curr_dir) {
  if (!curr_dir) return;
  pwd(curr_dir->parinte);
  printf("/%s", curr_dir->nume);
}

TADir cd(TADir curr_dir, char *nume) {
  if (strcmp(nume, "..") == 0) {
    if (curr_dir->parinte != NULL) return curr_dir->parinte;
    return curr_dir;
  }
  if (Is_Dir(curr_dir->dirs, nume) == 0) {
    printf("Directory not found!\n");
    return curr_dir;
  }
  return GetDPos(curr_dir->dirs, nume);
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
      // printf("%s\n", word[wordCount]);
      wordCount++;
      word[wordCount] = strtok(NULL, " ");
    }

    if (strcmp(word[0], "touch") == 0) {
      // printf("TOUCH %s\n", word[1]);
      touch(&curr_dir, word[1]);
    }

    if (strcmp(word[0], "mkdir") == 0) {
      // printf("MKDIR %s\n", word[1]);
      mkdir(&curr_dir, word[1]);
    }

    if (strcmp(word[0], "ls") == 0) {
      // printf("LS\n");
      ls(curr_dir);
    }

    if (strcmp(word[0], "rm") == 0) {
      if (!curr_dir->files) {
        printf("File %s doesn't exist!\n", word[1]);
        continue;
      }
      if (Is_File(curr_dir->files, word[1]) == 0) {
        printf("File %s doesn't exist!\n", word[1]);
        continue;
      }
      // printf("RM %s\n", word[1]);

      curr_dir->files = rm(curr_dir->files, word[1]);
    }

    if (strcmp(word[0], "rmdir") == 0) {
      if (!curr_dir->dirs) {
        printf("Directory %s doesn't exist!\n", word[1]);
        continue;
      }
      if (Is_Dir(curr_dir->dirs, word[1]) == 0) {
        printf("Directory %s doesn't exist!\n", word[1]);
        continue;
      }

      curr_dir->dirs = rmdir(curr_dir->dirs, word[1]);
    }

    if (strcmp(word[0], "cd") == 0) {
      // printf("root: %s|curr: %s\n", root->nume, curr_dir->nume);
      curr_dir = cd(curr_dir, word[1]);
      // printf("\nroot: %s|curr: %s\n", root->nume, curr_dir->nume);
    }

    if (strcmp(word[0], "pwd") == 0) {
      // printf("root: %s|curr: %s\n", root->nume, curr_dir->nume);
      pwd(curr_dir);
      // printf("\nroot: %s|curr: %s\n", root->nume, curr_dir->nume);
      printf("\n");
    }

    if (strcmp(word[0], "find") == 0) {
    }

    if (strcmp(word[0], "quit") == 0) {
      // dealloc
      free(word);
      free(line);
      return 0;
    }

    free(word);
    free(line);
  }
}
