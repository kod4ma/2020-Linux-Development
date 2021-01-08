/** @file */ 

#include <stdio.h>
#include <libintl.h>
#include <locale.h>
#include <string.h>
#include <stdbool.h>


#define _(STRING) gettext(STRING)

//! The number of Roman numerals.
#define ROMAN_SIZE 100

//! An array of roman numerals (from 1 to 100) generated using python.
static char  *roman[] ={"I","II","III","IV","V","VI","VII","VIII","IX","X","XI","XII","XIII","XIV","XV",
                        "XVI","XVII","XVIII","XIX","XX","XXI","XXII","XXIII","XXIV","XXV","XXVI","XXVII",
                        "XXVIII","XXIX","XXX","XXXI","XXXII","XXXIII","XXXIV","XXXV","XXXVI","XXXVII","XXXVIII",
                        "XXXIX","XL","XLI","XLII","XLIII","XLIV","XLV","XLVI","XLVII","XLVIII","XLIX","L","LI",
                        "LII","LIII","LIV","LV","LVI","LVII","LVIII","LIX","LX","LXI","LXII","LXIII","LXIV",
                        "LXV","LXVI","LXVII","LXVIII","LXIX","LXX","LXXI","LXXII","LXXIII","LXXIV","LXXV",
                        "LXXVI","LXXVII","LXXVIII","LXXIX","LXXX","LXXXI","LXXXII","LXXXIII","LXXXIV","LXXXV",
                        "LXXXVI","LXXXVII","LXXXVIII","LXXXIX","XC","XCI","XCII","XCIII","XCIV","XCV","XCVI",
                        "XCVII","XCVIII","XCIX","C"};

/*!Functions converts an Arabic numeral to a Roman numeral.
    IN: int(Arabic numeral)
    OUT: cher *(Roman numeral)
*/
char * arabic_to_roman(int i){
    return roman[i - 1];
}

/*!Functions converts a Roman numeral to an Arabic numeral.
    IN:  cher *(Roman numeral)
    OUT: int(Arabic numeral)
*/
int roman_to_arabic(char * str){
    int out = 0;
    for(int i = 0; i < ROMAN_SIZE; i++){
        if(strcmp(roman[i], str) == 0){
            out = i+1;
            break;
        }
    }
    return out;
}

int main(int argc, char *argv[]) {
    int l = 1, r = 100;
    char answer;
    char tmp;
    bool is_roman = false;
    printf("%d\n", argc);

    if(argc > 1){
        if(strcmp(argv[1], "-r") == 0){
            is_roman = true;
        }

    }
    printf("%d\n", is_roman);

    setlocale (LC_ALL, "");
    bindtextdomain ("binaryguess", ".");
    textdomain ("binaryguess");
    if(is_roman){
        printf(_("a number between I and C should be chosen\n"));
    }else{
        printf(_("a number between 1 and 100 should be chosen\n"));
    }

    while(l<r) {
        if(is_roman){
            printf(_("is the number greater than %s?\n"), arabic_to_roman((l+r)/2));
        }else{
            printf(_("is the number greater than %d?\n"), (l+r)/2);
        }
        scanf("%c%c", &answer, &tmp);
        if(answer == 'y')
        	l = (l+r)/2+1;
        else if(answer == 'n')
            r = (l+r)/2;
    }
    printf("%s\n", arabic_to_roman(r));
    printf("%d\n", roman_to_arabic(arabic_to_roman(r)));
    if(is_roman){
         printf(_("the number is %s?\n"), arabic_to_roman(r));

    }else{
        printf(_("the number is %d?\n"), r);
    }
    return 0;
}
