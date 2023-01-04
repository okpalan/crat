# Compling and running the raytracer with vector.o
# This is a simple example of how to compile and run the raytracer
# with the vector.o file.  The vector.o file is a library of
# vector functions that are used by the raytracer.  The vector.o
# file is compiled and linked with the raytracer to create the
# executable raytracer.  The raytracer executable is then run
# with the input file scene1.txt.  The output is written to the
# file scene1.ppm.  The output file scene1.ppm is a PPM image
# file that can be viewed with the xv image viewer.
#
# To compile and run the raytracer with vector.o:
#   make
#   ./raytracer scene1.json scene1.ppm
#
# To compile and run the raytracer with vector.o and the
# debug flag:
#   make
#   ./raytracer -d scene1.txt scene1.ppm
