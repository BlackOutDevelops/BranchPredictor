// Joshua Frazer jo227789
// Simulator Cache Project, Spring 2020
// Using Atom & Linux Bash Shell on Windows 10.
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

int m,
    n,
    right = 0,
    wrong = 0;

int main(int argc, char **argv) {
  int i,
      sizeOfTable,
      ghb = 0,
      mIndex,
      nExt,
      index,
      prediction;
  long int pc;
  int *mTable;
  double missPrediction = 0;
  char buffer[900],
       outcome;

  FILE *inp = fopen(argv[3], "r");

  m = atoi(argv[1]);
  n = atoi(argv[2]);

  sizeOfTable = pow(2, m);



  mTable = (int *)calloc(sizeOfTable, sizeof(int *));
  for (i = 0; i < sizeOfTable; i++)
  {
      mTable[i] = 2;
  }

  // Personal counter
  i = 1;

  // printArray();
  while(!feof(inp))
  {
    fscanf(inp, "%s", buffer);
    if (strlen(buffer) < 2)
      break;
    pc = strtol(buffer, NULL, 16);
    memset(buffer, 0, sizeof(buffer));
    fscanf(inp, "%s", &outcome);

    pc /= 4;
    mIndex = pc % (long int)(pow(2, m));
    nExt = ghb << (m-n);
    index = mIndex ^ nExt;

    if (index > pow(2, m))
      printf("EXCEEDS WITH INDEX: %d\nWrong Prediction: %d Right Prediction: %d Miss Prediction: %.2lf %d\n", index, wrong, right, missPrediction, wrong + right);

    prediction = mTable[index];

    if (outcome == 't' && prediction >= 2)
    {
      if (prediction == 2)
        mTable[index] = 3;

      right++;
    }
    else if (outcome == 't' && prediction < 2)
    {
      mTable[index]++;
      wrong++;
    }
    else if (outcome == 'n' && prediction <= 1)
    {
      if (prediction == 1)
        mTable[index] = 0;

      right++;
    }
    else if (outcome == 'n' && prediction > 1)
    {
      mTable[index]--;
      wrong++;
    }

    if (outcome == 't')
      ghb = (ghb >> 1) + pow(2, n-1);
    else
      ghb = ghb >> 1;
  }
  // for (i = 0; i < sizeOfTable; i++)
  // {
  //   printf("%d: %d\n", i, mTable[i]);
  // }
  missPrediction = 100*(double)wrong/(wrong + right);
  printf("%d %d %.2lf\n", m, n, missPrediction);
  fclose(inp);

  return 0;
}
