#include<fstream>
#include<iostream>
#include<vector>
#include<cmath>

using namespace std;

//output image resolution
static const int imageWidth = 1280;
static const int imageHeight = 720;

//aspect ratio constant
//converting either the divisor or divident to a float, otherwise aspectRatio is an int 
const float aspectRatio = float(imageWidth) / imageHeight;

static const int maxColorComp = 255;

//z-coordinate is constant in the -z direction equal to 1
const int z = -1;

int main()
{

	ofstream ppmFileStream("crt_output_image.ppm", ios::out | ios::binary);
	ppmFileStream << "P3\n";
	ppmFileStream << imageWidth << " " << imageHeight << "\n";
	ppmFileStream << maxColorComp << "\n";

	for (int row_idx = 0; row_idx < imageHeight; ++row_idx)
	{
		for (int col_idx = 0; col_idx < imageWidth; ++col_idx)
		{
			//changing coordinates of a pixel from its upper left corner to its center

			/*swapping x and y since in the right handed coordinate system, y points upwards
			and therefore accounts for the number of rows and the x coordinate points to the right
			therefore changes as the number of columns changes */

			float x_new = col_idx + 0.5;
			float y_new = row_idx + 0.5;

			//converting raster coordinates to NDC coordinates (boundaries between 0 and 1) 
			x_new /= imageWidth;
			y_new /= imageHeight;

			//converting NDC coordinates to Screen coordinates (boundaries between -1 and 1)
			x_new = (2.0 * x_new) - 1.0;
			y_new = 1.0 - (2.0 * y_new);

			//This takes into account the aspect ratio 
			x_new *= aspectRatio;

			//declaring, defining and normalizing a vector 
			std::vector<float> vec{ x_new, y_new, z };
			float vec_len = sqrt(pow(vec[0], 2) + pow(vec[1], 2) + pow(vec[2], 2));
			for (auto i = vec.begin(); i != vec.end(); ++i)
			{
				*i /= vec_len;
			}

			/*Each component of the normalised vector gets multiplied by 255 to obtain a color component:
			red corresponds to first component of the normalised direction vector, green to second
			and blue to third component (z-component).

			Some of the values are negative but since the rays are symmetric with respect to
			the origin, we can just take the absolute value of the negative numbers */

			int r = abs(maxColorComp * vec[0]);
			int g = abs(maxColorComp * vec[1]);
			int b = abs(maxColorComp * vec[2]);

			ppmFileStream << r << ' ' << g << ' ' << b << "\n";

		}
	}

	ppmFileStream.close();

	return 0;
}