#include "lin.h"

int getch(){
    int ch;
    ch = getchar();

    return ch;
}


void clear_screen(){
    printf("\e[H\e[2J");
    printf("\e[3J"); 
}


void get_terminal_size(term_size* ts){
    struct winsize w;

    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &w) == 0) {
        ts->height = w.ws_row;
        ts->width = w.ws_col;
    }
}



struct termios oldattr, newattr;

void OS_init(){
    tcgetattr(STDIN_FILENO, &oldattr);
    newattr = oldattr;
    newattr.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newattr);
}
void OS_close(){
    tcsetattr(STDIN_FILENO, TCSANOW, &oldattr);
}