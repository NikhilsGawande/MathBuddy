#include <stdio.h>
#include <string.h> 
#include "num.h"
void printmenu() {
	printf("1. add :");
	printf("2. sub :");
	printf("3. mul :");

}
int main() {
 	Number a, b , c;
 	int choice;
 	
	printmenu();	
 	while(scanf("%d", &choice) != EOF) {
		switch(choice) {
			case 1 : 
			 	a = CreateNumber(a);
				b = CreateNumber(b);
				c = AddNumber(a , b);
				PrintNumber(c);
			break;	
			case 2 : 
			 	a = CreateNumber(a);
				b = CreateNumber(b);
				printf("\n a is " ) ; PrintNumber(a);
				printf("\n b is " ) ; PrintNumber(b);
					
				c = SubNumber(a , b);
				PrintNumber(c);
			break;
			case 3:
			 	a = CreateNumber(a);
				b = CreateNumber(b);
				c = MulNumber(a , b);
				PrintNumber(c);
			break;
		}
	}	
	return 0;
	
}

