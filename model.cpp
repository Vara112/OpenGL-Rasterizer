#include <fstream>
#include <sstream>
#include <iostream>
#include "model.h"
#include <vector>
#include <typeinfo>

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
            
            //Add vertex points to my vertex's vector
            verts.push_back({x, y, z});


        }




    }

}
int Model::nverts() const{
    //Returns the number of vertex;s in the models vector
    return verts.size();
}



vec3 Model::vert(const int i) const {
    //Allows us to access vertex's from our models vector
    return verts[i];
}

