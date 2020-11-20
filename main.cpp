#include "tgaimage.h"

const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red   = TGAColor(255, 0,   0,   255);
const int width  = 100;
const int height = 100;


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
	TGAImage image(width, height, TGAImage::RGB);
	
	for (int i=0; i < 1000000; i++) { //draws lines a million times to test with gprof
		line(13, 20, 80, 40, image, white);
		line(20, 13, 40, 80, image, red); 
		line(80, 40, 13, 20, image, red);
	}
	image.flip_vertically(); // puts the origin at the left bottom corner of the image
	image.write_tga_file("output.tga");
	return 0;
}

