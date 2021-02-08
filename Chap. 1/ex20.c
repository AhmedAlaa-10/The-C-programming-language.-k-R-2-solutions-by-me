#include <stdio.h>

/* 
    Please notice that I am writing this for my practice, thus I may do things just for practice.  
    Also, there may be mistakes. 
    Author: Ahmed Alaa
*/ 

#define TAP_STOP 5          /* There is a tap stop every TAP_STOP columns. Exactly at columns 0, 5, 10, .. if TAP_STOP = 5 */ 
#define SPACE ' '           /* A space character */
#define TAP '\t'            /* A tab character */ 
#define NEW_LINE '\n'       /* A new line character */ 

#define CALC_NUM_SPACE(pos) (TAP_STOP - (pos % TAP_STOP))   /* Calc the number of spaces to replace the tab char. given that the current column is at pos */

/*
    Program: detab 
    Replace each tab ('\t') character with the proper number of blanks to space to the next tab stop. 
*/
int main(void)
{   
    int ch;         /* Store the last character that was read from the input */ 
    int pos;        /* Store the number of the column in the current line, zero-indexed */ 
    int num_space;  /* Store the proper number of blanks to replace the last tab that was read from the input */  

    pos = 0;
    while ( (ch = getchar()) != EOF) {
        if (ch == TAP) {
            num_space = CALC_NUM_SPACE(pos);      
            while (num_space--) {       
                putchar(SPACE);
                ++pos; 
            }
        }
        else if (ch == NEW_LINE) {
            putchar(ch);
            pos = 0; 
        }
        else {
            putchar(ch); 
            ++pos; 
        }
    }   


    return 0; 
}
