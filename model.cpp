#include <fstream>
#include <sstream>
#include <iostream>
#include "model.h"


Model::Model(const std::string filename){
    
    std::ifstream in;

    in.open(filename, std::ifstream::in);

    if (in.fail()) {
        std::cerr << "Failed to open " << filename << std::endl;
        return;
    }

    float x, y, z;
    std::string trash;

    std::string line;
    while (!in.eof()){
        std:getline(in, line);


        if (line[0] == 'v' && line[1]== ' '){
            std::istringstream iss(line);
            iss >> trash >> x >> y >> z;
            printf("X: %f, Y: %f, Z: %f \n", x, y, z);
        }




    }

}