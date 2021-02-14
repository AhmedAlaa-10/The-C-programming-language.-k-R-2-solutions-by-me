/*
  Thanks to feedback from Toby Speight 
  https://codereview.stackexchange.com/questions/255915/the-solution-for-the-exercise-1-22-from-the-book-the-c-programming-language-k/255917#255917
*/

#include <stdio.h> 
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>


#define TAB_STOP_DIST 8         /* There is a tab stop each 8 columns */ 



int get_next_tap_pos(int current_column) {
    // columns numbered 0, 1, 2... there is a tap stop at 0, 5, 10, 15, 20
    return current_column / TAB_STOP_DIST * TAB_STOP_DIST + TAB_STOP_DIST; 
}

int main(int argc, char **argv)
{
    // check program usage 
    if (argc < 2 ) {
        printf("Usage: ./a.out lineSize\n");
        printf("Note: lineSize is an integer > 0\n"); 
        return 0; 
    }
    int line_max_size = atoi(argv[1]); 
    if (line_max_size <= 0) {
        printf("Usage: ./a.out lineSize\n");
        printf("Note: lineSize is an integer > 0\n"); 
        return 0;
    }

    
    char block[line_max_size+1];
    unsigned int column_pos = 0;                 /* Indicate the current column in the output where the next character will be printed*/
    unsigned int index_non_blank = 0;            /* Indicate the number of the non-blank char in the next non-blank char sequence */ 

    int ch; 
    while ( (ch = getchar()) != EOF) {
        if ( ! isspace(ch)) {
            if (index_non_blank == line_max_size) {
                // There is a word bigger than the size of the line
                block[line_max_size] = '\0'; 
                // Should I print it in the current line or in the next line ?
                // Our word is as big as our line. so if current line is not empty, we can't print it here
                if (column_pos != 0) 
                    putchar('\n');
                printf("%s\n", block); 
                column_pos = 0; 
                index_non_blank = 0;
                block[index_non_blank] = ch;  
            }
            else {
                block[index_non_blank] = ch; 
                ++index_non_blank; 
            }
        }
        else {
            // Is there a non-blank sequence that just finished ?
            if (index_non_blank) { // if index_noon_blank > 0, then there is a non-blank sequence to be processed ?
                // Should the current word be printed in the current line or next line ?
                block[index_non_blank] = '\0'; 
                int expected_column_num = column_pos + index_non_blank; 
                if (expected_column_num <= line_max_size) {
                    printf("%s", block); 
                    column_pos = expected_column_num; 
                }
                else {
                    putchar('\n'); 
                    printf("%s", block); 
                    column_pos = index_non_blank; 
                }
                index_non_blank = 0; 
            }
            // now print the whitespace character and update column position 
            if (ch == '\n') {       // handling new line
                putchar(ch); 
                column_pos = 0; 
            }
            else if (ch == ' ' && column_pos < line_max_size) { // handling space character
                putchar(ch); 
                ++column_pos; 
            }
            else if (ch == '\t' && column_pos < line_max_size) { // handling tab character
                putchar(ch); 
                column_pos = get_next_tap_pos(column_pos); 
            }
            else {
                putchar('\n');
                column_pos = 0;  
            }
        }
    }

    return 0; 
}
