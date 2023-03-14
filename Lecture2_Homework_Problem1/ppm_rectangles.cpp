//Creating my first ppm file and dividing it into rectangles with pixels of different colors.

/*The idea behind the colours of the rectangles is I tried to imitate the picture we were shown
of the RGB colours and the colours we can get when mixing them.
Since there were only 7 colours and I have 9 rectangles, I mixed yellow and red to get orange
and red and magenta to get the pink colour. Hope you like it :) */

#include <fstream>
#include <iostream>
#include <random>
using namespace std;

//image resolution 
static const int imageWidth = 1920;
static const int imageHeight = 1080;


const int row_a = imageHeight / 3;       //pixel number where the second row of rectangles start 
const int row_b = 2 * imageHeight / 3;   //pixel number where the third row of rectangles start 

const int col_a = imageWidth / 3;        //pixel number where the second column of rectangles start 
const int col_b = 2 * imageWidth / 3;    //pixel number where the third column of rectangles start 

static const int maxColComp = 255;



int main()
{
	ofstream ppmFileStream("crt_output_image.ppm", ios::out | ios::binary);
	ppmFileStream << "P3\n";
	ppmFileStream << imageWidth << " " << imageHeight << "\n";
	ppmFileStream << maxColComp << "\n";

	//generating random numbers between 0 and 255 and 0 and 128 to accomplish the "noise" effect
	random_device rd1,rd2;
	mt19937 gen(rd1());
	mt19937 gen2(rd2());
	uniform_int_distribution<> distr1(0, 255);
	uniform_int_distribution<> distr2(0, 128); //generating random numbers between 0 and 128 to get 
											   //the orange colour and the colour between magenta and red



	for (int row_idx = 0; row_idx < imageHeight; ++row_idx)
	{
		for (int col_idx = 0; col_idx < imageWidth; ++col_idx)
		{
			if (row_idx >= 0 && row_idx < row_a)
			{
				if (col_idx >= 0 && col_idx < col_a)
				{
					ppmFileStream << "0 " << distr1(gen) <<  " 0\t";
				}

				else if (col_idx >= col_a && col_idx < col_b)
				{
					ppmFileStream << "0 " << distr1(gen) << " " << distr1(gen) << "\t";
				}

				else
				{
					ppmFileStream << "0 0 " << distr1(gen) << "\t";
				}
			}

			if (row_idx >= row_a && row_idx < row_b)
			{
				if (col_idx >= 0 && col_idx < col_a)
				{
					ppmFileStream << distr1(gen) << " " << distr1(gen) << " 0" << "\t";
				}

				else if (col_idx >= col_a && col_idx < col_b)
				{
					ppmFileStream << distr1(gen) << " " << distr1(gen) << " " << distr1(gen) << "\t";
				}

				else
				{
					ppmFileStream << distr1(gen) << " 0 " << distr1(gen) << "\t";
				}
			}

			if (row_idx >= row_b && row_idx < imageHeight)
			{
				if (col_idx >= 0 && col_idx < col_a)
				{
					ppmFileStream << distr1(gen) << " " << distr2(gen2) << " 0\t"; 
				}

				else if (col_idx >= col_a && col_idx < col_b)
				{
					ppmFileStream << distr1(gen) << " 0 0\t";
				}

				else
				{
					ppmFileStream << distr1(gen) << " 0 " << distr2(gen2) <<"\t";
				}
			}
		}
	}
	
	ppmFileStream.close();

	return 0;
}