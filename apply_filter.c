int filter[7][7] = { { 1, 1, 1, 1, 1, 1, 1 }, 
                     { 1, 1, 1, 1, 1, 1, 1 }, 
                     { 1, 1, 1, 1, 1, 1, 1 }, 
                     { 1, 1, 1, 1, 1, 1, 1 }, 
                     { 1, 1, 1, 1, 1, 1, 1 }, 
                     { 1, 1, 1, 1, 1, 1, 1 }, 
                     { 1, 1, 1, 1, 1, 1, 1 } }; 

#pragma pack(pop)

void applyfilter(int **arr,int height,int width, int padding)
{
  int temp;
  int totalcount;
  for(int i=0; i<height; i++)
  {
    for(int j=0; j<width*3; j+=3)
    {
      totalcount=49;
      for(int k=-3; k<=3; k++)
      {
        for(int l=-3;l<=3; l++)
        {
          if( ((i+k) < 0) || ((j+l) < 0) || ((i+k) >= height) || ((j+l) >= 3*width+padding) )
          {  
            temp=0;
            totalcount--;
          }
          else
          {
            printf("\nReached here with arr = %d, filter= %d", arr[i+k][j+l], filter[k+3][l+3]);
            temp=arr[i+k][j+l]*filter[k+3][l+3];
          } 
          arr[i][j] = arr[i][j] +  temp;
          printf("\ni=%d j=%d k=%d l=%d, temp=%d", i,j,k,l, temp);
        } 
      } 
      arr[i][j] =(int) arr[i][j]/totalcount;
    } 
  } 
} 


