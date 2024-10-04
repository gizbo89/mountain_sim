#include <iostream>
#include "input/geotiff.h"
#include "common/common.h"
//#include "sun_rad/sunmouvement.h"
int main(int argc, char **argv) {
	if (argc!=2){
		cout<< "Error: Wrong number of arguments"<<endl;
		cout<< "Expected:" <<argv[0]<<" config_file"<<endl;
		return 1;
	}
	Logger* logger_ = Logger::GetInstance("/home/gizbo89/Desktop/test.log");
	const char* DEMpath = "/home/gizbo89/Desktop/MDT02-ETRS89-HU31-0180-2-COB2.tif";
	logger_->log(INFO, "Ingesting file");
	Geotiff input(DEMpath);
	int* p = input.GetDimensions();
	std::cout << p[0]<<" " << p[1]<<" " << p[2] << std::endl;
	//auto mat = input.GetRasterBand_(1);
	//std::cout << "Element at (" << 0 << ", " << 0 << ") = " << (*mat)(0, 0) << std::endl;
	logger_->~Logger();
	return 0;
}
