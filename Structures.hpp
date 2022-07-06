#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string>
#include <cmath>
#include <vector>


using namespace std;


struct Point
{
	double x, y;
	
	
	Point(double x = 0, double y = 0)
	{
		this->x = x;
		this->y = y;
	}
	
	
	double distance(Point point)
	{
		double dx = this->x-point.x;
		double dy = this->y-point.y;
		return sqrt(dx*dx + dy*dy);
	}
	
	
	bool operator==(Point point)
	{
		if(this->x == point.x && this->y == point.y)
		{
			return true;
		}
		return false;
	}
};


struct Edge
{
	Point a = *(new Point);
	Point b = *(new Point);
	
	
	Edge(Point a = *(new Point), Point b = *(new Point))
	{
		this->a = a;
		this->b = b;
	}
	
	
	bool operator==(Edge edge)
	{
		if((this->a == edge.a && this->b == edge.b) ||
		(this->a == edge.b && this->b == edge.a))
		{
			return true;
		}
		return false;
	}
};


struct Triangle
{
	Point a = *(new Point);
	Point b = *(new Point);
	Point c = *(new Point);
	
	
	Triangle(Point a = *(new Point), Point b = *(new Point), Point c = *(new Point))
	{
		this->a = a;
		this->b = b;
		this->c = c;
	}
	
	
	bool compare_eges(Edge edge)
	{
		Edge edge_a = *(new Edge(this->a, this->b));
		Edge edge_b = *(new Edge(this->b, this->c));
		Edge edge_c = *(new Edge(this->c, this->a));
		
		if(edge == edge_a || edge == edge_b || edge == edge_c)
		{
			return true;
		}
		return false;
	}
	
	
	bool operator==(Triangle triangle)
	{
		if(this->a == triangle.a && this->b == triangle.b &&
		this->c == triangle.c)
		{
			return true;
		}
		return false;
	}
	
	
	Point circle_center()
	{
		double d = 2*(this->a.x*(this->b.y-this->c.y)+
		this->b.x*(this->c.y-this->a.y)+
		this->c.x*(this->a.y-this->b.y));

		double x =((this->a.x*this->a.x+this->a.y*this->a.y)*(this->b.y-this->c.y)+
		(this->b.x*this->b.x+this->b.y*this->b.y)*(this->c.y-this->a.y)+
		(this->c.x*this->c.x+this->c.y*this->c.y)*(this->a.y-this->b.y))/d;
		
		double y =((this->a.x*this->a.x+this->a.y*this->a.y)*(this->c.x-this->b.x)+
		(this->b.x*this->b.x+this->b.y*this->b.y)*(this->a.x-this->c.x)+
		(this->c.x*this->c.x+this->c.y*this->c.y)*(this->b.x-this->a.x))/d;
		
		Point p = *(new Point(x, y));
		return p;
	}
};

