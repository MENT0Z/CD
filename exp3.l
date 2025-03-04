%{
#include "y.tab.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
%}

%option noyywrap

%%

[0-9]+(\.[0-9]+)?   { yylval.num = atof(yytext); return NUMBER; }
"sin"               { return SIN; }
"cos"               { return COS; }
"tan"               { return TAN; }
"asin"              { return ASIN; }
"acos"              { return ACOS; }
"atan"              { return ATAN; }
"sinh"              { return SINH; }
"cosh"              { return COSH; }
"tanh"              { return TANH; }
"cot"               { return COT; }
"log"               { return LOG; }
"log10"             { return LOG10; }
"log2"              { return LOG2; }
"log3"              { return LOG3; }
"log5"              { return LOG5; }
"exp"               { return EXP; }
"sqrt"              { return SQRT; }
"cqrt"              { return CQRT; }
"abs"               { return ABS; }
"fabs"              { return FABS; }
"ceil"              { return CEIL; }
"floor"             { return FLOOR; }
"pow"               { return POW; }
"+"                 { return '+'; }
"-"                 { return '-'; }
"*"                 { return '*'; }
"/"                 { return '/'; }
"("                 { return '('; }
")"                 { return ')'; }
"\n"                { return 0; }
[ \t]               { /* Ignore whitespace */ }
.                   { printf("Unrecognized character: %s\n", yytext); }

%%

int yywrap() { return 1; }

%{
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void yyerror(const char *s);
int yylex();
%}

%union {
    double num;
}

%token <num> NUMBER
%token SIN COS TAN ASIN ACOS ATAN SINH COSH TANH COT
%token LOG LOG10 LOG2 LOG3 LOG5 EXP SQRT CQRT ABS FABS CEIL FLOOR POW

%left '+' '-'
%left '*' '/'
%right SIN COS TAN ASIN ACOS ATAN SINH COSH TANH COT
%right LOG LOG10 LOG2 LOG3 LOG5 EXP SQRT CQRT ABS FABS CEIL FLOOR POW

%%

input:
    | input line
    ;

line:
    expr '\n' { printf("Result: %g\n", $1); }
    ;

expr:
    NUMBER { $$ = $1; }
    | expr '+' expr { $$ = $1 + $3; }
    | expr '-' expr { $$ = $1 - $3; }
    | expr '*' expr { $$ = $1 * $3; }
    | expr '/' expr { 
        if ($3 == 0) {
            yyerror("Division by zero!");
            $$ = 0;
        } else {
            $$ = $1 / $3;
        }
    }
    | POW '(' expr ',' expr ')' { $$ = pow($3, $5); }
    | SIN expr { $$ = sin($2); }
    | COS expr { $$ = cos($2); }
    | TAN expr { $$ = tan($2); }
    | ASIN expr { $$ = asin($2); }
    | ACOS expr { $$ = acos($2); }
    | ATAN expr { $$ = atan($2); }
    | SINH expr { $$ = sinh($2); }
    | COSH expr { $$ = cosh($2); }
    | TANH expr { $$ = tanh($2); }
    | COT expr { $$ = 1 / tan($2); }
    | LOG expr { $$ = log($2); }
    | LOG10 expr { $$ = log10($2); }
    | LOG2 expr { $$ = log2($2); }
    | LOG3 expr { $$ = log($2) / log(3); }
    | LOG5 expr { $$ = log($2) / log(5); }
    | EXP expr { $$ = exp($2); }
    | SQRT expr { $$ = sqrt($2); }
    | CQRT expr { $$ = cbrt($2); }
    | ABS expr { $$ = fabs($2); }
    | FABS expr { $$ = fabs($2); }
    | CEIL expr { $$ = ceil($2); }
    | FLOOR expr { $$ = floor($2); }
    | '(' expr ')' { $$ = $2; }
    ;

%%

void yyerror(const char *s) {
    fprintf(stderr, "Error: %s\n", s);
}

int main() {
    printf("Enter expression:\n");
    return yyparse();
}
