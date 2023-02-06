/*The values the variables correspond to are: 'n' is the number of discretization points; 'i' is the counter used in the for loop; 'a' is the lower limit of the integral; 'b' is the upper limit of the integral; 'd' is dx or delta x, the width of the trapezoids; 's' is the sum of the area of the trapezoids. The sum of the first and last functions are calculated separately from the rest since they are divided by 2.*/

#include <sstream>
#include <math.h>
#include <iostream>
#include <string>
#include <iomanip>

double fun(double x);

int main() {

  	int n,i;
	double a,b,d,s=0;
	std::string in_val;

	std::cout << "Using the Trapezoidal Rule to determine the definite integral of cos(x^2). The discreization points are determined by the lower limit 'a' and the upper limit 'b' with the formula n=|(b-a)/(2*pi*10^-4/b)+1| (with b switched with a if the absolute value of b is less than the absolute value of a).\n";

	std::cout << "Enter the lower limit 'a':\n";
    std::getline(std::cin, in_val);

    a = std::stod(in_val);

	std::cout << "Enter the upper limit 'b':\n";
    std::getline(std::cin, in_val);

    b = std::stod(in_val);

	if(abs(b)<abs(a)){

	n=abs(a*(a-b)/(2*3.14159*0.0001)+1);

	}

	else if(abs(b)>=abs(a)){

	n=abs(b*(b-a)/(2*3.14159*0.0001)+1);

	}

	d=(b-a)/(n-1);

	s=d/2*(fun(a) + fun(b));

	for(i=1;i<=n-2;i++){

	s=s+d*fun(a+i*d);

	}

	std::cout << "The signed area under the curve is equal to: " << std::setprecision(6) << s << std::endl;

return (0);

}

double fun(double x)

{

double form;

	form = cos(x*x);

return (form);

}




