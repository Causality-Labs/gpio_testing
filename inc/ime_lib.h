#ifndef _IME_LIB_H_
#define _IME_LIB_H_

//#define EXISTING_FILE "/dev/here"
//#define NON_EXISTING_FILE "/dev/not_here"

struct point
{
    int x;
    int y;
};

int add_numbers(int x, int y);
int DrawPoint(struct point);
struct point MakePoint(int x , int y);
int init_Display(int x, int y);
//int ime_open(const char * file_name);

#endif  /* _IME_LIB_H_ */