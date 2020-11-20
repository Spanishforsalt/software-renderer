# software-renderer

A personal project following  Dmitry V. Sokolov's tinyrenderer lessons for educational purposes. The renderer mimics the structure of OpenGL, with the goal being to take a test file with a polygonal wire + pictures with textures as input, and output a rendered model.

The only external dependency used is a class to read TGA (image format) files. The only functionality available with this class, in addition to loading and saving images, is the capability to set the color of one pixel.

## Update History

v0.01: Initial commit up to end of lesson 1, program draws line to screen utilising bresnehem's line drawing algorithm.  
Current example output:  
![output.tga](https://user-images.githubusercontent.com/72558704/99830128-2bae7480-2b55-11eb-86d2-0427d16dc37a.png)

