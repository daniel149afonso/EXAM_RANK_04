// Assignment name:		vbc
// Expected files:		*.c *h
// Allowed functions:	malloc, calloc, realloc, free, printf, isdigit, write

// Write a program that prints the result of a mathematical expression given as argument.
// It must handle addition, multiplication and parenthesis. All values are between 0 and 9 included.
// In case of an unexpected symbol, you must print "Unexpected token '%c'\n".
// If the expression ends unexpectedly, you must print "Unexpected end of input\n".
// The same rule applies if finding an unexpected '(' or ')'.
// In case of a syscall failure, you must exit with 1.

// Examples:
// $> ./vbc '1' | cat -e
// 1$
// $> ./vbc '2+3' | cat -e
// 5$
// $> ./vbc '3*4+5' | cat -e
// 17$
// $> ./vbc '3+4*5' | cat -e
// 23$
// $> ./vbc '(3+4)*5' | cat -e
// 35$
// $> ./vbc '(((((2+2)*2+2)*2+2)*2+2)*2+2)*2' | cat -e
// 188$
// $> ./vbc '1+'
// Unexpected end of input
// $> ./vbc '1+2)' | cat -e
// Unexpected token ')'$

// File provided: vbc.c, see below.