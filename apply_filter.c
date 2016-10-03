#define FILTER_SIZE 7

// Kernel Matrix
int filter[7][7] = { { 1, 1, 1, 1, 1, 1, 1 }, 
                     { 1, 1, 1, 1, 1, 1, 1 }, 
                     { 1, 1, 1, 1, 1, 1, 1 }, 
                     { 1, 1, 1, 1, 1, 1, 1 }, 
                     { 1, 1, 1, 1, 1, 1, 1 }, 
                     { 1, 1, 1, 1, 1, 1, 1 }, 
                     { 1, 1, 1, 1, 1, 1, 1 } }; 

#pragma pack(pop)

// Function takes in the original 2D image representation and returns 
// the blurred image
int **applyfilter(int **arr,int height,int width, int padding)
{
  int temp;
  int totalcount;
  
  // Allocate the new array for copy
  int **arr2;
  arr2= (int**) malloc(sizeof(int*) * height );
  for(int i=0; i<height;i++)
  {
    arr2[i] = (int*) malloc(sizeof(int) * (3*width+padding));
  }
  
  //Sliding window algorithm
  for(int i=0; i<height; i++)
  {
    for(int j=0; j<width*3; j+=1)
    {
      totalcount=49;
      for(int k=-(FILTER_SIZE/2); k<=(FILTER_SIZE/2); k++)
      {
        for(int l=-(FILTER_SIZE/2);l<=(FILTER_SIZE/2); l++)
        {
          //Make sure the filter doesn't apply out of the window size
          if( ((i+k*3) < 0) || ((j+l*3) < 0) || 
              ((i+k*3) >= height) || ((j+l*3) >= 3*width+padding) || 
              (filter[k+(FILTER_SIZE/2)][l+(FILTER_SIZE/2)] == 0))
          {  
            temp=0;
            totalcount--;
          }
          else
          {
            temp=arr[i+k*3][j+l*3]*filter[k+3][l+3];
          } 
          arr2[i][j] = arr2[i][j]+ temp;
        } 
      } 
      if(totalcount == 0)
        arr2[i][j] = 0;
      else
        arr2[i][j] =(int) arr2[i][j]/totalcount;
    } 
  }
  return arr2;
} 


