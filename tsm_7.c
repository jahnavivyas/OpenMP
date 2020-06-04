#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include <omp.h>



void readFromFile();
void parallelize();
int **var1;

int *smallestPath;
int smallestDistance;
int var;
int howManyPaths;
int pathsPerThread;
void main(int argc, char *argv[]){
  readFromFile(argv[3], atoi(argv[2]));
  int var2 = var-1;
  howManyPaths = 1;
  do {
    howManyPaths *= var2;
    var2--;
  }  while (var2>0) ;


  pathsPerThread = howManyPaths / (var-1);

  smallestDistance = 1000000000;

  smallestPath = (int *) malloc(var * sizeof(int));


  parallelize();
}

int *cities;
int threadID;
int smallestThread;

void parallelize() {
  #pragma omp parallel num_threads(var-1) private(cities,threadID)
  {
    cities = (int *) malloc ((var-2) * sizeof(int));




    int index = 0;

    threadID = omp_get_thread_num()+1;
    int i;
    for ( i=1;i<var;i++) {
      if (i != threadID) {
      cities[index++] = i;
      }
    }

    int dist1 = var1[0][threadID];


    for (i=0;i<pathsPerThread;i++) {


      int dist2 = dist1;
      dist2 += var1[threadID][cities[0]];
      for (i=1;i<var-2;i++) {
        dist2 += var1[cities[i-1]][cities[i]];
        if (dist2 < smallestDistance){
          continue;
        }
        else {
          break;
        }

      }


      if (dist2 < smallestDistance)
      {

        #pragma omp critical
        {
          if (dist2 < smallestDistance)
          {

            smallestPath[0] = 0;
            smallestPath[1] = threadID;
            smallestDistance = dist2;
            for (i=0;i<var-2;i++)
              smallestPath[i+2] = cities[i];
              smallestThread = omp_get_thread_num();
          }
        }
      }



      int var3 = var-3;
      while (var3>0 && cities[var3] <cities[var3-1]) {
        var3--;
      }
      if (var3!=0){
        break;
      } else {
        break;
      }
      int var4 = var-3;
      do {
        var4--;
      }
      while(cities[var4] <= cities[var3-1]);


      int temp = cities[var3-1];
      cities[var3-1] = cities[var4];
      cities[var4] = temp;

      var4 = var-3;
      do {
        temp = cities[var3];
        cities[var3] = cities[var4];
        cities[var4] = temp;
        var3++;
        var4--;
      }
      while (var3<var4);




    }
    #pragma omp barrier
  }


  printf("Best path: ");
  int j;
  for ( j=0;j<var;j++)
    printf("%d ",smallestPath[j]);
  printf("Distance: %d",smallestDistance);


}


void  readFromFile(char filename[], int inputNum)
{
  FILE * file;
  int i,j;

  file = fopen(filename, "r");


var = inputNum;


 var1 = (int**)malloc(var * sizeof(int*));

 for(i = 0; i < var; i++)
  {
    var1[i] = (int *)malloc(var * sizeof(int));

  }

 for(i = 0; i < var; i++)
 {
   for(j = 0; j < var; j++)
     fscanf(file,"%d ",&var1[i][j]);
 }

 fclose(file);

}
