/*
 * geotiff.h
 *
 *  Created on: Apr 20, 2024
 *      Author: gizbo89
 */

#ifndef INPUT_GEOTIFF_H_
#define INPUT_GEOTIFF_H_
#include "iostream"
#include "string"
#include "gdal_priv.h"
#include "cpl_conv.h"
#include "gdalwarper.h"
#include "stdlib.h"
using namespace std;
typedef std::string String;

class Geotiff {

  private:
	const char* filename;        // name of Geotiff
    GDALDataset *geotiffDataset; // Geotiff GDAL datset object.
    double geotransform[6];      // 6-element geotranform array.
    int dimensions[3];           // X,Y, and Z dimensions.
    int NROWS,NCOLS,NLEVELS;     // dimensions of data in Geotiff.

  public:

    // define constructor function to instantiate object
    // of this Geotiff class.
    Geotiff( const char* tiffname );
    ~Geotiff();
    const char *GetFileName();
    const char *GetProjection();
    double *GetGeoTransform();
    double GetNoDataValue();
    int *GetDimensions();
    float** GetRasterBand(int z);
    template<typename T>
    float** GetArray2D(int layerIndex,float** bandLayer);
};
#endif /* INPUT_GEOTIFF_H_ */
