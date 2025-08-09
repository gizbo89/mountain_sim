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
#include <vector>
#include <math.h>       /* sqrt */
#include <utility> 
#include<bits/stdc++.h> 

enum class case_quadrant {
    FIRST, SECOND, THIRD, FOURTH
};

class Liner {
public:
    Liner(unsigned int dimX, unsigned int dimY, unsigned int originx,
     unsigned int originy, double cosine, double sine): dimX_(dimX), dimY_(dimY),
        originx_(originx), originy_(originy), cosine_(cosine), sine_(sine) {}
    vector<pair<unsigned int, unsigned int>> line_generator() const;
private:
    void next_pixel(unsigned int & x, unsigned int & y, const case_quadrant & c, bool & keepGoing) const;
    vector<pair<unsigned int,unsigned int>>::iterator find_minimum(vector<pair<unsigned int,unsigned int>> mylist_) const;
    double distance(const unsigned int & x, const unsigned int & y) const;
    unsigned int dimX_;
    unsigned int dimY_;
    unsigned int originx_;
    unsigned int originy_;
    double cosine_;
    double sine_;
};


Eigen::Vector3d solar_incident_angle();
shared_ptr<MatrixXf> shade_projector(const Geotiff & DEM_);

#endif /* SUNRAD_SUNMOUVEMENT_H_ */
