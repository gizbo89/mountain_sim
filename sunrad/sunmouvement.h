/*
 * sunmouvement.h
 *
 *  Created on: Mar 12, 2024
 *      Author: gizbo89
 */

#ifndef SUNRAD_SUNMOUVEMENT_H_
#define SUNRAD_SUNMOUVEMENT_H_
#include "common/common.h"
#include "input/geotiff.h"

Eigen::Vector3d solar_incident_angle();
shared_ptr<MatrixXf> shade_projector(const Geotiff & DEM_);

#endif /* SUNRAD_SUNMOUVEMENT_H_ */
