#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "model.h"

//Constructor for Model class
Model::Model(const char* filename) { 
    std::ifstream object_file(filename);
    std::string line;

    while (getline(object_file, line)) { //read each line from file into string
        std::istringstream iss(line); //iss denotes each "word" up to a whitespace

        if (line[0] == 'v') {
            char temp; //"trash" char for non-value elements such as 'v' or 'f'

            iss >> temp; //dumps 'v' into temp so its not processed anymore
            Vector3f v;
            iss >> v[0] >> v[1] >> v[2]; //vertex line is in form "v 1.0f 2.0f 3.0f"
            _vertices.push_back(v);
        
        } else if (line[0] == 'f') {
            char temp; //"trash" char for non-value elements such as 'v' or 'f'
            int index, temp_int; 

            std::vector<int> f;
            iss >> temp;
            
            while (iss >> index >> temp >> temp_int >> temp >> temp_int) {
                /* f lines are formated "f 1/2/3 4/5/6 7/8/9" 
                    the first int after each space refers to the index of a 
                    vertex in the .obj file*/

                index--; //.obj files are 1-indexed rather than 0-indexed
                f.push_back(index); //append index to f container
            }
            _faces.push_back(f); //append f container into _faces
        }     
    }
}

