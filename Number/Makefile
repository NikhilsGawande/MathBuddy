mathbuddy: main.o num.o numstack.o  
	cc main.o num.o numstack.o -o mathbuddy 
main.o: main.c num.h
	cc -c main.c
num.o: num.c num.h numstack.h
	cc -c num.c
numstack.o : numstack.c numstack.h	
	cc -c numstack.c

