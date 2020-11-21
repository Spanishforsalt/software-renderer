#include <cmath>
#include <vector>
#include "model.h"
#include "geometry.h"
#include "tgaimage.h"

const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red   = TGAColor(255, 0,   0,   255);
const int width  = 800;
const int height = 800;
Model* model = NULL;


void line(int x0, int y0, int x1, int y1, TGAImage &image, TGAColor colour) { //Utilising Bresenhelm's line drawing algorithm
	
	bool steep = false;

	if (std::abs(x0-x1) < std::abs(y0-y1)) { //if the line is taller than it is wide, transpose
		std::swap(x0,y0);
		std::swap(x1,y1);
		steep = true;
	}

	if (x0>x1) { //two of the same line drawn in opposite directions should be symmetrical, therefore:
		std::swap(x0,x1); //draw from left to right always
		std::swap(y0,y1);
	}

	if (x0 < 0 || x1 > image.get_width() || y0 < 0 || y1 > image.get_height()){
		exit(1); //Check for points being within borders of image now that we know x0<x1 and y0<y1
	}

	int dx = x1-x0; //Remove the divisor from the loop as it stays the same per line
	int dy = y1-y0;
	float d_slope_error = abs(dy)*2; // instead of abs(dy/float(dx)) we use this to remove floating point arithmetic
	//slope_error tells program how far from ideal straight line it is
	float slope_error = 0;
	int y = y0;
	const int yincr = (y1>y0? 1 : -1); //Computed before loop for optimasation

	if (steep) {
		for (int x = x0; x < x1; x++) {
			image.set(y,x,colour); //account for transposition
			slope_error += d_slope_error;
			if (slope_error > dx) {
				y += yincr; //y++ or y-- depending on if target is higher or lower than where we are
				slope_error -= dx * 2;
				/* program is now closer to ideal straight line therefore reduce error,
			avoiding floating point arithemtic by multiplying by 2 */
			}
		}
	} else {
		for (int x = x0; x < x1; x++) {
			image.set(x,y,colour);
			slope_error += d_slope_error;
			if (slope_error > dx) {
				y += yincr; //y++ or y-- depending on if target is higher or lower than where we are
				slope_error -= dx * 2;
			}
		}
	}
	/* if statements are seperated outside of for loop so they aren't checked several times over
	note, g++ -O3 is smart enough to optimise the code better than I can, this is purely for my own education*/
}

int main(int argc, char** argv) {
	(argc == 2) ? model = new Model(argv[1]) : model = new Model("obj/african_head.obj");
	/* if file path is specified in command line arguments then use object at path as model
		else use default */

	TGAImage image(width, height, TGAImage::RGB);

	for (int i = 0; i < model->num_of_faces(); i++) {
		std::vector<int> face = model->face(i); //retrieve each face from container of faces

		for (int j = 0; j < 3; j++) {
			Vector3f v0 = model->vertex(face[j]); //note that face 1/2/3 refers to index of each vertex
			Vector3f v1 = model->vertex(face[(j+1)%3]);
			/* (j+1) % 3 allows a triangle to form between 1->2, 2->3, 3->1 in above example */
			
			int x0 = (v0.x+1) * width/2;
			int x1 = (v1.x+1) * height/2;
			int y0 = (v0.y+1) * width/2;
			int y1 = (v1.y+1) * height/2;

			line(x0, y0, x1, y1, image, white);
		}
	}

	image.flip_vertically(); // puts the origin at the left bottom corner of the image
	image.write_tga_file("output.tga");
	return 0;
}

