
typedef struct node {
	int digit;
	struct node *next , *prev;
}node;
typedef struct integer {
	struct node *head, *tail;
	int length;
	char sign;
}integer;

void iappend(integer *l, int a) ;

void iinit(integer *l) ;

void ireverse(integer *l) ;


/* Create and return an Integer from a string. The string can be assumed to be a string of digits */
integer CreateIntegerFromString(char *str);

/* Create and return an Integer by reading a string stored in the file given by fname. The string in the file can be assumed to be a string of digits */
integer CreateIntegerFromFile(char *fname);

/* Given an Integer "a", add a digit at the end of the integer. For exampple if Integer a=1234, and char digit='5', then the function returns Integer=12345 */
integer AddDigitToInteger(integer a, char digit);

/* This function adds two Integers a and b, and returns the sum as Integer */
integer AddIntegers(integer a, integer b);


/* This function substracts two Integers a and b, and returns the sum as Integer */
integer SubstractIntegers(integer a, integer b);


/* This function multiplies two Integers a and b, and returns the sum as Integer*/
integer MultiplyIntegers(integer a, integer b);

/* Print an Integer */
void PrintInteger(integer *a);

