#include <stdlib.h> 
#include <stdio.h> 
#include <string.h>
#include<ctype.h>
//#include "num.h"
#include "numstack.h"
void initNumber(Number *a) {
	a->sign = '+';
	a->integer = NULL;
	a->fraction = NULL;
}
char *getstring() {
	char *str;
	str = NULL;
	char d;
	int SIZE = 16, count = 0;
	str = (char *)malloc(SIZE);
	int i = 0;
	printf("Please enter Number:");
	while(scanf("%c", &d) != EOF ) {
		str[count] = d;
		count++;
		if(count == SIZE) {
			SIZE *= 2;
			str = (char *)realloc(str, SIZE);
			if(str == NULL) {
				printf("Failed for %d\n", SIZE);
				exit(1);
			}
		}
	}
	str[count] = '\0';	
	return str;
}
Number CreateNumber(Number num) {
	char *str, *a ;
	int ssize;
	str = NULL;
	str = getstring();
//	printf("\n str is %s" , str);
	ssize = strlen(str);
	a =(char *)malloc(strlen(str) + 1);
	strcpy(a, str);
//	printf("\n a is %s" , a);
	free(str);
//	num = (Number *)malloc(sizeof(Number));
	int space = 0, i, asize, sign = 0;
	initNumber(&num);
	for(i = 0;  i < ssize; i++) {
		if(a[i] == ' ') {
			if (space == 2) {
				printf("Invalid"); 
				return num;
			}
			space = 1;
		}
		else if (a[i] == '+') {
			if(space == 2 || sign == 1 ) {
				printf("Invalid"); 
				return num;
			}
			else { 
				num.sign = '+';
				sign = 1;
			}
		}
		else if (a[i] == '-') {
			if(space == 2 || sign == 1) {
				printf("Invalid"); 
				return num;
			}
			else { 
				num.sign = '-';
				sign = 1;
			}
		}
		
		else if(isalnum(a[i]) && (space == 1 || space == 0)) { 
			num.integer = &a[i];
			space = 2;
		}
		else if (a[i] == '.') 	
			num.fraction  = &a[i];
/*		else {
			printf("Invalid"); 
			return NULL;
		}
*/	}
	if(num.fraction == NULL) {
		num.fraction = &a[i];
	}

	if(sign == 0) 
		num.sign = '+';
	
	return num;
}
void PrintNumber(Number a) {
	printf("\n Number :");
	printf("%c" , a.sign);
	printf("%s" , a.integer);
//	printf("\n fraction :");
//	printf("%s" , a.fraction);

}
Number AddNumber(Number a , Number b) {
	char *p, *q;
	int psize = 0, qsize = 0, i;
	char dot[2];
	dot [0] = '.';
	dot[1] = '\0';
	Number c; 
	initNumber(&c);
	p = AddInteger(a, b);	
//	printf("\nAdd integer is = %s", p);
	q = AddFraction(a, b);
	
	if(q) {
		psize = strlen(p);
		qsize = strlen(q);
		p = (char *)realloc(p , (psize + qsize + 4));
		strcat(p, dot);
		strcat(p, q);
		psize = strlen(p);
		for(i = 0; i < psize;  i++) {
			if(p[i] == '.' ) 
				c.fraction = &p[i];
		}
	}
	c.integer = p;
	return c;
}
char* AddInteger(Number a , Number b) {
	int x, y, z, carry, k, i;
	x = y = z = carry = 0;
	int asize = 0 , bsize = 0;
	char *p , *q , *temp, *sum;
	temp = NULL;
	p = a.fraction;
	q = b.fraction;
	*p = '\0' ;
	*q = '\0';
	asize = strlen(a.integer);
	bsize = strlen(b.integer);
	if(asize < bsize) {
		temp = q;
		q = p;
		p = temp;
	}
	sum = (char *)malloc(1);
	*sum = '\0';	
	while((q - b.integer) > 4) {
		*p = '\0';
		*q = '\0';
		p = p - 4;
		q = q - 4;
		x = atoi(p);
		y = atoi(q);
		z = x + y + carry;
		sum = appendleft(z % 10000,  sum);
		carry = z / 10000;
	} 
	if(q != b.integer) {
		*p = '\0';
		*q = '\0';
		k = 1;
		for(i = 0; i < (q - b.integer); i++) {
			k = k * 10;
		}
		p = p - (q - b.integer) ;
		q = b.integer;
		x = atoi(p);
		y = atoi(q);
		z = x + y + carry;
		sum = appendleft(z % k, sum);
		carry = z / k;
	}
	while((p - a.integer) > 4) {
		*p = '\0';
		p = p - 4;
		x = atoi(p);
		z = x + carry ;
		sum = appendleft(z % 10000 , sum);
		carry = z / 10000;
	}
	if(p != a.integer) {
		*p = '\0';
		p = a.integer;
		x = atoi(p);
		sum = appendleft((x + carry), sum);
	}
	return sum;
}
char* AddFraction(Number a, Number b) {
	char *p , *q, *m, *n, *sum;
	int x, y, z, i;
	char zero = '0', null ='\0';
	m = a.fraction;
	n = b.fraction;
	if(m == NULL && n != NULL) {
		n++;
		return n;
	}
	else if(n == NULL && m != NULL) {
		m++;
		return m;
	}
	else if(m == NULL && n == NULL) {
		return NULL;
	}
	
	m++;
	n++;
	x = strlen(m);
	y = strlen(n);
	p = (char *)malloc(x + 1);
	strcpy(p, m);
	q = (char *)malloc(y + 1);
	strcpy(q, n);	
	if(x < y) {
		z = y - x;
		p =(char *)realloc(p, (strlen(p) + z + 1));
		for(i = 0; i < z; i++) 
			strcat(p , &zero);
		strcat(p , &null);
	}
	else if(y < x) {
		z = x - y;
		q =(char *)realloc(q, (strlen(q) + z + 1));
		for(i = 0; i < z; i++) 
			strcat(q , &zero);
		strcat(q , &null);
	}	
	a.integer = p;
	b.integer = q;
	x = strlen(p);
	a.fraction = &p[x];
 	b.fraction = &q[x];
	sum = AddInteger(a, b);
	return sum;
}
char *appendleft(int a, char *str) {
	int i, k;
	i = 0;
	k = 1;
	while(a / k != 0 ) {
		i++;
		k = k * 10;
	}
	str = (char *)realloc(str , (strlen(str) + i + 1));
	if(str == NULL) {	
		printf("Error");
		exit(1);
	}
	char *temp;
	temp = (char *)malloc(strlen(str) + 1) ;
	strcpy(temp, str);
	*str = '\0';
	sprintf(str, "%d", a);
	str[i] = '\0';
	strcat(str, temp);
	free(temp);
	return str;
}
int CompareNumber(Number a, Number b) {
	char *p, *q;
	if((a.fraction - a.integer) > (b.fraction - b.integer)) 
		return 1;
	else if((a.fraction - a.integer) < (b.fraction - b.integer)) 
		return -1;
	else {
		p = a.integer;
		q = b.integer;
		while(p != '\0' && q != '\0') {
			if(*p > *q) 
				return 1;
			else if(*p < *q)
				return -1;
			else {
				p++;
				q++;
			}
		}
	}
	return 0;
}
Number SubNumber(Number a, Number b) {
	Number c, ttemp;
	char * temp, *p, *q;
	int x, y, i, j, borrow, z;
	x = y = i = j = borrow = 0;
	initNumber(&c);
	initNumber(&ttemp);

	int mm, m, n, o;
	mm = CompareNumber(a, b) ;
	if(mm < 1) {
		ttemp = a;
		a = b;
		b = ttemp;
	}
	else if (mm = 0) {
		return c;
	}
	p = a.integer;
	q = b.integer;
	x = strlen(p);
	y = strlen(q);
	p = p + x;
	q = q + y;
	if(x > y) 
		temp = (char* )malloc(x + 1);
	else 
		temp = (char* )malloc(y + 1);
	m = p - a.fraction;
	n = q - b.fraction;
	p--;
	q--;
	if(m > n) {
		o = m - n ;
		for(i = 0; i < o; i++) {
			temp[j++] = *p;
			p--;
		}
	}
	else if (m < n) {
		o = n - m ;
		for(i = 0; i < o; i++) {
			temp[j++] = *q;
			q--;
		}	
	}
	mm = (q - b.integer);
	for(i = 0; i < mm + 1; i++) {
		if(*p < *q) {
			z = 10 + *p - *q - borrow ;	
			z = '0' + z;
			temp[j++] = z;
			borrow = 1;
		}
		else if  (*p > *q) {
			z = *p - *q - borrow;	
			z = '0' + z;
			temp[j++] = z;
			borrow = 0;
		}
		else if(*p == '.') {
			temp[j++] = '.';
		}	
		else {
			if(borrow) {
				temp[j++] = '9';	
				borrow = 1;
			}
			else {
				temp[j++] = '0';
				borrow = 0;
			}
		}
		if(q != b.integer) {
			p--;
			q--;
		}
	}	
	mm = p - a.integer;
	p--;
	if(borrow) 
		(*p)--;
	for(i = 0; i < mm; i++) {
		temp[j++] = *p;
		p--;
	}
	temp[j] = '\0';
//	printf(" temp %s \n", temp);
	int stemp = strlen(temp);
	char *str;
	str =(char *)malloc(strlen(temp) +1);
	for (i = 0 ; i < stemp; i++) {
		str[i] = temp[stemp - 1 - i];
	}
	str[i] = '\0';
//	printf("%s", str);
	c = CreateNumberFromString(str);
	return c;
}
Number CreateNumberFromString(char *str) {
	Number a;
	initNumber(&a);
	int i;
	char *temp;
	temp = str;
	if(*str == '+') {
		a.sign = '+';
		temp++;
	}
	else if (*str == '-') {
		a.sign = '-';
		temp++;
	}
	else {
		a.sign = '+';
	}
	a.integer = temp;
	int n = strlen(temp);
	for(i = 0; i < n; i++) 
		if(temp[i] == '.') 
			a.fraction = &temp[i];
	if(a.fraction == NULL) {
		i = strlen(a.integer);
		a.fraction = a.integer + i;
	}
	return a;
}
Number MulNumber(Number a , Number b) {
	numstack *nc;
	nc = (numstack *)malloc(sizeof(numstack));
	numinit(nc);
	int x, y, carry = 0, n, i , k, j, pp = 0, zero= 0;
	Number temp, c, an, bn;
	char *p, *q , *mul;
	
	x = strlen(a.integer);
	y = strlen(b.integer);
	if(x < y) {
		temp = a;
		a = b;
		b = temp;
	}
	q = b.integer;
	y = strlen(q);
	q = q + y;
	q--;
	char mn[x + 1];
//	printf("q is %c", *q); 
	for(i = 0; i < y; i++) {
		pp = 0;
		if(*q == '.') {
			i++;
			q--;
		}	
		mul = (char *)malloc(1);
		*mul ='\0';

		for(j = 0; j < zero; j++) {
			mul[pp++] = '0';
		}
		zero++;
		mul[pp] ='\0';
		strcpy(mn, a.integer);
		c = CreateNumberFromString(mn);
		p = c.integer;
	//	printf("\nc is %s", c.integer);
		x = strlen(p);
	//	printf("\n x  is %d", x); 
		p = p + x;
		k = 1;
		while(p != c.fraction) {
			*p = '\0';
			if((p - c.fraction) > 4) { 
				p = p - 4;
				n = atoi(p);
				n = n * (*q - '0');
			//	printf("%d", n);
				mul = appendleft(((n % 10000) + carry), mul);
				carry = n / 10000;
			}	
			else {
				p = c.fraction;
				p++;
				n = atoi(p);
			//	printf(" n is %d", n);
				
				n = n * (*q - '0');
			//	printf(" n is %d", n);

				while(n / k != 0 ) {
					k = k * 10;
				}	
				//k = k / 10;			
				mul = appendleft(((n % k) + carry), mul);
				n = (n % k) + carry;
			//	printf("\n (n %% k) + carry = %d", n); 
				carry = n / k;
				p--;
			}
		}
		
		*p = '\0';
		while(p != c.integer) {
			if((p - c.integer) > 4) { 
				p = p - 4;
				n = atoi(p);
				n = n * (*q - '0');
				mul = appendleft(((n % 10000) + carry), mul);
				carry = n / 10000;
			}	
			else {
				p = c.integer;
				n = atoi(p);
				n = n * (*q - '0');
				while(n / k != 0 ) {
					k = k * 10;
				}				
				mul = appendleft(((n % k) + carry), mul);
				carry = n / k;
			}
		}
		printf("\nmul = %s", mul);
		q--;

		initNumber(&temp);
		temp = CreateNumberFromString(mul);
/*		temp.integer = mul;
		x = strlen(mul);
		temp.fraction = mul + x;	
*/		printf("temp is "); PrintNumber(temp);

		numpush(nc, temp);
	}
	printnumstack(nc);
	an = numpop(nc);
//	printf("\nan is "); PrintNumber(an);
	y = strlen(b.integer);
	y = y - 2;
	printf("y is %d", y);
	for(i = 0; i < y; i++) {
		bn = numpop(nc);
	//		printf("\n bn is"); PrintNumber(an);
		an = AddNumber(an, bn);
	//		printf("\n an is"); PrintNumber(an);
	}
	initNumber(c);
	x = strlen(a.integer) - (a.fraction - a.integer) ;
	y = strlen(b.integer) - (b.fraction - b.integer);
	x--;
	y--;
	
	return c;

}


			
			
			
