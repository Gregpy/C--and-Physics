#include <sstream>
#include <math.h>
#include <iostream>
#include <string>

int
main(int argc, char *argv[])
{

	double *p, *l, *d, *u, *r, x, dx, xL, xR, lamk, lamp;

	int n, i;
	std::string in_val;
	int td_solve(double *l, double *d, double *u, double *r, double *y, int n);

	FILE *fp;

	std::cout << "Using FEBS to compute a two-point boundary value problem, part 2.\n";


	std::cout << "Enter lambda-k: ";
    std::getline(std::cin, in_val);

    lamk = std::stod(in_val);

	std::cout << "Enter lambda-p: ";
    std::getline(std::cin, in_val);

    lamp = std::stod(in_val);

	std::cout << "Enter N: ";
    std::getline(std::cin, in_val);

    n = std::stoi(in_val);

	p = (double*)malloc(n*sizeof(double));

	l = (double*)malloc(n*sizeof(double));

	d = (double*)malloc(n*sizeof(double));

	u = (double*)malloc(n*sizeof(double));

	r = (double*)malloc(n*sizeof(double));

	xL = -0.5;

	xR = 0.5;

	dx = (xR-xL)/(n-1);

	for (i = 0; i < n; i++) {

	  x = -0.5 + i*dx;

	  u[i] = 4*(pow(x/dx, 2) + x/dx);

	  l[i] = 4*(pow(x/dx, 2) - x/dx);

	  d[i] = -8*pow(x/dx, 2) - 1.0/(lamk*lamk);

	  r[i] = 0.0;
}

	u[0] += l[0];

	d[0] -= 2*dx*l[0]/lamp;

	r[0] -= 2*dx*l[0]/lamp;

	l[n-1] += u[n-1];

	d[n-1] -= 2*dx*u[n-1]/lamp;

	r[n-1] -= 2*dx*u[n-1]/lamp;

	if (td_solve(&l[0], &d[0], &u[0], &r[0], &p[0], n) != 0) {

		fprintf(stderr, "td_solve() failed!\n");

		exit(2);
}
	fp = fopen("gbp3b.txt", "w");
	std::cout << "Results sent to gbp3b.txt\n";
	for (i = 0; i < n; i++) {

		x = xL + i*dx;

		fprintf(fp, "%le %le\n", x, p[i]);
}
	fclose(fp);

	exit(0);
}

	int
	td_solve(double *l, double *d, double *u, double *r, double *y, int n)
{

	int i;
/*
* do Gaussian elimination:
*/

	for (i = 1; i < n; i++) {

		if (d[i-1] == 0.0) return 1;

		d[i] -= l[i]*u[i-1]/d[i-1];

		r[i] -= l[i]*r[i-1]/d[i-1];
}
/*
* do back-substitution:
*/
	if (d[n-1] == 0.0) return 2;

	y[n-1] = r[n-1]/d[n-1];

	for (i = n-2; i >= 0; i--) {

		if(d[i] == 0.0) return 2;

		y[i] = (r[i] - u[i]*y[i+1])/d[i];
}
	return 0;
}

