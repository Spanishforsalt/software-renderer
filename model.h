#ifndef __MODEL_H__
#define __MODEL_H__ //include guards, so file isn't included multiple times

#include <vector>
#include "geometry.h"

class Model {
    private:
        std::vector<Vector3f> _vertices; //container for all vertices in a model
        std::vector<std::vector<int>> _faces; 
        //container for all faces of formal v/vt/vn hence vector of vector

    public:
        Model(const char* filename); //constructor for a model will take a path to a .obj file
        int num_of_vertices() { return (int)_vertices.size(); }
        int num_of_faces() { return (int)_faces.size(); }
        Vector3f vertex(int i) { return _vertices[i]; } //one vertex is a Vector3f denoted by the index in vector
        std::vector<int> face(int i) {return _faces[i]; }
        //one face is a vector as before, obtained from _faces by its index


};
#endif
