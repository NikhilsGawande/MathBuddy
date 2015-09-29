#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<errno.h>
#include "integer.h"
void iinit(integer *l) {
	l->head = l->tail = NULL;
	l->length = 0;
}
void iappend(integer *l, int a) {
	node *temp, *p;
	temp = (node *)malloc(sizeof(node));	
	temp->digit = a;
	if(l->head == NULL) { 
		l->head = temp->next = temp->prev = l->tail = temp;
		l->length = 1;
		return;
	}
	p = l->tail;
	temp->next = p->next;
	temp->prev = p;
	p->next->prev = temp;
	p->next = temp;
	l->tail = temp;
	(l->length)++;
	return;
}
/* Create and return an Integer from a string. The string can be assumed to be a string of digits */
integer CreateIntegerFromString(char *string) {
	integer i;
	char *temp;
	int j, len;
	iinit(&i);
	if(*string == '+') { 
		i.sign = '+';
		string++;
	}
	else if (*string == '-') {
		i.sign = '-';
		string++;
	}
	else { 
		i.sign = '+';
	}
	temp = string;
	while(*temp != '\0') {
		iappend(&i, (*temp - '0'));
		temp++;
	}
	return i;
}
/* Print an IntegSer */
void PrintInteger(integer *l) {
	node *p = l->head;
	printf("No is :%c", l->sign);
	while(p != l->tail) {
		printf("%d", p->digit);
		p = p->next;
	}
	printf("%d\n", p->digit);
	return;
}
integer AddDigitToInteger(integer a, char digit) {
	iappend(&a, (digit - '0'));
	return a ;
}
integer AddIntegers(integer a, integer b) {
 	integer c;
	iinit(&c);
	int sign;	
	if((a.sign == '+') && (b.sign == '+') )
		c.sign = '+';
	else if((a.sign == '-') && (b.sign == '-')) 
		c.sign = '-';
	else {
		integer result ;
		iinit(&result);
		if (a.sign == '-') { 
			a.sign = '+';
			sign = '-';
		}
		else {
			b.sign = '+';
			sign = '+';
		} 
		result = SubstractIntegers(a, b);	
		result.sign = sign;
		return result;
	}
	node *p , *q;
	p = a.tail;
	q = b.tail;
	int carry = 0, result ;
	while((p != a.head) && (q != b.head)) {
		result = p->digit + q->digit + carry  ;
		carry = (result / 10000);
		iappend(&c, (result % 10000));
		p = p->prev;
		q = q->prev;
	}		 
	iappend(&c, (p->digit + q->digit + carry ));
	while (p != a.head) {
		p = p->prev;
		iappend(&c, p->digit + carry);
		carry = 0;
	}
	while (q != b.head) {
		q = q->prev;
		iappend(&c, q->digit + carry);
		carry = 0;
	}
	ireverse(&c);
	return c;
}	
void ireverse(integer *l) {
	node *p, *q, *r;
	if(l->head == l->tail)
		return;
	if(l->length == 2) {
		p = l->tail;
		l->tail = l->head;
		l->head = p;
		return;
	}		
	q = l->head;
	p = q->next;
	r = p->next;
	while(q != r) {
		p->next = q;
		q = p;	
		p = r;
		r = r->next;
	}
	l->head  = q->next;

	q = l->tail;
	p = q->prev;
	r = p->prev;
	while(q != r) {
		p->prev = q;
		q = p;	
		p = r;
		r = r->prev;
	}
	l->tail = q->prev;
}
integer SubstractIntegers(integer a, integer b) {
	printf("a.sign = %c , b.sign = %c", a.sign , b.sign);
	if(a.sign != b.sign ) {
		integer result ;
		char sign;
		if (a.sign == '-') { 
			a.sign = '+';
			sign = '-';
		}
		else {
			b.sign = '+';
			sign = '+';
		} 
		result = AddIntegers(a, b);
		result.sign = sign;		
		return result ;
	}
	node *p, *q;
	p = a.tail;
	q = b.tail;
	integer no1, no2, r;
	iinit(&no1);
	iinit(&no2);
	iinit(&r);
	if (a.length > b.length) { 
		no1 = a;
		no2 = b;
	}
	else if (a.length < b.length) {
		no1 = b;
		no2 = a;
	}
	else {
		while (p != a.tail) {
			if (p->digit > q->digit ) { 
				no1 = a;
				no2 = b;
			}
			else if (p->digit < q->digit) {
				no1 = b;
				no2 = a;
			}
			else {
				p = p->next;
				q = q->next;
			}
		}
	}
	if (no1.head == NULL && no2.head == NULL) {
		if (p->digit > q->digit ) { 
			no1 = a;
			no2 = b;
		}
		else if (p->digit < q->digit) {
			no1 = b;
			no2 = a;
		}
		else
			return no1;
	}
	int borrow = 0;
	node *m, *n;
	m = no1.tail;
	n = no2.tail;
	while(n != no2.head) {
		if(m->digit < n->digit) {
			iappend(&r, (10 + m->digit - n->digit - borrow));
			borrow = 1;
		}
		else if (m->digit > n->digit) {
			iappend(&r, (m->digit - n->digit - borrow));
			borrow = 0;
		}
		else {
			if(borrow == 1) {
				iappend(&r, (10 + m->digit - n->digit - borrow));
				borrow = 1;
			}
			else {
				iappend(&r, 0);
				borrow = 0;
			}
		}
		m = m->prev;
		n = n->prev;
	}
	if(m->digit < n->digit) {
		iappend(&r, (10 + m->digit - n->digit - borrow));
		borrow = 1;
	}
	else if (m->digit > n->digit) {
		iappend(&r, (m->digit - n->digit - borrow));
		borrow = 0;
	}
	else {
		if(borrow == 1) {
			iappend(&r, (10 + m->digit - n->digit - borrow));
			borrow = 1;
		}
		else {
			iappend(&r, 0);
			borrow = 0;
		}
	}
	m = m->prev;
	while(m != no1.tail) {
		iappend(&r, (m->digit - borrow));
		borrow = 0;
		m = m->prev;
	}
	ireverse(&r);
	r.sign = no1.sign;
	return r;
}

integer MultiplyIntegers(integer a, integer b) {
	node *p, *q;
	p = a.tail;
	q = b.tail;
	integer no1, no2, r;
	iinit(&no1);
	iinit(&no2);
	iinit(&r);
	if (a.length > b.length) { 
		no1 = a;
		no2 = b;
	}
	else if (a.length < b.length) {
		no1 = b;
		no2 = a;
	}
	else {
		while (p != a.tail) {
			if (p->digit > q->digit ) { 
				no1 = a;
				no2 = b;
			}
			else if (p->digit < q->digit) {
				no1 = b;
				no2 = a;
			}
			else {
				p = p->next;
				q = q->next;
			}
		}
	}
	if (no1.head == NULL && no2.head == NULL) {
		if (p->digit > q->digit ) { 
			no1 = a;
			no2 = b;
		}
		else if (p->digit < q->digit) {
			no1 = b;
			no2 = a;
		}
		else {
 			 no1 = a;
			no2 = b;
		}
	}
	node *m, *n;
	n = no2.tail;
	int size = no2.length, carry = 0, i, j;
	integer temp[size];
	for(i = 0; i < size ; i++) {
		m = no1.tail;
		iinit(&temp[i]);
		temp[i].sign = '+';
		printf("n->digit is %d\n", n->digit);
		for(j = 0; j < i; j++) {
			iappend(&temp[i], 0);
		} 
		while (m != no1.head) {
			int r;
			r = m->digit * n->digit + carry;
			carry = (r/10);
			iappend(&temp[i], r%10);
			m = m->prev;	
		}
		iappend( &temp[i], m->digit * n->digit +carry);
		iappend(&temp[i] , carry);
		ireverse(&temp[i]);
		n = n->prev;
	}
	for(i = 0; i < (size - 1) ; i++) {
		temp[i + 1] = AddIntegers(temp[i], temp[i + 1]);	
	}
	if(no1.sign == '-' && no2.sign == '-' )
		temp[(size - 1)].sign = '+';
	else if (no1.sign == '+' && no2.sign == '+' )
		temp[(size - 1)].sign = '+';
	else 
		temp[(size - 1)].sign = '-';	
	return temp[(size - 1)];
}	
integer CreateIntegerFromFile(char *fname) {
	FILE *fp;
	char c;
	integer r;
	iinit(&r);
	fp = fopen(fname , "r");
	printf("1");
	if(fp == NULL) {
		perror("open failed");
		return ;
	}
	fread(&c, sizeof(char), 1, fp);
	if( c == '+')
		r.sign = '+';
	else if( c == '-') 
		r.sign = '-';
	else {
		r.sign = '+';
		iappend(&r, (c - '0'));
	}
	fread(&c, sizeof(char), 1, fp);
	while(isalnum(c)) {
		iappend(&r, (c - '0'));
		fread(&c, sizeof(char), 1, fp);
	}
	return r;
}
	 

		
















