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

    
    std::string trash;

    std::string line;
    while (!in.eof()){
        std::getline(in, line);




        if (line[0] == 'v' && line[1]== ' '){
            std::istringstream iss(line);
            float x, y, z;
            iss >> trash >> x >> y >> z;
            
            //Add vertex points to my vertex's vector
            verts.push_back({x, y, z});


        }
        else if (line[0] == 'f'){
            //faces

            std::istringstream iss(line);
            std::string vecA, vecB, vecC;
            iss >> trash >> vecA >> vecB >> vecC;
            int a, b, c;
 
            std::sscanf(vecA.c_str(), "%d/%d/%d", &a, &b, &c);
            facet_vrt.push_back(a);

            std::sscanf(vecB.c_str(), "%d/%d/%d", &a, &b, &c);
            facet_vrt.push_back(a);

            std::sscanf(vecC.c_str(), "%d/%d/%d", &a, &b, &c);
            facet_vrt.push_back(a);


        }




    }

}

int Model::nfaces() const{

    return static_cast<int>(facet_vrt.size()/3);

}

int Model::nverts() const{
    //Returns the number of vertex;s in the models vector
    return verts.size();
}



vec3 Model::vert(const int i) const {
    //Allows us to access vertex's from our models vector
    return verts[i];
}


vec3 Model::vert(const int iface, const int nthvert) const{

    int index = (iface * 3) + nthvert;

    return verts[index];
}
