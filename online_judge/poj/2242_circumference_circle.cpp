// http://poj.org/problem?id=2242
#include <cstdio>
#include <limits>
#include <cmath>

#define PI 3.141592653589793

template<typename T>
class Equation
{
public:
	Equation(T x1, T y1, T x2, T y2, T x3, T y3);
	~Equation();
public:
	T compute_circumference();
private:
	void compute_center_coordinate();
private:
	T x1_, y1_, x2_, y2_, x3_, y3_;
	T x0_, y0_;
};

template<typename T>
Equation<T>::Equation(T x1, T y1, T x2, T y2, T x3, T y3)
: x1_(x1)
, y1_(y1)
, x2_(x2)
, y2_(y2)
, x3_(x3)
, y3_(y3)
{
}

template<typename T>
Equation<T>::~Equation()
{
}

template<typename T>
void Equation<T>::compute_center_coordinate()
{
	// equations:
	// a*x + b*y = c
	// d*x + e*y = f
	
	// solution:
	// x = (c*e - b*f)/(a*e - b*d)
	// y = (a*f - c*d)/(a*e - b*d)

	T a = 2*(x2_ - x1_);
	T b = 2*(y2_ - y1_);
	T c = (y2_ - y1_)*(y1_ + y2_) + (x2_ - x1_)*(x1_ + x2_);
	T d = 2*(x3_ - x1_);
	T e = 2*(y3_ - y1_);
	T f = (y3_ - y1_)*(y1_ + y3_) + (x3_ - x1_)*(x1_ + x3_);

	x0_ = (c*e - b*f)/(a*e - b*d);
	y0_ = (a*f - c*d)/(a*e - b*d);
}

template<typename T>
T Equation<T>::compute_circumference()
{
	(*this).compute_center_coordinate();

	T radius = sqrt((x0_ - x1_)*(x0_ - x1_) + (y0_ - y1_)*(y0_ - y1_));
	return 2*PI*radius;
}

int main(int argc, char* argv[])
{
	/*
	float float_max = std::numeric_limits<float>::max();
	printf("(float)max: %f\n",float_max);

	int float_digits10 = std::numeric_limits<float>::digits10;
	printf("(float)digits10: %d\n",float_digits10);
	
	int float_digits = std::numeric_limits<float>::digits;
	printf("(float)digits: %d\n", float_digits);
	*/

	// http://stackoverflow.com/questions/210590/why-does-scanf-need-lf-for-doubles-when-printf-is-okay-with-just-f
	double x1,y1,x2,y2,x3,y3;
	char ch = '\n';
	bool flag = true;

	// http://stackoverflow.com/questions/3197025/end-of-fileeof-of-standard-input-stream-stdin
	// Ctrl+Z as EOF

	while (flag)
	{
		if (scanf("%lf",&x1) == EOF)
		{
			break;
		}
		scanf("%lf",&y1);
		scanf("%lf",&x2);
		scanf("%lf",&y2);
		scanf("%lf",&x3);
		scanf("%lf",&y3);
		
		if (scanf("%c",&ch) == EOF)
		{
			flag = false;
		}

		Equation<double> eqn(x1,y1,x2,y2,x3,y3);
		printf("%.2f\n",eqn.compute_circumference());
	}

	return 0;
}

/*
http://www.informatik.uni-ulm.de/acm/Locals/1996/
*/