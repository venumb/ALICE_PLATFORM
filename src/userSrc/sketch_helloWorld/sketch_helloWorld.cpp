#define _MAIN_



#ifdef _MAIN_

#include "main.h"
#include "MODEL.h"
#include <array>
#include <memory>
#include<time.h>
#include<experimental/generator> 

using namespace std;
using namespace std::experimental;
#include "sketch_spatialBinning\spatialBin.h"


///////// ----------------------------------------- model - view - controller (MVC) paradigm / pattern / template  ----------------- ////////////////////////////// 
/////////////////////////// model  ///////////////////////////////////////////
// idea : make 100 points, make them move towards nearest neighbor ;



class circle
{
public:
	vec cen;
	vec pts[100];
	bool detectedOrNot[100];

	///////// setup methods 
	void initialisePoints() // out points on a circle 
	{
		for (int i = 0; i < 100; i++)
		{
			pts[i] = vec(
				1.0 * sin(2 * PI * 1 / 100 * i), // x coordinate
				1.0 * cos(2 * PI * 1 / 100 * i), // y coordinate
				0 // z coordinate
			);

			pts[i] = pts[i] + cen; // move points relative to the location of the center
		}
	}

	///////// update methods 

	void reset()
	{
		for (int i = 0; i < 100; i++)detectedOrNot[i] = false;
	}
	void detect(circle &other)
	{
		for (int i = 0; i < 100; i++)
		{

			for (int j = 0; j < 100; j++)
			{
				if (pts[i].distanceTo(other.pts[j]) < .5)
				{
					detectedOrNot[i] = true;
					break;
				}
			}
		}
	}
	void expand()
	{
		for (int i = 0; i < 100; i++)
		{
			if (!detectedOrNot[i])
				pts[i] += (pts[i] - cen).normalise() * 0.1;
		}
	}

	///////// display methods 
	void display() // display the center and display the points 
	{
		drawPoint(cen);
		for (int i = 0; i < 100; i++)
		{
			drawPoint(pts[i]);
		}
	}

	///////// export methods
};



///////////////////////////////////////////////////////////// MAIN PROGRAM /////////////////////////////////////////////////////////////



vector<vec> layer_pts;
list<vec> stack_pts;

int numPtsPerLayer = 32;
float radius = 10;

vec up(0, 0, 1);

//API application programming interface

void setup()
{
	
	float inc = (2.0) / numPtsPerLayer;
	printf("\n %1.2f ", inc);
	for (float parameter = 0.0; parameter < 2.0; parameter += inc)
	{
		float x = radius * cos(PI * parameter);
		float y = radius * sin(PI * parameter);

		vec A(x, y, 0);
		layer_pts.push_back(A);
	}

	printf("\n %i", layer_pts.size());

}


void update(int value)
{

	
	for (auto pt : layer_pts)
	{
		stack_pts.push_back(pt);
	}

}

/////////////////////////// view  ///////////////////////////////////////////

void draw()
{


	backGround(0.75);
	drawGrid(20);

	
	glPointSize(2.0);
	for (auto pt : stack_pts)
	{
		drawPoint(pt);
	}

	glPointSize(5.0);
	glColor3f(1, 0, 0);
	for (auto pt : layer_pts)
	{
		drawPoint(pt);
	}


}

/////////////////////////// control  ///////////////////////////////////////////
void mousePress(int b, int state, int x, int y)
{
}

void mouseMotion(int x, int y)
{

}

void keyPress(unsigned char k, int xm, int ym)
{


	if (k == 'w')
	{
		Matrix4 transform;
		
		transform.translate(up);

		for (int i = 0; i< layer_pts.size(); i++)
		{
			
			layer_pts[i] = transform * layer_pts[i];			
		}

	}

	if (k == 'r')
	{
		Matrix4 transform;
		
		transform.translate(up);
		transform.rotateX(1);

		for (int i = 0; i< layer_pts.size(); i++)
		{

			layer_pts[i] = transform * layer_pts[i];
		}

	}

}





#endif // _MAIN_