Here are the Flex (Lex) programs for each of your requirements:

### 1. **Flex program to identify the identifier or not**
```flex
%{
#include <stdio.h>
%}

%%
[a-zA-Z_][a-zA-Z0-9_]*    { printf("Identifier: %s\n", yytext); }
.                          { printf("Not an identifier: %s\n", yytext); }

%%

int main() {
    yylex();
    return 0;
}

int yywrap() {
    return 1;
}
```

---

### 2. **Flex program to find a vowel or not**
```flex
%{
#include <stdio.h>
%}

%%
[aeiouAEIOU]    { printf("Vowel: %s\n", yytext); }
.               { printf("Not a vowel: %s\n", yytext); }

%%

int main() {
    yylex();
    return 0;
}

int yywrap() {
    return 1;
}
```

---

### 3. **Flex Program to count the number of lines and characters**
```flex
%{
#include <stdio.h>
int lines = 0, characters = 0;
%}

%%
\n      { lines++; characters++; }
.       { characters++; }

%%

int main() {
    yylex();
    printf("Lines: %d, Characters: %d\n", lines, characters);
    return 0;
}

int yywrap() {
    return 1;
}
```

---

### 4. **Flex code to count total number of characters**
```flex
%{
#include <stdio.h>
int characters = 0;
%}

%%
.       { characters++; }

%%

int main() {
    yylex();
    printf("Total Characters: %d\n", characters);
    return 0;
}

int yywrap() {
    return 1;
}
```

---

### 5. **Flex Program to count number of words**
```flex
%{
#include <stdio.h>
int words = 0;
%}

%%
[^\t\n ]+    { words++; }
\n|[ \t]     {}

%%

int main() {
    yylex();
    printf("Total Words: %d\n", words);
    return 0;
}

int yywrap() {
    return 1;
}
```

---

### 6. **Flex program to count the number of lines, spaces, and tabs**
```flex
%{
#include <stdio.h>
int lines = 0, spaces = 0, tabs = 0;
%}

%%
\n      { lines++; }
" "     { spaces++; }
"\t"    { tabs++; }

%%

int main() {
    yylex();
    printf("Lines: %d, Spaces: %d, Tabs: %d\n", lines, spaces, tabs);
    return 0;
}

int yywrap() {
    return 1;
}
```

---

### 7. **Flex program to count the frequency of the given word in a file**
```flex
%{
#include <stdio.h>
int count = 0;
#define WORD "hello"  // Change this to any word you want to count
%}

%%
{WORD}   { count++; }

%%

int main() {
    yylex();
    printf("Frequency of '%s': %d\n", WORD, count);
    return 0;
}

int yywrap() {
    return 1;
}
```

---

### 8. **Flex program to add line numbers to a given file**
```flex
%{
#include <stdio.h>
int line_num = 1;
%}

%%
^.*\n    { printf("%d: %s", line_num++, yytext); }

%%

int main() {
    yylex();
    return 0;
}

int yywrap() {
    return 1;
}
```

---

### 9. **Flex Program to find an uppercase and lowercase letter**
```flex
%{
#include <stdio.h>
%}

%%
[A-Z]   { printf("Uppercase letter: %s\n", yytext); }
[a-z]   { printf("Lowercase letter: %s\n", yytext); }
.       {}

%%

int main() {
    yylex();
    return 0;
}

int yywrap() {
    return 1;
}
```

---

### 10. **Flex program to check if the given string is a digit or word**
```flex
%{
#include <stdio.h>
%}

%%
[0-9]+     { printf("Digit: %s\n", yytext); }
[a-zA-Z]+  { printf("Word: %s\n", yytext); }

%%

int main() {
    yylex();
    return 0;
}

int yywrap() {
    return 1;
}
```

---

### 11. **Flex program to check if it is a well-formed parenthesis or not**
```flex
%{
#include <stdio.h>
int balance = 0;
%}

%%
"("   { balance++; }
")"   { balance--; }

%%

int main() {
    yylex();
    if (balance == 0)
        printf("Well-formed parenthesis\n");
    else
        printf("Not well-formed\n");
    return 0;
}

int yywrap() {
    return 1;
}
```

---

### 12. **Flex program to implement positive closure (`(a+)+` matches sequences of 'a')**
```flex
%{
#include <stdio.h>
%}

%%
(a+)+   { printf("Positive closure match: %s\n", yytext); }

%%

int main() {
    yylex();
    return 0;
}

int yywrap() {
    return 1;
}
```

---

### 13. **Flex code to count total number of tokens**
```flex
%{
#include <stdio.h>
int tokens = 0;
%}

%%
.   { tokens++; }

%%

int main() {
    yylex();
    printf("Total Tokens: %d\n", tokens);
    return 0;
}

int yywrap() {
    return 1;
}
```

---

### 14. **Flex Program to Identify and Count Positive and Negative Numbers**
```flex
%{
#include <stdio.h>
int positive = 0, negative = 0;
%}

%%
[+-]?[0-9]+ {
    if (yytext[0] == '-')
        negative++;
    else
        positive++;
}

%%

int main() {
    yylex();
    printf("Positive Numbers: %d, Negative Numbers: %d\n", positive, negative);
    return 0;
}

int yywrap() {
    return 1;
}
```

---

### 15. **Flex program to identify operators or not**
```flex
%{
#include <stdio.h>
%}

%%
[+\-*/%]   { printf("Operator: %s\n", yytext); }
.          { printf("Not an operator: %s\n", yytext); }

%%

int main() {
    yylex();
    return 0;
}

int yywrap() {
    return 1;
}
```

---

These programs are written in Flex (Lex) and can be compiled using:
```bash
lex program.l
gcc lex.yy.c -o output -ll
./output
```
Let me know if you need modifications! 🚀
