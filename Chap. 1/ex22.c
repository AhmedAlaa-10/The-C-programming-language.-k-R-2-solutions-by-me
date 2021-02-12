/*
    Exercise: 1-22 in k&R2 book 
    By Ahmed Alaa
*/

#include <stdio.h> 

#define LINE_MAX_SIZE 21        /* The maximum number of columns allowed in a single line */
#define IN_NON_BLANK_SEQ 1      /* Indicate that a sequence of non-blank character are being processed */ 
#define TAP_STOP_DIST 5

#define NON_BLANK(ch)   (ch != '\t' && ch != '\n' && ch != ' ') 

int get_next_tap_pos(int current_column) {
    // columns numbered 0, 1, 2... there is a tap stop at 0, 5, 10, 15, 20
    return current_column / TAP_STOP_DIST * TAP_STOP_DIST + TAP_STOP_DIST; 
}

int main(void) 
{
    char block[LINE_MAX_SIZE+1];
    int column_pos = 0;                 /* Indicate the current column in the output where the next character will be printed*/
    int index_non_blank = 0;            /* Indicate the number of the non-blank char in the next non-blank char sequence */ 
    int state = !IN_NON_BLANK_SEQ;      /* Indicate whether a non-blank character is being processed */ 

    int ch; 
    while ( (ch = getchar()) != EOF) {
        if (NON_BLANK(ch)) {

            state = IN_NON_BLANK_SEQ; 
            if (index_non_blank == LINE_MAX_SIZE) {
                // There is a word bigger than the size of the line
                block[LINE_MAX_SIZE] = '\0'; 
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
            if (state == IN_NON_BLANK_SEQ) {
                // Should the current word be printed in the current line or next line ?
                block[index_non_blank] = '\0'; 
                int expected_column_num = column_pos + index_non_blank; 
                if (expected_column_num <= LINE_MAX_SIZE) {
                    printf("%s", block); 
                    column_pos = expected_column_num; 
                }
                else {
                    putchar('\n'); 
                    printf("%s", block); 
                    column_pos = index_non_blank; 
                }

                state = !IN_NON_BLANK_SEQ;  
                index_non_blank = 0; 
            }
            // now print the whitespace character and update column position 
            if (ch == '\n') {
                putchar(ch); 
                column_pos = 0; 
            }
            else if (ch == ' ' && column_pos < LINE_MAX_SIZE) {
                putchar(ch); 
                ++column_pos; 
            }
            else if (ch == '\t' && column_pos < LINE_MAX_SIZE) {
                putchar(ch); 
                column_pos = get_next_tap_pos(column_pos); 
            }
            else {
                putchar('\n');
                column_pos = 0;  
            }
        }
    }
}
