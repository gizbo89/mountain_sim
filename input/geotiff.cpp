/*
 * geotiff.cpp
 *
 *  Created on: Mar 20, 2024
 *      Author: gizbo89
 */
#include "geotiff.h"


  Geotiff::Geotiff( const char* tiffname ) {
      filename = tiffname ;
      GDALAllRegister();

      // set pointer to Geotiff dataset as class member.
      geotiffDataset = (GDALDataset*) GDALOpen(filename, GA_ReadOnly);
      
      // set the dimensions of the Geotiff
      NROWS   = GDALGetRasterYSize( geotiffDataset );
      NCOLS   = GDALGetRasterXSize( geotiffDataset );
      NLEVELS = GDALGetRasterCount( geotiffDataset );

    }

    // define destructor function to close dataset,
    // for when object goes out of scope or is removed
    // from memory.
  Geotiff::~Geotiff() {
      // close the Geotiff dataset, free memory for array.
      GDALClose(geotiffDataset);
      GDALDestroyDriverManager();
    }

  const char * Geotiff::GetFileName() {
    /*
      * function GetFileName()
      * This function returns the filename of the Geotiff.
      */
    return filename;
  }

  const char * Geotiff::GetProjection() {
    /* function const char* GetProjection():
      *  This function returns a character array (string)
      *  for the projection of the geotiff file. Note that
      *  the "->" notation is used. This is because the
      *  "geotiffDataset" class variable is a pointer
      *  to an object or structure, and not the object
      *  itself, so the "." dot notation is not used.
      */
    return geotiffDataset->GetProjectionRef();
  }

  double * Geotiff::GetGeoTransform() {
    /*
      * function double *GetGeoTransform()
      *  This function returns a pointer to a double that
      *  is the first element of a 6 element array that holds
      *  the geotransform of the geotiff.
      */
    geotiffDataset->GetGeoTransform(geotransform);
    return geotransform;
  }

  double Geotiff::GetNoDataValue() {
    /*
      * function GetNoDataValue():
      *  This function returns the NoDataValue for the Geotiff dataset.
      *  Returns the NoData as a double.
      */
    return (double)geotiffDataset->GetRasterBand(1)->GetNoDataValue();
  }

  int * Geotiff::GetDimensions() {
    /*
      * int *GetDimensions():
      *
      *  This function returns a pointer to an array of 3 integers
      *  holding the dimensions of the Geotiff. The array holds the
      *  dimensions in the following order:
      *   (1) number of columns (x size)
      *   (2) number of rows (y size)
      *   (3) number of bands (number of bands, z dimension)
      */
    dimensions[0] = NROWS;
    dimensions[1] = NCOLS;
    dimensions[2] = NLEVELS;
    return dimensions;
  }

  std::shared_ptr<MatrixXf> Geotiff::GetRasterBand_(int z) {

    /*
      * function float** GetRasterBand_(int z):
      * This function reads a band from a geotiff at a
      * specified vertical level (z value, 1 ...
      * n bands). To this end, the Geotiff's GDAL
      * data type is passed to a switch statement,
      * and the template function GetArray2D (see below)
      * is called with the appropriate C++ data type.
      * The GetArray2D function uses the passed-in C++
      * data type to properly read the band data from
      * the Geotiff, cast the data to float**, and return
      * it to this function. This function returns that
      * float** pointer.
      */

    auto retVal = make_shared<MatrixXf>();
    switch( GDALGetRasterDataType(geotiffDataset->GetRasterBand(z)) ) {
      case 0:
    	return retVal; // GDT_Unknown, or unknown data type.
      case 1:
        // GDAL GDT_Byte (-128 to 127) - unsigned  char
        return GetArray2D<unsigned char>(z);
      case 2:
        // GDAL GDT_UInt16 - short
        return GetArray2D<unsigned short>(z);
      case 3:
        // GDT_Int16
        return GetArray2D<short>(z);
      case 4:
        // GDT_UInt32
        return GetArray2D<unsigned int>(z);
      case 5:
        // GDT_Int32
        return GetArray2D<int>(z);
      case 6:
        // GDT_Float32
        return GetArray2D<float>(z);
      case 7:
        // GDT_Float64
        return GetArray2D<double>(z);
      default:
        break;
    }
    return retVal;
  }

  template<typename T>
  std::shared_ptr<MatrixXf> Geotiff::GetArray2D(int layerIndex) {

      /*
      * function float** GetArray2D(int layerIndex):
      * This function returns a pointer (to a pointer)
      * for a float array that holds the band (array)
      * data from the geotiff, for a specified layer
      * index layerIndex (1,2,3... for GDAL, for Geotiffs
      * with more than one band or data layer, 3D that is).
      *
      * Note this is a template function that is meant
      * to take in a valid C++ data type (i.e. char,
      * short, int, float), for the Geotiff in question
      * such that the Geotiff band data may be properly
      * read-in as numbers. Then, this function casts
      * the data to a float data type automatically.
      */

      // get the raster data type (ENUM integer 1-12,
      // see GDAL C/C++ documentation for more details)
      GDALDataType bandType = GDALGetRasterDataType(
        geotiffDataset->GetRasterBand(layerIndex));

      // get number of bytes per pixel in Geotiff
      int nbytes = GDALGetDataTypeSizeBytes(bandType);

      // allocate pointer to memory block for one row (scanline)
      // in 2D Geotiff array.
      T *rowBuff = (T*) CPLMalloc(nbytes*NCOLS);
      std::shared_ptr<Eigen::MatrixXf> mymatrix = std::make_shared<Eigen::MatrixXf>(NROWS, NCOLS);

      for(int row=0; row<NROWS; row++) {     // iterate through rows

        // read the scanline into the dynamically allocated row-buffer
        /*
        RasterIO(GDALRWFlag eRWFlag, int nXOff, int nYOff, int nXSize, int nYSize, void *pData,
        int nBufXSize, int nBufYSize, GDALDataType eBufType, GSpacing nPixelSpace, GSpacing nLineSpace, GDALRasterIOExtraArg *psExtraArg)
        (nXOff, nYOff)*----------*
                      |  nXSize  |
                      |          |
                      |          |nYSize
                      *----------*
        */
        CPLErr e = geotiffDataset->GetRasterBand(layerIndex)->RasterIO(
          GF_Read,0,row,NCOLS,1,rowBuff,NCOLS,1,bandType,0,0);
        if(!(e == 0)) {
          cout << "Warning: Unable to read scanline in Geotiff!" << endl;
          exit(1);
        }

        for( int col=0; col<NCOLS; col++ ) { // iterate through columns
          (*mymatrix)(row, col) = (float)rowBuff[col];
        }
      }
      CPLFree( rowBuff );
      return mymatrix;
  }

  /*

  addRasterBand(const MatrixXf & sample){
      // Initialize GDAL
    GDALAllRegister();

    // Open the existing GeoTIFF file in update mode
    GDALDataset *poDataset = (GDALDataset *)GDALOpen(this->filename, GA_Update);
    if (poDataset == nullptr) {
        printf("Failed to open the file.\n");
        return 1;
    }

    // Get dimensions of the dataset
    int xSize = poDataset->GetRasterXSize();
    int ySize = poDataset->GetRasterYSize();

    // Add a new band to the dataset (e.g., of type GDT_Byte)
    CPLErr eErr = poDataset->AddBand(GDT_Byte, nullptr);
    if (eErr != CE_None) {
        printf("Failed to add a new band.\n");
        GDALClose(poDataset);
        return 1;
    }

    // Get the new band (the last band)
    int newBandIndex = poDataset->GetRasterCount(); // Get the number of bands (the new band is the last one)
    GDALRasterBand *poBand = poDataset->GetRasterBand(newBandIndex);

    // Optionally write data to the new band
    // Create a buffer to hold the new band data (example: fill with 0's)
    unsigned char *buffer = (unsigned char *)CPLMalloc(sizeof(unsigned char) * this->NROWS * this->NCOLS);
    memset(buffer, 0, this->NROWS * this->NCOLS);

    // Write the buffer to the new band
    eErr = poBand->RasterIO(GF_Write, 0, 0, xSize, ySize, buffer, xSize, ySize, GDT_Byte, 0, 0);
    if (eErr != CE_None) {
        printf("Failed to write data to the new band.\n");
        CPLFree(buffer);
        GDALClose(poDataset);
        return 1;
    }

    // Free the buffer
    CPLFree(buffer);

    // Close the dataset and clean up
    GDALClose(poDataset);
  }
*/




