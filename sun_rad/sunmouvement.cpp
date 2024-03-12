#include "sunmouvement.h"

Eigen::VectorXd solar_incident_angle() {
  const double pi = 3.14159;
  double var1;
  cout<<"Introduzca la posición de la tierra en la eclíptica: {0:90(primavera),90:180(verano),180:270(otoño),270:360(invierno)}"<<endl;
  cin >> var1;
  const double gamma = var1*2.0*pi/360.0;//{0=spring;90=summer;180=autumn;270=winter}
  const double phi = 0.0;//precession
  const double theta = 22.5*2.0*pi/360.0;//nutation angle
  double var2;
  cout<<"Introduzca la latitud"<<endl;
  cin >> var2;
  const double philat = var2*2.0*pi/360.0;//latitude angle
  const double cosphi = cos(phi);//cosinus precession angle
  const double sinphi = sin(phi);//sinus precession angle
  const double costheta = cos(theta);//cosinus nutation angle
  const double sintheta = sin(theta);//sinus nutation angle
  double       psi      = 0.0;//initial rotation
  Eigen::Matrix3d nut;
  nut << 1.0, 0.0, 0.0,
		 0.0, costheta, sintheta,
		 0.0, -sintheta, costheta;
  Eigen::Matrix3d prec;
    prec << cosphi, sinphi, 0.0,
    		-sinphi, cosphi, 0.0,
			0.0, 0.0, 1.0;
  const double coslat = cos(philat);
  const double sinlat = sin(philat);

  Eigen::Vector3d unb3;
  unb3 << coslat, 0.0, sinlat;
  const vector urhob {cos(gamma),sin(gamma),0.0};

  const double inc = 2.0*pi/360.0;
  int i;
  const tensor T {sinlat,1.0,sinlat,0.0,-coslat,0.0};
  unb3 = T*unb3;
  ofstream myfile;
  myfile.open ("output.txt");
for (i=0; psi<= 2*pi; i++)
{
   const double cospsi = cos(psi);
   const double sinpsi = sin(psi);
   const tensor rot {cospsi,cospsi,1.0,0.0,0.0,sinpsi};
   vector urhob3;
   urhob3 = (rot*(nut*prec))*urhob;
   urhob3 = T*urhob3;
   //myfile <<  "\n{u_rho}_b3*{u_n}_b3= " << urhob3*unb3 << endl;
   //myfile <<  "{u_rho}_b3"<< endl << urhob3 << endl;
   if (urhob3*unb3<=0.0){
   myfile << 1.0 <<" "<< 1.0 << " " << 0.0 <<" "<< -urhob3.v[0] << " "<< -urhob3.v[1] << " "<< -urhob3.v[2]  << endl;
   }
   psi+=inc;
}
  myfile << 1.0 <<" "<< 1.0 << " " << 0.0 <<" "<< unb3.v[0] << " "<< unb3.v[1] << " "<< unb3.v[2]  << endl;
  myfile << 1.0 <<" "<< 1.0 << " " << 0.0 <<" "<< -1.0 << " "<< 0.0 << " "<< 0.0  << endl;
  myfile.close();
  

return 0;
}
