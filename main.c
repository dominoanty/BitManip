#include <stdio.h>
#include <stdlib.h>
#include "bmp_headers.h"

#include "apply_filter.c"
#include "read_bmp.c"



void main(int argc, char *argv[])
{
  read_bmp(argv[1], "output.bmp");

} 
