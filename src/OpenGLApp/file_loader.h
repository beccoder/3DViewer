#ifndef SRC_FILE_LOADER_H_
#define SRC_FILE_LOADER_H_

int get_data(char *path, float **v, unsigned int *v_size, unsigned int **faces,
             unsigned int *faces_size);
void count_size(char *line, unsigned int *size);
int trimString(char *str, char *line);
int alloc_v(float **vertices, unsigned int line_v);
int alloc_f(unsigned int **faces, unsigned int line_f);
int load_v(char *line, float **vertices, unsigned int line_v);
int load_f(char *line, unsigned int **faces, unsigned int *line_f, int *cur_f);
int read_f(char *line, unsigned int **faces, int *cur_f);
int read_longf(char *line, unsigned int **faces, unsigned int size_arr,
               int *cur_f);
void free_v(float **vertices);
void free_f(unsigned int **faces);
#endif  // SRC_FILE_LOADER_H_
