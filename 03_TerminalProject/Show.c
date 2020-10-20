#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>

WINDOW *create_newwin(int height,int width,int starty,int startx);
void destroy_win(WINDOW *local_win);
int count_lines(char *file_name);
char** file_load(char *file_name, int l, int text_w);

int main(int argc, char *argv[]) {
    if(argc != 2) {
        printf("filename is not set.\n");
        return -1;
    }
    WINDOW *window;
    initscr();
    cbreak();
    keypad(stdscr,TRUE);
    int height = 30, width = 60;
    int starty = (LINES-height)/2;
    int startx = (COLS-width)/2;
    int lines = count_lines(argv[1]);
    int c = 0;
    if(lines < 0) {
        endwin();
        printf("file error.\n");
        return -2;
    }
    int text_w = width-1, text_h = height-2;
    char **arr = file_load(argv[1],lines,text_w);
    if(arr == NULL) {
        endwin();
        printf("memory error.\n");
        return -3;
    }
    printw("File: %s",argv[1]);
    refresh();
    window = create_newwin(height,width,starty,startx);
    for(int i=0; i<text_h; ++i) {
        mvprintw(starty+i+1,startx+1,"%s",arr[i]);
    }
    int scroll_pos = 0;
    while((c = getch()) != 0x1b) {
        if(c == 0x20) {
            if(text_h+scroll_pos != lines) {
                scroll_pos++;
            }
            werase(window);
            refresh();
            window = create_newwin(height,width,starty,startx);
            int z = 0;
            for(int z=0, i=scroll_pos; i<text_h+scroll_pos; ++z, ++i) {
                mvprintw(starty+z+1,startx+1,"%s",arr[i]);
            }
        }
    }

    endwin();
    return 0;
}

WINDOW* create_newwin(int height,int width,int starty,int startx) {
    WINDOW *local_win;
    local_win = newwin(height,width,starty,startx);
    box(local_win,0,0);
    wrefresh(local_win);
    return local_win;
}

char** file_load(char *file_name, int l, int text_w) {
    FILE *f = fopen(file_name,"r");
    char c;
    if (f == NULL) {
        return NULL;
    }
    char **arr = calloc(l, sizeof(char*));
    for(int i=0; i<l; ++i) {
        arr[i] = calloc(text_w,sizeof(char));
    }
    int i, j;
    for(i=0; i<l; ++i) {
        for(j=0; j<text_w-1; ++j) {
            c = fgetc(f);
            if(c == EOF) {
                arr[i][j] = 0;
                fclose(f);
                return arr;
            } else if(c == '\n') {
                arr[i][j] = 0;
                break;
            } else {
                arr[i][j] = c;
            }
        }
        if(j == text_w-1) {
            while(fgetc(f) != '\n');
        }
    }
    fclose(f);
    return arr;
}

int count_lines(char *file_name) {
    FILE *f = fopen(file_name,"r");
    if(f == NULL) {
        return -1;
    }
    int result = 0, c;
    while(!feof(f)) {
        c = fgetc(f);
        if(c == 10) {
            ++result;
        }
    }
    fclose(f);
    return result;
}
