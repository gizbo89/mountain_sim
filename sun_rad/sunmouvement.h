/*
 * sunmouvement.h
 *
 *  Created on: Mar 12, 2024
 *      Author: gizbo89
 */

#ifndef SUN_RAD_SUNMOUVEMENT_H_
#define SUN_RAD_SUNMOUVEMENT_H_
#include "common/common.h"
#include "input/geotiff.cpp"

Eigen::Vector3d solar_incident_angle();
void shade_projector(const Geotiff & DEM_, double lat, Geotiff & Shade);

#endif /* SUN_RAD_SUNMOUVEMENT_H_ */
