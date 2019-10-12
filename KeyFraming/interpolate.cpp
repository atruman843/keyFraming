//
//  interpolate.cpp
//  SimpleGlut
//
//  Created by Andrew Truman on 9/21/19.
//  Copyright © 2019 lab. All rights reserved.

#include "interpolate.hpp"
#include <iostream>
using namespace std;


class Interpolate {
    public:

    int ind_x=0;
    int ind_y=1;
    int ind_z=2;
    int ind_phi=3;
    int ind_theta=4;
    int ind_psi=5;
    int ind_omega=6;
    float dt = 0.5;
    
    bool curve = true;
    bool quaternion = false;
    
    std::vector<std::vector<float>>  catmull_rom= {
        {-0.5, 1.5, -1.5, 0.5},
        {1.0, -2.5, 2.0, -0.5},
        {-0.5, 0.0, 0.5,  0.0},
        { 0.0, 1.0, 0.0,  0.0}
    };

    std::vector<std::vector<float>> b_spline = {
        {-0.167, 0.5, -0.5, 0.167},
        {  0.5,  -1.0,  0.5,  0.0},
        { -0.5,  0.0,  0.5,   0.0},
        {0.167, 0.67, 0.167,  0.0}
    };
    
    std::vector<std::vector<float>> M;
    std::vector<std::vector<float>> keyFrames;
    
    std::vector<Event> events;
    
    Interpolate(std::vector<std::vector<float>> keyFrames, bool curve, bool quaternion, float dt) {
        this->curve = curve;
        this->quaternion = quaternion;
        this->keyFrames = keyFrames;
        this->dt = dt;
        whichCurve();
        interpolate();
    }
    
    void whichCurve() {
        if (curve == true) {
            M = catmull_rom;
        }
        else {
            M = b_spline;
        }
    }
    
    
    std::vector<Event> getEvents() {
        return events;
    }
    
    void interpolate() {
        for (float i = 0; i + 4 <= keyFrames.size(); i++) {
            std::vector<float> frameVals;
            for (float j = 0; j < 60*dt; j++) {
                frameVals.push_back(getParametricValues(i, ind_x, j));
                frameVals.push_back(getParametricValues(i, ind_y, j));
                frameVals.push_back(getParametricValues(i, ind_z, j));
                frameVals.push_back(getParametricValues(i, ind_phi, j));
                frameVals.push_back(getParametricValues(i, ind_theta, j));
                frameVals.push_back(getParametricValues(i, ind_psi, j));
                frameVals.push_back(getParametricValues(i, ind_omega, j));
                Event frame;
                frame.setFrame(frameVals);
                if (quaternion) {frame.quaternionCalc();}
                else {frame.calcRotationMatrix();}
                this->events.push_back(frame);
                frameVals.clear();
            }
        }
    }

    float getParametricValues(int index1, int index2, float t) {
        float out_sum = 0;
        t /= 60;
        
        for (int i = 0; i < M.size(); i++) {
            float in_sum = 0;
            for (int j = 0; j < M.size(); j++) {
                in_sum += pow(t, (3 - j)) * M[j][i];
            }
            out_sum += in_sum * keyFrames[index1 + i][index2];
        }
        return out_sum;
    }
    
};


