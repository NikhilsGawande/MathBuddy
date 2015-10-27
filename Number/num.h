typedef struct Number {
	char sign;
	char *integer;
	char *fraction;
}Number;

void initNumber(Number *a);
Number CreateNumber(Number num);
void PrintNumber(Number );
Number AddNumber(Number a , Number b);
char* AddInteger(Number a , Number b);
char* AddFraction(Number a, Number b) ;
char *appendleft(int a, char *str);

Number SubNumber(Number a , Number b);
int CompareNumber(Number a, Number b) ;
Number CreateNumberFromString(char *str);


Number MulNumber(Number a , Number b);
Number DivNumber(Number a , Number b);
Number power(Number a , Number b);
