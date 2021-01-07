#define PCRE2_CODE_UNIT_WIDTH 8
#include <ncurses.h>
#include <pcre2.h> 
#include <string.h>
#include <locale.h>

#define MAXSTR 80
#ifdef WITHOUT_UTF
#define PCRE_OPTIONS 0
#else
#define PCRE_OPTIONS PCRE2_UCP
#endif


int pcredemo(WINDOW *win, char *str1, char* str2){
    pcre2_code *re;
    PCRE2_SPTR pattern;     /* PCRE2_SPTR is a pointer to unsigned code units of */
    PCRE2_SPTR subject;     /* the appropriate width (in this case, 8 bits). */

    int errnum;
    int i, rc;

    PCRE2_SIZE erroffs;
    PCRE2_SIZE *ovector;
    PCRE2_SIZE subject_length;

    pcre2_match_data *match_data;

    pattern = (PCRE2_SPTR)str1;
    subject = (PCRE2_SPTR)str2;
    subject_length = (PCRE2_SIZE)strlen((char *)subject);

    re = pcre2_compile(pattern, PCRE2_ZERO_TERMINATED, PCRE2_UCP, &errnum, &erroffs, NULL);

    if (re == NULL) {
        PCRE2_UCHAR buffer[256];
        pcre2_get_error_message(errnum, buffer, sizeof(buffer));
        wprintw(win, " PCRE2 compilation failed at offset %d: %s\n", (int)erroffs,
               buffer);
        return 1;
    }

    match_data = pcre2_match_data_create_from_pattern(re, NULL);

    rc = pcre2_match(re, subject, subject_length, 0, 0, match_data, NULL);

    if (rc < 0) {
        switch(rc) {
        case PCRE2_ERROR_NOMATCH:
            wprintw(win," No match\n");
            break;
        default:
            wprintw(win," Matching error %d\n", rc);
            break;
        }
        pcre2_match_data_free(match_data);   /* Release memory used for the match */
        pcre2_code_free(re);                 /*   data and the compiled pattern. */
        return 1;
    }

    ovector = pcre2_get_ovector_pointer(match_data);

    for (i = 0; i < rc; i++)
        wprintw(win, " %2ld: %.*s\n", ovector[2*i], 
                 (int)(ovector[2*i+1] - ovector[2*i]),
                 subject + ovector[2*i]);

    pcre2_match_data_free(match_data);  /* Release the memory that was used */
    pcre2_code_free(re);                /* for the match data and the pattern. */

    return 0;

}

WINDOW* create_newwin(int height,int width,int starty,int startx) {
    WINDOW *local_win;
    local_win = newwin(height,width,starty,startx);
    box(local_win,0,0);
    wrefresh(local_win);
    return local_win;
}

void clean_wind(WINDOW* wind){
    werase(wind); 
    box(wind, 0, 0);
    wrefresh(wind);
}



int main()
{
    setlocale(LC_ALL, "");
    const int height = 3;
    initscr();
    refresh();

    WINDOW *win0 = create_newwin(LINES - height*3, COLS -2*height + 2, height*2, height);
    WINDOW *win1 = create_newwin(height,(COLS -2*height)/2, height, height);
    WINDOW *win2 = create_newwin(height, (COLS -2*height)/2,height, height + (COLS -2*height)/2 + 2);
    char str[MAXSTR], str1[MAXSTR];
    keypad(win1, TRUE);
    keypad(win2, TRUE);
    scrollok (win0, TRUE);
    wmove(win0, 1, 0);
    do{
    clean_wind(win2);
    clean_wind(win1);
    mvwgetnstr(win1, 1, 1, str, (COLS -2*height)/2  - 2);
    if(!*str){
        break;
    }
    mvwgetnstr(win2, 1, 1, str1, (COLS -2*height)/2 - 2);
    wprintw(win0," Entered: %s : %s\n", str, str1);
    pcredemo(win0, str, str1);
    box(win0, 0, 0);
    wrefresh(win0);

    }while(*str);
    endwin();
}

