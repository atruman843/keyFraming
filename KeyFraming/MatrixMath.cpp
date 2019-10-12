//
//  MatrixMath.cpp
//  SimpleGlut
//
//  Created by Andrew Truman on 10/5/19.
//  Copyright © 2019 lab. All rights reserved.
//

#include "MatrixMath.hpp"
using namespace std;

class MatrixMath {
    
public:
    
    vector<float> scalarVectorMult(float S, vector<float> V) {
        vector<float> newV;
        for (int i = 0; i < V.size(); i++) {
            newV.push_back(S*V[i]);
        }
        return newV;
    }

    vector<float> vectorCrossProd(vector<float> V1, vector<float> V2) {
        if (V1.size() != V2.size()) {
            return V1;
        }
        
        vector<float> newV = {
            V1[1]*V2[2] - V1[2]*V2[1],
            V1[2]*V2[0] - V1[0]*V2[2],
            V1[0]*V2[1] - V1[1]*V2[0]
        };
        
        return newV;
        
    }

    float vectorDotProd(vector<float> V1, vector<float> V2) {
        if (V1.size() != V2.size()) {
            return 0;
        }
        
        float val = 0;
        
        for (int i = 0; i < V1.size(); i++) {
            val += V1[i] + V2[i];
        }
        
        return val;
    }

    vector<float> vectorAdd(vector<float> V1, vector<float> V2) {
        vector<float> newV;
        
        for (int i = 0; i < V1.size(); i++) {
            newV.push_back(V1[i] + V2[i]);
        }
        
        return newV;
    }
    
    vector<vector<float>> matrixMult(vector<vector<float>> M1, vector<vector<float>> M2) {
        vector<vector<float>> M3;
        for (int i = 0; i < 4; i++) {
            M3.push_back({0,0,0,0});
            for (int j = 0; j < 4; j++) {
                float sum = 0;
                for (int k = 0; k < 4; k++) {
                    sum += M1[k][i] * M2[j][k];
                }
                M3[i][j] = sum;
            }
        }
        
        return M3;
    }
};
