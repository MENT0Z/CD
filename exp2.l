%{
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int line_no = 1;  // Track line numbers

void print_token(const char* type, const char* value) {
    static int token_count = 1;  // Token numbering
    printf("%d %d %s %s\n", token_count++, line_no, type, value);
}
%}

%option noyywrap

DIGIT    [0-9]
ID       [a-zA-Z_][a-zA-Z0-9_]*
KEYWORDS int|main|return|if|then|begin|end|procedure|function
OPERATORS "+"|"-"|"*"|"/"|"="|"=="|"!="|"<"|">"|"<="|">="|"&&"|"||"|"!"
SPECIAL  [.;,()\[\]{}]

%%

// Keywords
{KEYWORDS} { print_token("keyword", yytext); }

// Identifiers (variable names, function names)
{ID} { print_token("identifier", yytext); }

// Integer Constants
{DIGIT}+ { print_token("constant", yytext); }

// Floating-point Constants
{DIGIT}+"."{DIGIT}+ { print_token("float", yytext); }

// Operators
{OPERATORS} { print_token("operator", yytext); }

// Special symbols (punctuation, separators)
{SPECIAL} { print_token("special symbols", yytext); }

// String literals
\"[^\"]*\" { print_token("string", yytext); }

// Character literals
'[a-zA-Z0-9]' { print_token("character", yytext); }

// Comments (Ignored)
"//".* { }
"/*"[^*]*"*/" { }

// Newlines
\n { line_no++; }

// Ignore whitespace and tabs
[ \t]+ { }

// Unrecognized characters
. { print_token("unrecognized", yytext); }

%%

int yywrap() { return 1; }

int main() {
    FILE *fp;
    char filename[50];

    printf("Enter the filename: \n");
    scanf("%s", filename);

    fp = fopen(filename, "r");
    if (!fp) {
        printf("Error opening file.\n");
        return 1;
    }

    yyin = fp;  // Set input source to file
    yylex();    // Start lexical analysis

    fclose(fp); // Close file
    return 0;
}
