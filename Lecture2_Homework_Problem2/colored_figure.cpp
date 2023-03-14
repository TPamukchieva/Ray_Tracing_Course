//Defining a figure and colouring it a different colour
#define _USE_MATH_DEFINES

#include <fstream>
#include <cmath>
using namespace std;

//Output image resolution
static const int imageWidth = 700;
static const int imageHeight = 700;

static const int maxColComp = 255;


int rowCenter = imageHeight / 2;
int colCenter = imageWidth / 2;

int R = 80;       //radius of central, big circle
int r = 60;       //radii of small circles 

/*Calculating the centers of the 5 small circles, 
which are the 5 vertices of a pentagon 
(every two vertices are 72 degrees apart)*/
int c0_col_center = colCenter;
int c0_row_center = rowCenter - round((R + 0.4*r));

int c1_col_center = colCenter + round((R + 0.4*r) * cos((18 * M_PI) / 180));
int c1_row_center = rowCenter - round((R + 0.4*r) * sin((18 * M_PI) / 180));

int c2_col_center = colCenter + round((R + 0.4*r) * cos((-54 * M_PI) / 180));
int c2_row_center = rowCenter - round((R + 0.4*r) * sin((-54 * M_PI) / 180));

int c3_col_center = colCenter - round((R + 0.4*r) * cos((18 * M_PI) / 180));
int c3_row_center = rowCenter - round((R + 0.4*r) * sin((18 * M_PI) / 180));

int c4_col_center = colCenter - round((R + 0.4*r) * cos((-54 * M_PI) / 180));
int c4_row_center = rowCenter - round((R + 0.4*r) * sin((-54 * M_PI) / 180));


int main()
{
	ofstream ppmFileStream("crt_output_image2.ppm", ios::out | ios::binary);
	ppmFileStream << "P3\n";
	ppmFileStream << imageWidth << " " << imageHeight << "\n";
	ppmFileStream << maxColComp << "\n";

	for (int rowIdx = 0; rowIdx < imageHeight; ++rowIdx)
	{
		for (int colIdx = 0; colIdx < imageWidth; ++colIdx)
		{
			//using Pythagoras theorem 
			if (R >= round(sqrt(pow(colIdx - colCenter, 2) + pow(rowIdx - rowCenter, 2))))
			{
				ppmFileStream << "255 255 0\t";
			}
			else if (r >= round(sqrt(pow(colIdx - c0_col_center, 2) + pow(rowIdx - c0_row_center, 2))))
			{
				ppmFileStream << "191 148 255\t";
			}
			
			else if (r >= round(sqrt(pow(colIdx - c1_col_center, 2) + pow(rowIdx - c1_row_center, 2))))
			{
				ppmFileStream << "191 148 255\t";
			}

			else if (r >= round(sqrt(pow(colIdx - c2_col_center, 2) + pow(rowIdx - c2_row_center, 2))))
			{
				ppmFileStream << "191 148 255\t";
			}

			else if (r >= round(sqrt(pow(colIdx - c3_col_center, 2) + pow(rowIdx - c3_row_center, 2))))
			{
				ppmFileStream << "191 148 255\t";
			}

			else if (r >= round(sqrt(pow(colIdx - c4_col_center, 2) + pow(rowIdx - c4_row_center, 2))))
			{
				ppmFileStream << "191 148 255\t";
			}

			else
			{
				ppmFileStream << "0 0 0\t";
			}
			
		}
	}

	ppmFileStream.close();

	return 0;
}
