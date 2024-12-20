#include "sunmouvement.h"

Eigen::Vector3d solar_incident_angle(const double gamma_deg, const double lat) {
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
  Eigen::Matrix3d nut;
  nut << 1.0, 0.0, 0.0,
		 0.0, costheta, sintheta,
		 0.0, -sintheta, costheta;
  //Precession matrix
  Eigen::Matrix3d prec;
    prec << cosphi, sinphi, 0.0,
    		-sinphi, cosphi, 0.0,
			0.0, 0.0, 1.0;

  const double coslat = cos(philat);
  const double sinlat = sin(philat);

  //Vector representing the sun rays in a system reference attached to the sun
  Eigen::Vector3d urhob;
  urhob << cos(gamma), sin(gamma), 0.0;

  //Vector attached to earth system of reference
  Eigen::Vector3d unb3;
  unb3 << coslat, 0.0, sinlat;
  Eigen::Matrix3d T;
    T << sinlat, 0.0, -coslat,
  		 0.0,    1.0,     0.0,
  		coslat, 0.0,  sinlat;
  Eigen::Vector3d unb4;
  unb4 = T*unb3;

  const double inc = 2.0*pi/360.0;
  int i;
  for (i=0; psi<= 2*pi; i++)
	{
	   const double cospsi = cos(psi);
	   const double sinpsi = sin(psi);
	   Eigen::Matrix3d rot;
	   rot << cospsi, sinpsi, 0.0,
		  	  -sinpsi, cospsi, 0.0,
			   0.0,    0.0, 1.0;
	   Eigen::Vector3d urhob3;
	   urhob3 = (rot*(nut*prec))*urhob;
	   Eigen::Vector3d urhob4;
	   urhob4 = T*urhob3;
	   if (urhob4.dot(unb4)>=0.0){

	   }
	   psi+=inc;
	}

	return 0;
}


void shade_projector(const DEM & DEM_,  double lat, Geotiff & Shade){
  /*
  This function takes a raster DEM_ that has the height associated to each pixel.
  ray is the vector that contains the solar ray direction in the same frame of reference than DEM_.
  Shade will be edited following the shade projection algorithm:
  For each pixel in order to check if its under shade, we take the direction defined by the projection of ray onto DEM_,
  if the pixels in that direction have a height higher than the elevation given by the ray departing from the current pixel, then the pixel is shaded.
  ASSUMPTIONS:
  * DEM objects are W->E in the sense of growing columns
  * DEM objects are N->S in the sense of growing rows
  */

}
