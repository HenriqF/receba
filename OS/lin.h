
#ifndef OS_GB
#define OS_GB

#include <stdio.h>
#include <unistd.h>
#include <termios.h>
#include <poll.h>
#include <sys/ioctl.h>

void OS_init();
void OS_close();


int getch();
void clear_screen();

typedef struct {
    unsigned short width;
    unsigned short height;
} term_size;
void get_terminal_size(term_size* ts);

#endif