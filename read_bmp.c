
int read_bmp(char* input, char *output) {

    //variable dec:
    FILE *fp,*out;
    bitmap_header* hp;
    int n;
    char *data;
    int linewidth;
    int padding=0;
    int **arr;

    //Open input file:
    fp = fopen(input, "r");
    if(fp==NULL){
        //cleanup
    }


    //Read the input file headers:
    hp=(bitmap_header*)malloc(sizeof(bitmap_header));
    if(hp==NULL)
        return 3;

    n=fread(hp, sizeof(bitmap_header), 1, fp);
    if(n<1){
        //cleanup
    }
    printf("\n The width  is %d", hp->bitmapsize);
    printf("\n The height  is %d", hp->bitmapsize);
    printf("\n The bitsperpixel is %d", hp->bitsperpixel);
    printf("\n The compression is %d", hp->compression);
    printf("\n The horizontal res  is %d", hp->horizontalres);
    printf("\n The vertical res  is %d", hp->verticalres);
    printf("\n The numcolors  is %d", hp->numcolors);
    printf("\n The offset size is %d", hp->fileheader.dataoffset);

    // Setting up parameters and array
    padding = (4 - hp->width%4)%4;
    linewidth= 3*hp->width + padding;
    arr= (int**) malloc(sizeof(int*) * hp->height );

    // Print out padding
    printf("\nThe padding is %d", padding);

    for(int i=0; i<hp->height;i++)
    {
      arr[i] = (int*) malloc(sizeof(int) * linewidth);
    } 



    //Read the data of the image:
    data = (unsigned char*)malloc(sizeof(unsigned char)*linewidth);
    if(data==NULL){
        //cleanup
    }

    fseek(fp,sizeof(unsigned char)*hp->fileheader.dataoffset,SEEK_SET);
    for(int i=0; i<hp->height; i++)
    {
      n=fread(data,sizeof(unsigned char),linewidth, fp);
      for(int j=0; j<hp->width*3; j+=3)
      {
        arr[i][j+2] = (unsigned char)data[j+0];
        arr[i][j+1] = (unsigned char)data[j+1];
        arr[i][j+0] = (unsigned char)data[j+2];
      } 
      
    } 
    arr = applyfilter(arr, hp->height, hp->width, padding);

    //Open output file:
    out = fopen(output, "w");
    
    n=fwrite(hp,sizeof(char),sizeof(bitmap_header),out);
    
    fseek(out,sizeof(char)*hp->fileheader.dataoffset,SEEK_SET);
    
    for(int i=0; i<hp->height; i++)
    {
      for(int j=0; j<hp->width*3; j+=3)
      {
        //Swapping BGR to RGB values
         data[j+0] = (char)arr[i][j+2];
         data[j+1] = (char)arr[i][j+1];
         data[j+2] = (char)arr[i][j+0];
      } 
      n=fwrite(data,sizeof(char),linewidth,out);
      
    }

    // Wrapping up
    fclose(fp);
    fclose(out);
    free(hp);
    free(data);
    return 0;
}
