/*
    Exercise: 1-21 in K&R2 C book. 
    Author: Ahmed Alaa
*/

#include <stdio.h>


#define TAP_STOP_DIST 8     /* There is a tap stop every 5 columns, at columns 0, 5, 10, 15, ... */
#define IN 1                /* Indicate that We are inside a spaces sequence that didn't end yet */ 
#define OUT 0               /* Indicate that There is no spaces sequence which didn't completely processed */ 
#define TAP_CHAR '\t'        
#define NEW_LINE_CHAR '\n'
#define SPACE_CHAR ' '



int update_col_pos(int col_pos, int ch); 
void process_space_seq(int start_pos, int end_pos);     /* replace the sequence of spaces [start_pos, end_pos) by the min number of tabs and blanks */
int find_next_tap_stop_pos(int col_pos);                


int main (void)
{
    int ch, col_pos, start_pos, end_pos, state;

    col_pos = 0; 
    state = OUT; 
    while ( (ch = getchar()) != EOF) {
        if (ch == SPACE_CHAR) {
            if (state == OUT) {
                state = IN; 
                start_pos = col_pos; 
            }
        }
        else {
            if (state == IN) {
                state = OUT; 
                end_pos = col_pos; 
                process_space_seq(start_pos, end_pos);
            }
            putchar(ch);
        }
        col_pos = update_col_pos(col_pos, ch); 
    }

    return 0; 
}   


int update_col_pos(int col_pos, int ch) 
{
    int new_col_pos;     
    switch (ch)
    {
    case NEW_LINE_CHAR:
        new_col_pos = 0; 
        break;
    case TAP_CHAR:
        new_col_pos = find_next_tap_stop_pos(col_pos);
        break;
    default:
        new_col_pos = col_pos + 1; 
        break;
    }

    return new_col_pos; 
}


void process_space_seq(int start_pos, int end_pos) 
{
    // if the sequence is only 1 space character then we just print it 
    // So, we prefer printing space instead of tap char when both lead to the next tab stop. 
    // reason, to not get a VERY different output when we change TAP_STOP_DIST 



    int next_tap_stop_pos; 
    while (start_pos < end_pos) {
        next_tap_stop_pos = find_next_tap_stop_pos(start_pos); 
        if (next_tap_stop_pos <= end_pos) {
            // We prefer space char to tap char, in case when, both move us to the next tap stop
            if (next_tap_stop_pos - start_pos == 1) 
                putchar(SPACE_CHAR); 
            else 
                putchar(TAP_CHAR); 

            start_pos = next_tap_stop_pos;
        }
        else {
            while (start_pos++ < end_pos) 
                putchar(SPACE_CHAR);
        }
    }
}

int find_next_tap_stop_pos(int col_pos) 
{
    return col_pos / TAP_STOP_DIST * TAP_STOP_DIST + TAP_STOP_DIST; 
}              
