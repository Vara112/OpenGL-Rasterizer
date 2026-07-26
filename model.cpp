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

   //BUG: Obj's faces are 1 based (not 0 based). Must offset all index's by 1
   //Order of operations:
   //1. Search for vertex index's in facet_vrt
   //2. Then return the vert for that index

    int index = (iface * 3) + nthvert;

    int vertInedx = facet_vrt[index];

    return vert(vertInedx);
}
