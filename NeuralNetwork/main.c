#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <err.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Maths.h"
#include "NeuralNetwork.h"
#include "TrainAndShow.h"
#include "GuessFunction.h"

//nodes + num of examples
#define numInputs (28*28)
#define numHiddenNodes 81
#define numOutputs 10
#define numTrainingSets 7


//Prototype of the final function for the Neural Network (get images, guess and write in a text doc)
void mainNN (int train, int verbose, int show, int load, int all, SDL_Surface** images_list, int *sudoNumList)
{
  char* sets[7] = {"00","01","02","03","04","05","06"};
  int order[7] = {0,1,2,3,4,5,6};
    load = load;
    if (show)
    {
        if (train)
            errx(0, "NeuralNetwork: can't train and show result");
        else
            show = 1;
    }
    else if (train || show)
    {
        TrainAndShow(train, verbose, show, 1, sets[0]);

        for(int j = 0; j < 5000; j++)
        {
            printf("\n=====%i ITERATION=====\n",j);

            TrainAndShow(train, verbose, show, 1, sets[order[0]]);

	}
    }
    //condition if we want to do all the way
    else if (all)
    {
        double *res = calloc(1,sizeof(double));
        for (size_t i = 0; i < 81; i++)
        {
            Guess(images_list[i],res);
            *res = round(*res);
            sudoNumList[i] = *res;
        }
        free(res);

    }
}


/*int main (int argc, char** argv)
{
  if(argc < 2)
  {
      printf("-train : train the Neural Network \n");
      printf("-verbose : activate verbose \n");
      errx(0, "\n");
  }

  int train = 0;
  int verbose = 0;
  int show = 0;
  int load = 0;

  for(int i = 0; i < argc; i++)
  {
      if(strcmp(argv[i],"-train") == 0)
          train=1;
      if(strcmp(argv[i],"-verbose") == 0)
          verbose = 1;
      if(strcmp(argv[i],"-show") == 0)
      {
          if (train)
              errx(0, "can't train and show result");
          else
              show = 1;
      }
      if(strcmp(argv[i],"-load") == 0)
          load = 1;
  }

  if(!train && !show)
      errx(0,"must train or show, please choose an option");

  if (train || show)
      TrainAndShow(train, verbose, show, load);


  return 1;
}*/

