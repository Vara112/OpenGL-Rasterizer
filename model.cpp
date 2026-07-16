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

    std::string line;
    while (!in.eof()){
        std:getline(in line);


        



    }

}