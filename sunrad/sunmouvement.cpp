#include "sunmouvement.h"



Vector3d solar_incident_angle(const double gamma_deg, const double lat) {
  const double pi = 3.14159;
  const double gamma = gamma_deg*2.0*pi/360.0;//{0=spring;90=summer;180=autumn;270=winter}
  const double phi = 0.0;//precession
  const double theta = 22.5*2.0*pi/360.0;//nutation angle
  double var2;
  //latitude angle in radians
  const double philat = lat*2.0*pi/360.0;
  ///
  const double cosphi = cos(phi);//cosinus precession angle
  const double sinphi = sin(phi);//sinus precession angle
  const double costheta = cos(theta);//cosinus nutation angle
  const double sintheta = sin(theta);//sinus nutation angle
  ///
  double       psi      = 0.0;//initial rotation
  //Nutation matrix
  Matrix3d nut;
  nut << 1.0, 0.0, 0.0,
		 0.0, costheta, sintheta,
		 0.0, -sintheta, costheta;
  //Precession matrix
  Matrix3d prec;
    prec << cosphi, sinphi, 0.0,
    		-sinphi, cosphi, 0.0,
			0.0, 0.0, 1.0;

  const double coslat = cos(philat);
  const double sinlat = sin(philat);

  //Vector representing the sun rays in a system reference attached to the sun
  Vector3d urhob;
  urhob << cos(gamma), sin(gamma), 0.0;

  //Vector attached to earth system of reference
  Vector3d unb3;
  unb3 << coslat, 0.0, sinlat;
  Matrix3d T;
    T << sinlat, 0.0, -coslat,
  		 0.0,    1.0,     0.0,
  		coslat, 0.0,  sinlat;
  Vector3d unb4;
  unb4 = T*unb3;

  const double inc = 2.0*pi/360.0;
  int i;
  for (i=0; psi<= 2*pi; i++)
	{
	   const double cospsi = cos(psi);
	   const double sinpsi = sin(psi);
	   Matrix3d rot;
	   rot << cospsi, sinpsi, 0.0,
		  	  -sinpsi, cospsi, 0.0,
			   0.0,    0.0, 1.0;
	   Vector3d urhob3;
	   urhob3 = (rot*(nut*prec))*urhob;
	   Vector3d urhob4;
	   urhob4 = T*urhob3;
	   if (urhob4.dot(unb4)>=0.0){

	   }
	   psi+=inc;
	}

	return unb4;//TODO
}

double Liner::distance(const unsigned int & x, const unsigned int & y) const{
  //function that computes the distance of the pixel to the straight line
}


vector<pair<unsigned int,unsigned int>>::iterator Liner::find_minimum(vector<pair<unsigned int,unsigned int>> mylist_) const{
  vector<double> values_;
  for (auto element : mylist_) {
          values_.push_back(distance(element.first, element.second));
      }
  //Find minimum value
  vector<double>::iterator result = min_element(values_.begin(), values_.end());
  vector<pair<unsigned int, unsigned int>>::iterator ret_val = mylist_.begin() + std::distance(values_.begin(), result);
  return ret_val;
}

void Liner::next_pixel(unsigned int & x, unsigned int & y, const case_quadrant & c, bool & keepGoing) const{
  /*This function computes the next pixel that minimizes the distance to the straight line*/
  vector<pair<unsigned int,unsigned int>> mylist_;
  if (c == case_quadrant::FIRST){
    mylist_.push_back(make_pair(x+1, y));
    mylist_.push_back(make_pair(x+1, y+1));
    mylist_.push_back(make_pair(x, y+1));
  } else if (c == case_quadrant::SECOND) {
    mylist_.push_back(make_pair(x-1, y));
    mylist_.push_back(make_pair(x-1, y+1));
    mylist_.push_back(make_pair(x, y+1));
  }
  else if (c == case_quadrant::THIRD) {
    mylist_.push_back(make_pair(x-1, y));
    mylist_.push_back(make_pair(x-1, y-1));
    mylist_.push_back(make_pair(x, y-1));
  }
  else if (c == case_quadrant::FOURTH) {
    mylist_.push_back(make_pair(x+1, y));
    mylist_.push_back(make_pair(x+1, y-1));
    mylist_.push_back(make_pair(x, y-1));
  }

  vector<pair<unsigned int,unsigned int>>::iterator result = find_minimum(mylist_);
  x = result->first;
  y = result->second;

  if (!(x >= 0 && x <= dimX_-1 && y >= 0 && y <= dimY_-1) ) keepGoing = false;

} 


vector<pair<unsigned int, unsigned int>> Liner::line_generator() const{
  /*This function takes a pixel as origin and a vector and using its projected direction, provides a list of the pixels that better fit the line
   defined by the input data
   If the angle of ray_ projected lies in 1st quadrant, then for possible next values are (x0+1,y0), (x0+1,y0+1), (x0,y0+1) -> Assess minimum error option
   If the angle of ray_ projected lies in 2nd quadrant, then for possible next values are (x0-1,y0), (x0-1,y0+1), (x0,y0+1) -> Assess minimum error option
   If the angle of ray_ projected lies in 3rd quadrant, then for possible next values are (x0-1,y0), (x0-1,y0-1), (x0,y0-1) -> Assess minimum error option
   If the angle of ray_ projected lies in 4th quadrant, then for possible next values are (x0+1,y0), (x0+1,y0-1), (x0,y0-1) -> Assess minimum error option*/
   // Compute angle of ray_ on image plane, ray_ is oriented such the direction goes from the plane to the sun and is a unitary vector
   case_quadrant c = case_quadrant::FIRST;
   if (cosine_>= 0.0 && sine_ >= 0.0) {//1st quadrant
    c = case_quadrant::FIRST;
  } else if (cosine_<= 0.0 && sine_ >= 0.0) {//2nd quadrant
    c = case_quadrant::SECOND;
  } else if (cosine_<= 0.0 && sine_ <= 0.0) {//3rd quadrant
    c = case_quadrant::THIRD;
  } else if (cosine_>= 0.0 && sine_ <= 0.0) {//4th quadrant
    c = case_quadrant::FOURTH; 
  }

  unsigned int x_current = originx_;
  unsigned int y_current = originy_;
  vector<pair<unsigned int, unsigned int>> list_;
  bool keepGoing = true;
  while (keepGoing){
    next_pixel(x_current, y_current, c, keepGoing);
    if (keepGoing) list_.push_back(make_pair(x_current, y_current));
  }

  return list_;
}

shared_ptr<MatrixXf> shade_projector(const Geotiff & DEM_, const Vector3d & ray, int band_){
  /*
  This function takes a raster DEM_ that has the height associated to each pixel.
  ray is the vector that contains the solar ray direction in the same frame of reference than DEM_. TODO, specify meaning of dimensions of ray, .
  Shade will be edited following the shade projection algorithm:
  For each pixel in order to check if its under shade, we take the direction defined by the projection of ray onto DEM_,
  if the pixels in that direction have a height higher than the elevation given by the ray departing from the current pixel, then the pixel is shaded.
  ASSUMPTIONS:
  * DEM objects are W->E in the sense of growing columns
  * DEM objects are N->S in the sense of growing rows
  */
  std::shared_ptr<MatrixXf> map_ = DEM_.GetRasterBand_(band_);
  /*The ray will be projected onto the plane, from the current pixel to the boundaries of the matrix
   in the direction of the projected ray we will check if height of pixels in that path is higher than the straight line described by the current pixel and the ray direction.
   If higher, then there is shade, if lower for all the pixels in the path, then is illuminated.
   */

  // Create list of affected pixels in the path
  //create_pixel_list(current_pixel);
	return mymatrix;
}
