As per the CS50x assignment, the only file that I created and wrote was helpers.c which is the code that creates the filters.
Everything else (helpers.h, bmp.h, filter.c, Makefile) was made by the cs50 staff. 

To compile, type in "make filter" in the terminal
To execute, type in ./filter -e/b/g/r images\(inputname).bmp (outputname).bmp

The -e/b/g/r just means the filter to choose, -e is for edge, -b is for blur, -g is for grayscale, and -r is for reverse/flip

The images\(inputname) is the path to the image you want to convert (must be 24 bit uncompressed bmp)
The (outputname).bmp is the path to the output image (which will be the result of the program)