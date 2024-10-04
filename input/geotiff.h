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
#include <memory>
#include "gdal_priv.h"
#include "cpl_conv.h"
#include "gdalwarper.h"
#include "stdlib.h"
#include "common/common.h"
typedef std::string String;

class Geotiff {

  private:
	const char* filename;        // name of Geotiff
    GDALDataset *geotiffDataset; // Geotiff GDAL datset object.
    double geotransform[6];      // 6-element geotranform array.
    int dimensions[3];           // X,Y, and Z dimensions.
    int NROWS,NCOLS,NLEVELS;     // dimensions of data in Geotiff.
    template<typename T>
    shared_ptr<MatrixXf> GetArray2D(int layerIndex);

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
    std::shared_ptr<MatrixXf> GetRasterBand_(int z);
    //addRasterBand(const MatrixXf & sample);


};
#endif /* INPUT_GEOTIFF_H_ */
