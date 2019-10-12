//
//  MatrixCalc.cpp
//  SimpleGlut
//
//  Created by Andrew Truman on 10/2/19.
//  Copyright © 2019 lab. All rights reserved.
//

#include <stdio.h>
#include <vector>
using namespace std;

vector<vector<float>> matrixMult(vector<vector<float>> M1, vector<vector<float>> M2) {
    vector<vector<float>> M3;
    
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            float sum = 0;
            for (int k = 0; k < 4; k++) {
                sum += M1[i][k] * M2[k][j];
            }
            M3[i][j] = sum;
        }
    }
    
    return M3;
}
