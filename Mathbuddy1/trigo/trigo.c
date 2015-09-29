double sine(double x) {
	int n, x1;
	int i = 0;
	double acc, term, den, sinx=0, sinval;
	x1 = x;
	/* Converting degrees to radians*/
	x = x*(3.142/180.0);
	//sinval = sin(x);
	/*printf("Enter the accuary for the result\n");
	scanf("%f", &acc);*/
	term = x;
	sinx = term;
	n = 1;
	do {
		den = 2*n*(2*n+1);
		term = -term * x * x / den;
		sinx = sinx + term;
		n = n + 1;
		i++;
	}while(i <= 10);
	printf("Sum of the sine series         = %lf\n", sinx);
}
double cos(double x) {
	int n,x1,i,j;
   	double sign,cosx,fact;
	x1=x;
	x=x*(3.142/180.0); /* Degrees to radians*/
	cosx=1;
	sign=-1;
	int i = 2;
	do
   	{
		 fact=1;
		 for(j=1;j<=i;j++)
		 {
			fact=fact*j;	int n, x1;
	int i = 0;
	double acc, term, den, sinx=0, sinval;
	double x;
        	 }
		 cosx=cosx+(pow(x,i)/fact)*sign;
      		 sign=sign*(-1);
      		 i = i +2;
	 }while(i<=n);
	 printf("Sum of the cosine series                    = %7.2f\n",cosx);
}
double tan(double x) {
	return (sin(x) / cos(x));
}

double cot(double x) {
	return(1 / tan(x));
}

double sec(double x) {
	return (1/cos(x));
}
 
double cosec(double) {
	return (1/sine(x));
}
double asine(double);
double acos(double);
double atan(double);
double acosine(double);
double asec(double);
double acosec(double);
double acot(double);

