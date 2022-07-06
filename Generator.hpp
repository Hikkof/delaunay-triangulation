#include "Structures.hpp"


using namespace std;


void generator(vector<Point>& points, int n, double r)
{
	double x, y, random;
	double square;
	
	srand(time(0));

	while (n > 0)
	{
		random = rand();
		random /= 10000;
		x = fmod(random, r*2)-r;
		
		random = rand();
		random /= 10000;
		y = fmod(random, sqrt(r*r - x*x));
		if (rand()%2 == 1)
		{
			y *= (-1);
		}
		n--;
		
		points.push_back(*(new Point(x, y)));
	}
}
