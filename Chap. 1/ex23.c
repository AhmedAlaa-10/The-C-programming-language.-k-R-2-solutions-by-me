/*
  Exercise 1-23: write program that will remove every comment from a C program
  By Ahmed Alaa 
*/ 

#include <stdio.h>
#include <stdbool.h>

#define DOUBLE_QUOTE_CHAR '"'
#define BASK_SLASH '\\'
#define NEW_LINE_CHAR '\n'
#define FORWARD_SLASH '/'
#define ASTERISK '*'
#define SINGLE_QUOTE_CHAR '\''

void print_quoted_string();     /* called when a quote char that indicate begining of string is encountered. print the quoated string then stop */ 
void skip_single_line_comment(); /* called when we see // that indicate start of a single-line comment . skip that comment */ 
void skip_multiple_line_comment();  

int main(void)
{
    char cur_char; 
    bool prev_forward_slash = false;    // to handle //, /*
    bool prev_single_quote = false;     // to handle '"' 
    bool prev_back_slash = false;       // to handle '\"' 

    while ( (cur_char = getchar()) != EOF) {
        if (cur_char == DOUBLE_QUOTE_CHAR && !prev_single_quote && !prev_back_slash) // to exclude '"' and '\"'. Are there any other casse ? 
            print_quoted_string(); 
        else if (prev_forward_slash && cur_char == FORWARD_SLASH) { // this // can not be inside a string. because the first if statement guarentee it.
            skip_single_line_comment();
            prev_forward_slash = false; 
        } 
        else if (prev_forward_slash && cur_char == ASTERISK ) {
            skip_multiple_line_comment(); 
            prev_forward_slash = false; 
        }
        else {
            if (prev_forward_slash) 
                putchar(FORWARD_SLASH);  // since we don't print a forward slash until we read the character after it. 

            if (cur_char == FORWARD_SLASH)    // we should not print this forward slash now since it may be followed by * 
                prev_forward_slash = true;    
            else if (cur_char == SINGLE_QUOTE_CHAR) {
                prev_single_quote = true; 
                putchar(cur_char);
            }
            else if (cur_char == BASK_SLASH) {
                prev_back_slash = true;
                putchar(cur_char);
            } 
            else {
                prev_single_quote = prev_forward_slash =  prev_back_slash = false;
                putchar(cur_char); 
            }
        }
    }

    return 0; 
}


void print_quoted_string()
{
    putchar(DOUBLE_QUOTE_CHAR);   /* print the start quote of the string */ 

    bool prev_char_is_escape_char = false;  /* used to handle the escape sequences issues. for example:  "\\" , "\"", "\\\\\"" */ 
    char cur_char;
    while (1) {
        cur_char = getchar(); 
        
        if (cur_char == DOUBLE_QUOTE_CHAR && !prev_char_is_escape_char)    /* this quote char is the end quote of the string */ 
            break; 
        
        putchar(cur_char);

        /* current char is an escape char iff it's a back slash and not proceeded by escape char */ 
        prev_char_is_escape_char = (cur_char == BASK_SLASH && !prev_char_is_escape_char); 
    }

    putchar(DOUBLE_QUOTE_CHAR);    /* print the end quote of the string */
}

void skip_single_line_comment()
{
    while (getchar() != NEW_LINE_CHAR); 
    putchar(NEW_LINE_CHAR);
}

void skip_multiple_line_comment()
{
    char prev_char = '/'; 
    char cur_char = '*'; 

    while (1) {
        char cur_char = getchar(); 

        if (prev_char == '*' && cur_char == '/') {
            putchar(NEW_LINE_CHAR); 
            return; 
        }

        prev_char = cur_char; 
    }
}


