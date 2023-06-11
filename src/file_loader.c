#include "file_loader.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int get_data(char *path, float **v, unsigned int *v_size, unsigned int **faces,
             unsigned int *faces_size) {
  int err = 0;
  FILE *f;
  f = fopen(path, "r");

  *faces = NULL;
  *v = NULL;

  unsigned int line_v, line_f;
  line_v = line_f = 0;
  int cur_f = 0;
  if (f != NULL) {
    char l[2000];
    char line[2000];
    while (fgets(l, sizeof(l), f)) {
      trimString(l, line);
      if (memcmp(line, "v ", 2) == 0) {
        line_v++;
        if (load_v(line, v, line_v)) {
          err = 1;
          break;
        }
        *v_size = line_v * 3;
      }
      if (memcmp(line, "f ", 2) == 0) {
        line_f++;
        if (load_f(line, faces, &line_f, &cur_f)) {
          err = 1;
          break;
        }
        *faces_size = line_f * 3;
      }
    }
  } else {
    err = 1;
  }
  if ((int)line_v == 0 && (int)line_f == 0) err = 1;

  if (err != 0) {
    free(*faces);
    free(*v);
  }
  return err;
}

int load_f(char *line, unsigned int **faces, unsigned int *line_f, int *cur_f) {
  int err = 0;
  unsigned int size_arr = 0;
  count_size(line, &size_arr);
  if ((int)size_arr > 3) {
    (*line_f) += size_arr - 3;
  }
  if (alloc_f(faces, *line_f)) {
    err = 1;
  }
  if ((int)size_arr > 3 && err == 0) {
    if (read_longf(line, faces, size_arr, cur_f)) {
      err = 1;
    }
  } else if ((int)size_arr == 3 && err == 0) {
    if (read_f(line, faces, cur_f)) {
      err = 1;
    }
  } else {
    err = 1;
  }
  return err;
}

int read_f(char *line, unsigned int **faces, int *cur_f) {
  int err = 0;
  char *rest = line;
  char *token = strtok_r(rest, " ", &rest);
  while ((token = strtok_r(rest, " ", &rest))) {
    int len = sscanf(token, "%u/.", *faces + *cur_f);
    if (len != 1) {
      err = 1;
      break;
    }
    (*cur_f)++;
  }
  return err;
}

int read_longf(char *line, unsigned int **faces, unsigned int size_arr,
               int *cur_f) {
  int err = 0;
  int count = 0;
  unsigned int tmp[(int)size_arr];
  char *rest = line;
  char *token = strtok_r(rest, " ", &rest);
  while ((token = strtok_r(rest, " ", &rest))) {
    int len = sscanf(token, "%u/.", &tmp[count]);
    if (len != 1) {
      err = 1;
      break;
    }
    count++;
  }
  if (err != 1) {
    for (int i = 1; i < (int)size_arr - 1; i++) {
      *(*faces + *cur_f) = tmp[0];
      (*cur_f)++;
      *(*faces + *cur_f) = tmp[i];
      (*cur_f)++;
      *(*faces + *cur_f) = tmp[i + 1];
      (*cur_f)++;
    }
  }
  return err;
}

int load_v(char *line, float **v, unsigned int line_v) {
  int err = 0;
  if (alloc_v(v, line_v)) {
    err = 1;
  }
  char t0;
  int cur = 3 * ((int)line_v - 1);
  int len =
      sscanf(line, "%c %f %f %f", &t0, *v + cur, *v + cur + 1, *v + cur + 2);
  if (len != 4) {
    err = 1;
  }
  return err;
}

void count_size(char *line, unsigned int *size) {
  unsigned int count = 0;
  ;
  char dest[2000];
  snprintf(dest, sizeof(dest), "%s", line);
  char *rest = dest;
  char *token = strtok_r(rest, " ", &rest);
  while ((token = strtok_r(rest, " ", &rest))) {
    count++;
  }
  *size = count;
}

int trimString(char *str, char *line) {
  char *end;
  while (isspace((unsigned char)*str)) str++;
  end = str + strlen(str) - 1;
  while (end > str && isspace((unsigned char)*end)) end--;
  end[1] = '\0';
  snprintf(line, 2000, "%s", str);
  return 0;
}

int alloc_v(float **v, unsigned int line_v) {
  int err = 0;
  if (*v == NULL) {
    *v = (float *)malloc(3 * sizeof(float));
    if (v == NULL) {
      free(*v);
      err = 1;
    }
  } else {
    *v = (float *)realloc(*v, 3 * line_v * sizeof(float));
    if (*v == NULL) {
      free(*v);
      err = 1;
    }
  }
  return err;
}

int alloc_f(unsigned int **faces, unsigned int line_f) {
  int err = 0;
  if (*faces == NULL) {
    *faces = (unsigned int *)malloc(3 * line_f * sizeof(unsigned int));
    if (*faces == NULL) {
      free(*faces);
      err = 1;
    }
  } else {
    *faces = (unsigned int *)realloc(*faces, 3 * line_f * sizeof(unsigned int));
    if (*faces == NULL) {
      free(*faces);
      err = 1;
    }
  }
  return err;
}

void free_v(float **v) {
  free(*v);
  return;
}

void free_f(unsigned int **faces) {
  free(*faces);
  return;
}
