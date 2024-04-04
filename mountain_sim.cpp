#include <iostream>
#include "input/geotiff.cpp"
#include "sun_rad/sunmouvement.h"

int main(int argc, char **argv) {
	std::cout << "Hello World" << std::endl;
	const char* DEMpath = "/home/gizbo89/Desktop/MDT02-ETRS89-HU31-0180-2-COB2.tif";
	Geotiff input(DEMpath);
	Geotiff shade();
	shade_projector(input, lat, Date, shade);
	return 0;
	//solar_incident_angle();
}
