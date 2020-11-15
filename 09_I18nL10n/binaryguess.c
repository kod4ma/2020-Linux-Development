#include <stdio.h>
#include <libintl.h>
#include <locale.h>

#define _(STRING) gettext(STRING)

int main() {
    int l = 1, r = 100;
    char answer;

    setlocale (LC_ALL, "");
    bindtextdomain ("binaryguess", ".");
    textdomain ("binaryguess");

    printf(_("a number between 1 and 100 should be chosen\n"));

    while(l<r) {
        printf(_("is the number greater than %d? "), (l+r)/2);
        scanf("%c", &answer);
        if(answer == 'y')
        	l = (l+r)/2+1;
        else if(answer == 'n')
            r = (l+r)/2;
    }

    printf(_("the number is %d?\n"), r);
    return 0;
}
