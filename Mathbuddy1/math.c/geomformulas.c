#include "mymath.h"
#define PI = 3.1415
int striangle(int a, int b, int c) { 
	int s;
	s = (a + b + c) / 2;
	return s;
}
int atriangle(int a, int b, int c) {
	int s;
	s = striangle(a,b,c);
	area = sqrt ( s * (s-a) * (s-b) * (s-c));
	return area;
}
double scube(double side) {
	double surfArea = 6.0 * side * side;
	return surfArea;
}
double vcube(double side) {
	double volume = pow (side, 3);
	return volume ;
}
double scircle(double r) {
	double area = PI * pow (radius,2);
	return area;
}
double pcircle(double r) {
	double p = 2 * PI * r;
	return p;
}
