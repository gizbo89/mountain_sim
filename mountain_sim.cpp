#include <iostream>
#include "input/geotiff.h"
#include "input/config_parser.h"
#include "common/common.h"
//#include "sun_rad/sunmouvement.h"
int main(int argc, char **argv) {

	if (argc!=2){
		cout<< "Error: Wrong number of arguments"<<endl;
		cout<< "Expected:" <<argv[0]<<" config_file"<<endl;
		return 1;
	}


	string configFile(argv[1]);
	GetConfig appConfig;//call to constructor
	try{appConfig.init(configFile);}
	catch(exception &e){
		std::cout<<e.what()<<std::endl;
		return 1;
	} catch(...){
		return 1;
	}

	Logger* logger_ = Logger::GetInstance(appConfig.search("Outputs", "log_name"));

	logger_->log(INFO, "Ingesting file");
	Geotiff input(appConfig.search("Inputs", "dem_path"));
	int* p = input.GetDimensions();
	std::cout << p[0]<<" " << p[1]<<" " << p[2] << std::endl;
	//auto mat = input.GetRasterBand_(1);
	//std::cout << "Element at (" << 0 << ", " << 0 << ") = " << (*mat)(0, 0) << std::endl;
	logger_->~Logger();
	return 0;
}
