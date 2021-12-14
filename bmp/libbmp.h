#ifndef _LIB_BITMAP_H_
#define _LIB_BITMAP_H_

int print_bmp(char *path);
int read_bmp(char *filename, char **data, int *cols, int *rows);
int close_bmp(void);


#endif
