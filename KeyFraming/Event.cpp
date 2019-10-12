//
//  Event.cpp
//  SimpleGlut
//
//  Created by Andrew Truman on 9/22/19.
//  Copyright © 2019 lab. All rights reserved.
//

#include "Event.hpp"

class Event {
    
    public:

    vector<vector<float>> rotationMatrix;
    vector<float> quat;
    GLfloat rotationVector[16];
    vector<float> newFrame;
    MatrixMath m;
    float PI = 3.14159;
    
    vector<float> getFrame() {
        return newFrame;
    }
    
    GLfloat* getRotationVector() {
        return rotationVector;
    }
    
    vector<float> getQuaternion() {
        return quat;
    }
    
    void setFrame(vector<float> frame) {
        this->newFrame = frame;
    }
    
    void calcRotationMatrix() {
        
        float x = (newFrame[3]*PI)/180;
        float y = (newFrame[4]*PI)/180;
        float z = (newFrame[5]*PI)/180;
        
        vector<vector<float>> Rz = {
            {cos(z), -sin(z), 0, 0},
            {sin(z), cos(z),  0, 0},
            {0, 0, 1, 0},
            {0, 0, 0, 1}
        };
        
        vector<vector<float>> Ry = {
            {cos(y), 0, sin(y), 0},
            {0, 1, 0, 0},
            {-sin(y), 0, cos(y), 0},
            {0, 0, 0, 1}
        };
        
        vector<vector<float>> Rx = {
            {1, 0, 0, 0},
            {0, cos(x), -sin(x), 0},
            {0, sin(x), cos(x),  0},
            {0, 0, 0, 1}
        };

        rotationMatrix = m.matrixMult(m.matrixMult(Rz, Ry), Rx);
        
        for (int i = 0; i < rotationMatrix.size(); i++) {
            for (int j = 0; j < rotationMatrix[i].size(); j++) {
                rotationVector[i*4 + j] = rotationMatrix[j][i];
            }
        }
        
    }
    
    void quaternionCalc() {
        float x = (newFrame[3]*PI)/180;
        float y = (newFrame[4]*PI)/180;
        float z = (newFrame[5]*PI)/180;
        
        vector<float> Qx = {cos(x/2), sin(x/2), 0, 0};
        vector<float> Qy = {cos(y/2), 0, sin(y/2), 0};
        vector<float> Qz = {cos(z/2), 0, 0, sin(z/2)};
        
        this->quat = quaternionMult(quaternionMult(Qx, Qy), Qz);
        
    }
    
    vector<float> quaternionMult(vector<float> Q1, vector<float> Q2) {
        float S1 = Q1[0];
        float S2 = Q2[0];
        float newS = 0;
        vector<float> V1 = {Q1[1], Q1[2], Q1[3]};
        vector<float> V2 = {Q2[1], Q2[2], Q2[3]};
        vector<float> newV;
        vector<float> Q;
        
        newS = S1*S2 - m.vectorDotProd(V1, V2);
        newV = m.vectorAdd(m.vectorAdd(m.scalarVectorMult(S1, V2), m.scalarVectorMult(S2, V1)), m.vectorCrossProd(V1, V2));
                         
        Q = {newS, newV[0], newV[1], newV[2]};
        
        return Q;
        
    }
};
