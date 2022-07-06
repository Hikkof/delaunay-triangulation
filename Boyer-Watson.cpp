#include <cairo.h>
#include "Generator.hpp"


using namespace std;


void bowyerWatson(vector<Point> &points, double r)
{
	vector<Triangle> triangles;
	vector<Triangle> bad_triangles;
	vector<Edge> polygon;

	Edge edges[3];
	int value[3];
	Point center;

	Triangle super(*(new Point(0.0, 2*r)),
	*(new Point(-1*(r*1.75), -1*r)),
	*(new Point(r*1.75, -1*r)));

	triangles.push_back(*(new Triangle(super.a, super.b, points[0])));
	triangles.push_back(*(new Triangle(super.b, super.c, points[0])));
	triangles.push_back(*(new Triangle(super.c, super.a, points[0])));

	for (int i = 1; i < points.size(); i++)
	{
		bad_triangles.clear();
		
		for(int j = 0; j < triangles.size(); j++)
		{
			Point center = triangles[j].circle_center();
			
			if(center.distance(points[i]) <=
			center.distance(triangles[j].a))
			{
				bad_triangles.push_back(triangles[j]);
			}
		}
		
		polygon.clear();
		
		for(int j = 0; j < bad_triangles.size(); j++)
		{
			value[0] = 0, value[1] = 0, value[2] = 0;
			edges[0] = Edge(bad_triangles[j].a, bad_triangles[j].b);
			edges[1] = Edge(bad_triangles[j].b, bad_triangles[j].c);
			edges[2] = Edge(bad_triangles[j].c, bad_triangles[j].a);
			for(int k = 0; k < bad_triangles.size(); k++)
			{
				if(bad_triangles[k].compare_eges(edges[0]))
				{
					value[0]++;
				}
				if(bad_triangles[k].compare_eges(edges[1]))
				{
					value[1]++;
				}
				if(bad_triangles[k].compare_eges(edges[2]))
				{
					value[2]++;
				}
			}
			if(value[0] == 1)
			{
				polygon.push_back(edges[0]);
			}
			if(value[1] == 1)
			{
				polygon.push_back(edges[1]);
			}
			if(value[2] == 1)
			{
				polygon.push_back(edges[2]);
			}
		}
		for(int j = 0; j < bad_triangles.size(); j++)
		{
			for(int k = triangles.size()-1; k >= 0; k--)
			{
				if (triangles[k] == bad_triangles[j])
				{
					triangles.erase(triangles.begin()+k);
				}
			}
		}
		
		for(int j = 0; j < polygon.size(); j++)
		{
			triangles.push_back(*(new Triangle(polygon[j].a,
			polygon[j].b, points[i])));
		}
	}

	for(int i = triangles.size()-1; i >= 0; i--)
	{
		if (super.a == triangles[i].a ||super.b == triangles[i].a
		||super.c == triangles[i].a)
		{
			triangles.erase(triangles.begin()+i);
		}
		else if (super.a == triangles[i].b ||super.b == triangles[i].b
		||super.c == triangles[i].b)
		{
			triangles.erase(triangles.begin()+i);
		}
		else if (super.a == triangles[i].c ||super.b == triangles[i].c
		||super.c == triangles[i].c)
		{
			triangles.erase(triangles.begin()+i);
		}
	}

	cairo_surface_t *surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, 800, 800);
	cairo_t *cr = cairo_create(surface);
	cairo_set_line_width(cr, 2.0);
	double idk = 400/r;

	for (int i = 0; i < triangles.size(); i++)
	{
		cairo_move_to(cr, 400+triangles[i].a.x*idk,
		400+triangles[i].a.y*idk);
		cairo_line_to(cr, 400+triangles[i].b.x*idk,
		400+triangles[i].b.y*idk);
		cairo_line_to(cr, 400+triangles[i].c.x*idk,
		400+triangles[i].c.y*idk);
		cairo_line_to(cr, 400+triangles[i].a.x*idk,
		400+triangles[i].a.y*idk);
		cairo_stroke(cr);
	}

	cairo_surface_write_to_png(surface, "Delaunay Triangulation.png");
	cairo_surface_destroy(surface);
}


int main()
{
	double c, r = 5;
	vector<Point> points;
	generator(points, 100, r);
	
	bowyerWatson (points, r);
}

