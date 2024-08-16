#include <iostream>
#include "input/geotiff.h"
//#include "sun_rad/sunmouvement.h"
int main(int argc, char **argv) {
	std::cout << "Hello World" << std::endl;
	const char* DEMpath = "/home/gizbo89/Desktop/MDT02-ETRS89-HU31-0180-2-COB2.tif";
	Geotiff input(DEMpath);
	int* p = input.GetDimensions();
	std::cout << p[0]<<" " << p[1]<<" " << p[2] << std::endl;
	auto mat = input.GetRasterBand_(1);
	for (int i = 0; i < mat->rows(); ++i) {
	        for (int j = 0; j < mat->cols(); ++j) {
	            std::cout << "Element at (" << i << ", " << j << ") = " << (*mat)(i, j) << std::endl;
	        }
	    }
	return 0;
}
