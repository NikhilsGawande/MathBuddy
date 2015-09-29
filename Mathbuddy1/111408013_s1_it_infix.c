#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
int infix(char *);
#define OPERAND 	1
#define OPERATOR 	2
#define INVALID		3

typedef struct token {
	int type;
	union data {
		int num;
		char operator;
	}d;
}token;


enum states {SPC, NUM, OPR, END, ERROR};

token *getnext(char *string) {
	static int currstate = SPC, nextstate;
	static int i = 0;
	int sum, done = 0;
	token *p = (token *)malloc(sizeof(token));
	if(p == NULL)
		return NULL;
	while(1) {
		switch(string[i]) {
			case '1': case'2': case '3': case '4':
			case '5': case'6': case '7': case '8':
			case '9': case'0': 
				nextstate = NUM;
				break;
			case '+': case '-': case '*': case '/':
			case '%': case '(': case ')' :
				nextstate = OPR;
				break;
			case '\0':
				nextstate = END;
				break;
			case ' ':
				nextstate = SPC;
				break;
			default:
				nextstate = ERROR;
				break;
		}
		switch(currstate) {
			case SPC:
				switch(nextstate){
					case SPC:
						/* Do nothing */
						break;
					case NUM:
						sum = string[i] - '0';	
						break;
					case OPR:
						/* Do nothing */
						break;
					case END:
						break;
					case ERROR:
						break;
					default:
						break;
				}
				break;
			case NUM:
				switch(nextstate){
					case SPC:
						/* Num completed */
						p->type = OPERAND;
						p->d.num = sum;
						done = 1;
						break;
					case NUM:
						sum = sum * 10 + string[i] - '0';
						break;
					case OPR:
						p->type = OPERAND;
						p->d.num = sum;
						done = 1;
						break;
					case END:
						p->type = OPERAND;
						p->d.num = sum;
						done = 1;
						break;
					case ERROR:
						p->type = OPERAND;
						p->d.num = sum;
						done = 1;
						break;
					default:
						break;
				}
				break;
			case OPR:
				switch(nextstate){
					case SPC:
						p->type = OPERATOR;
						p->d.operator = string[i - 1];
						done = 1;
						break;
					case NUM:
						p->type = OPERATOR;
						p->d.operator = string[i - 1];
						sum = string[i] - '0';
						done = 1;
						break;
					case OPR:
						p->type = OPERATOR;
						p->d.operator = string[i - 1];
						done = 1;
						break;
					case END:
						p->type = OPERATOR;
						p->d.operator = string[i - 1];
						done = 1;
						break;
					case ERROR:
						p->type = OPERATOR;
						p->d.operator = string[i];
						done = 1;
						break;
					default:
						break;
				}
				break;
			case END:
				nextstate = END;
				done = 1;
				p = NULL;
				break;
			case ERROR:
				nextstate = ERROR;
				p->type = INVALID;
				done = 1;
				break;
			default:
				break;
		}
		currstate = nextstate;
		i++;
		if(done == 1)
			return p;
	}
	return NULL;	
}

int main() {
	int value;						
	char str[128];
	scanf("%[^\n]", str);
	printf("String: %s\n", str);
	value = infix(str);
	if(value == INT_MIN)
		printf("Error \n Please enter valid expression.\n");
	else 
		printf("Result is : %d \n ", value );
	
	return 0;
}


int infix(char *a) {
	char *bptr[128];
	int *nptr[128];
	char op[128];
	int num[128];
	int bcntr = 0, ncntr = 0;
	token *token;
	char premember ;
	char *p = op;
	int *q = num;
	int flagcntr = 0, bflagcntr = 0;
	char flag[128];
	int bflag[128];
	int f = 1;
	while((token = getnext(a))) {
		if(token ->type == OPERATOR) { 
			switch(token->d.operator) {			
				case '+' :
					switch(premember) {
						case '-': case '*' : case'/' : case '+' : case '%' :
							return INT_MIN;
							break;
						case 'N' : case ')' :
							*p = '+';
							p++;
							premember = '+';
							break;
						case '(' :
							break; 
					}
					break;
				case '%' :
					switch(premember) {
						case '-': case '*' : case'/' : case '+' : 
						case '(' :case '%':
							return INT_MIN;
							break;
						case 'N' : case ')' :
							premember = '%';
							break;
					}
					break;
				case '-' :
					switch(premember) {
						case '-' : case '*': case'/' : case '+' :
						case '%' :
							return INT_MIN;
							break;
						case 'N' : case ')':
							*p = '-';
							p++;
							premember = '-';
							break ;
						case '(' :
							*q = -1;
							q++;
							premember = '*';
							break;
					}
					break;
				case '*' :
					switch(premember) {
						case '(' : case '-' : case '*': case'/' :
						case '+' : case '%' : 					
							return INT_MIN;
							break;
						case ')' : case 'N' : 
							/*do nothing */
							break;
					}
					premember = '*';
					break;
				case '/':
					switch(premember) {
						case'(' : case '-' : case '*': case'/' : 							case '%' : case '+' :
							return INT_MIN;
							break;
						case ')' : case 'N' : 
							/*do nothing */
							break;
					}
					premember = '/';
					break;
				case '(' :
					bptr[bcntr] = p;
					*p = '(' ;
					nptr[ncntr] = q;
					p++;
					bcntr++;
					ncntr++;
					
					switch(premember) {
						case '(' : case '-' :
						case '+' :				
							/*do nothing*/
							break;
						case '*' : 
							flag[flagcntr++] = '*';
							bflag[bflagcntr++] = (bcntr - 1);
							break;
						case '%' : 
							flag[flagcntr++] = '%';
							bflag[bflagcntr++] = (bcntr - 1);
							break;

						case '/' :
							flag[flagcntr++] = '/';
							bflag[bflagcntr++] = (bcntr - 1);
							break;
						case 'N' : case ')' :
							return INT_MIN;
							break;
					}
					premember = '(' ;
					break;
				case ')' :
					switch(premember) {
						case'(' : case '-' : case '*': case'/' :
						case '+': case '%' :			
							return INT_MIN;
							break;
						case 'N' : case ')' :				
							*p = ')' ;
							p++;
							char *startop = bptr[(bcntr - 1)];
							int *startnum =nptr[(ncntr - 1)];
							int len = ((p - startop) - 2);
							if(len == 0) {
								bcntr--;
								p = bptr[bcntr];
								ncntr--;
							
							} else {
								char *m = startop;
								int *n = startnum;
								m++;
								while(*m != ')') {
									switch(*m) {
										case '+':
											n[1] = (n[0] + n[1]);
											n++;
											break;
										case '-':
											n[1] = (n[0] - n[1]);
											n++;
											break;
									}
									m++;
								}
								p = startop;
								*startnum = *n;
								bcntr--;
								ncntr--;
								q = startnum;
								q++;
							}
							if(bcntr == bflag[(bflagcntr-1)]) {
								switch(flag[(flagcntr - 1)]) {
										case '*' :
											q[-2] = (q[-2] * q[-1]);
											q--;
										
											break;
										case '%' :
											q[-2] = (q[-2] % q[-1]);
											q--;
										
											break;

										case '/' :
											if(q[-1] == 0)
												return INT_MIN;
											q[-2] = (q[-2] / q[-1]);
											q--;
										
											break;
								}
								flagcntr--;
								bflagcntr--;

							}
							break;

					}
					premember = ')';
					break;
				}
			}
		else if (token->type == OPERAND) {
			*q = token->d.num;
			q++;
			switch(premember) {
				case '(' : case '+' : case '-' :
					/*do nothing*/ 
					break;
				case 'N' :
					return INT_MIN;
					break;
				case '*' :
					q[-2] = (q[-2] * q[-1]);
					q--;
				
					break;
				case '%' :
					q[-2] = (q[-2] % q[-1]);
					q--;
					break;
				case '/' :
					if(token->d.num == 0) 
						return INT_MIN;
					q[-2] = (q[-2] / q[-1]);
					q--;
					break;
				case ')' :
					return INT_MIN;
					break;
			
			}
			premember = 'N';
			
		}
		else if (token -> type == INVALID) {
			return INT_MIN;
		}
	}
	if (bcntr != 0) {
		return INT_MIN;
	}
	q--;
	char *s = op;
	int *t = num;
	while(t != q) {
		switch(*s) {
			case '+' :
				t[1] = (t[0] + t[1]);
				s++;					
				break;
			case '-':
				t[1] = (t[0] - t[1]);
				s++;
				break;
			case '%' :
				t[1] = (t[0] % t[1]);
				s++;					
				break;
		}
		t++;
	}
	return(*t);
}
		
	
		















