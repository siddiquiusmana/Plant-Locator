#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct pos{
  int x;
  int y;
} pos;

pos origin;

typedef struct plants{
  pos location;
  int dist;
} plants;

typedef struct data{
  int numplants;
  int numQueries;
  int threshold;
  plants* plantss;
  pos* searchQueries;
} data;

data readData();
void distance(plants* plantss, int numplants);
void insertionSort(plants* plantss, int l, int length);
void printplantss(plants* plantss, int numplants, int r, FILE* ofp);
int compareTo(pos* ptrPtr1, pos* ptrPtr2);
void merge(plants* plantss, int l, int m, int r);
void mergeSort(plants* plantss, int l, int r, int threshold);
void sort(plants* plantss, int length, int threshold);
void querySearch(plants* plantss, pos* searchQueries, int numplants, int numQueries, FILE *ofp);
void binarySearch(plants* plantss, int low, int high, int x, int y, int dist, FILE *ofp);

int main()
{
  data data = readData();

  plants* plantss = data.plantss;
  pos* searchQueries = data.searchQueries;

  //Input Verification
  /*
  printf("%d %d %d %d %d\n", origin.x, origin.y, data.numplants, data.numQueries, data.threshold);
  for(int i=0; i<data.numplants; i++)
  {
    printf("%d %d \n", plantss[i].location.x, plantss[i].location.y);
  }
  for(int i=0; i<data.numQueries; i++)
  {
    printf("%d %d\n", searchQueries[i].x, searchQueries[i].y);
  }
  */

  distance(plantss, data.numplants);

  FILE *ofp = fopen("out.txt", "w");
  sort(plantss, data.numplants, data.threshold);
  printplantss(plantss, 0, data.numplants-1, ofp);

  querySearch(plantss, searchQueries, data.numplants, data.numQueries, ofp);
}

data readData()
{
  data data;
  FILE *ifp = fopen("in.txt", "r");
  fscanf(ifp, "%d %d %d %d %d", &origin.x, &origin.y,&data.numplants, &data.numQueries, &data.threshold);

  data.plantss = (plants*) malloc(sizeof(plants)*data.numplants);

  for(int i=0; i<data.numplants; i++)
  {
    fscanf(ifp, "%d %d", &data.plantss[i].location.x, &data.plantss[i].location.y);
  }

  data.searchQueries = (pos*) malloc(sizeof(pos)*data.numQueries);

  for(int i=0; i<data.numQueries; i++)
  {
    fscanf(ifp, "%d %d", &data.searchQueries[i].x, &data.searchQueries[i].y);
  }

  fclose(ifp);

  return data;
}

void distance(plants* plantss, int numplants)
{
  for(int i=0; i<numplants; i++)
  {
    plantss[i].dist = sqrt(pow((origin.x - plantss[i].location.x), 2) + pow((origin.y - plantss[i].location.y), 2));
  }
  //Function verification
  /*
  for(int i=0; i<numplants; i++)
  {
    printf("%d %d %d\n", plantss[i].location.x, plantss[i].location.y, plantss[i].dist);
  }
  */
}

void insertionSort(plants* plantss, int l, int r)
{
  int length = r-l;
  int i =0, j;
  plants item;
  for (i = l+1; i < l+length+1; i++)
  {
    item = plantss[i];

    for(j=i-1; j>=l; j--)
    {
      if(compareTo(&plantss[j].location, &item.location)==1)
        plantss[j+1] = plantss[j];
      else
        break;
    }
    plantss[j+1] = item;
  }
}

void printplantss(plants* plantss, int l, int r, FILE* ofp)
{
  for(int i=l; i<=r; i++)
  {
    printf("%d %d\n", plantss[i].location.x, plantss[i].location.y);
    fprintf(ofp, "%d %d\n", plantss[i].location.x, plantss[i].location.y);
  }
}

int compareTo(pos* ptrPtr1, pos* ptrPtr2)
{
  int dist1 = sqrt(pow((origin.x - ptrPtr1->x), 2) + pow((origin.y - ptrPtr1->y), 2));
  int dist2 = sqrt(pow((origin.x - ptrPtr2->x), 2) + pow((origin.y - ptrPtr2->y), 2));

  if(dist1 < dist2)
  {
    return -1;
  }
  else if(dist1 > dist2)
  {
    return 1;
  }
  else if(ptrPtr1->x == ptrPtr2->x && ptrPtr1->y == ptrPtr2->y)
  {
    return 0;
  }
  else
  {
    if(ptrPtr1->x < ptrPtr2->x)
    {
      return -1;
    }
    else if(ptrPtr1->x > ptrPtr2->x)
    {
      return 1;
    }
    else
    {
      if(ptrPtr1->y < ptrPtr2->y)
      {
        return -1;
      }
      else
        return 1;
    }
  }
}

void merge(plants* plantss, int l, int m, int r)
{
  int i, j, k;
  int n1 = m - l + 1;
  int n2 =  r - m;

  plants *L = (plants*) malloc(n1*sizeof(plants));
  plants *R = (plants*) malloc(n2*sizeof(plants));

  for (i = 0; i < n1; i++)
    L[i] = plantss[l + i];
  for (j = 0; j < n2; j++)
    R[j] = plantss[m + 1+ j];

  i = 0;
  j = 0;
  k = l;
  while (i < n1 && j < n2)
  {
    if (compareTo(&L[i].location, &R[j].location)==-1)
    {
      plantss[k] = L[i];
      i++;
    }
    else
    {
      plantss[k] = R[j];
      j++;
    }
    k++;
  }

  while (i < n1)
  {
    plantss[k] = L[i];
    i++;
    k++;
  }

  while (j < n2)
  {
    plantss[k] = R[j];
    j++;
    k++;
  }
  free(L);
  free(R);
}

void mergeSort(plants* plantss, int l, int r, int threshold)
{
  int length = r-l;
  if (length>threshold)
  {
    int m = (l+r)/2;

    mergeSort(plantss, l, m, threshold);
    mergeSort(plantss, m+1, r, threshold);
    merge(plantss, l, m, r);
  }
  else
  {
    insertionSort(plantss, l, r);
  }
}

void sort(plants* plantss, int length, int threshold)
{
  if(length > threshold)
  {
    mergeSort(plantss, 0, length-1, threshold);
  }
  else
  {
    insertionSort(plantss, 0, length);
  }
}

void querySearch(plants* plantss, pos* searchQueries, int numplants, int numQueries, FILE *ofp)
{
  for(int i = 0; i<numQueries; i++)
  {
    int dist = sqrt(pow((origin.x - searchQueries[i].x), 2) + pow((origin.y - searchQueries[i].y), 2));

    binarySearch(plantss, 0, numplants-1, searchQueries[i].x, searchQueries[i].y, dist, ofp);
  }
}

void binarySearch(plants* plantss, int low, int high, int x, int y, int dist, FILE *ofp)
{
  int mid;
  while(low<=high)
  {
    mid = (low+high)/2;

    if(dist == plantss[mid].dist)
    {
      if(plantss[mid].location.x == x && plantss[mid].location.y == y)
      {
        fprintf(ofp, "%d %d found at rank %d\n", x, y, mid+1);
        printf("%d %d found at rank %d\n", x, y, mid+1);
        return;
      }
      else
      {
        while(dist == plantss[mid].dist && x < plantss[mid].location.x)
        {

          if(plantss[--mid].location.x == x && plantss[mid].location.y == y)
          {
            fprintf(ofp, "%d %d found at rank %d\n", x, y, mid+1);
            printf("%d %d found at rank %d\n", x, y, mid+1);
            return;
          }
        }
        while(dist == plantss[mid].dist && x > plantss[mid].location.x)
        {
          if(plantss[++mid].location.x == x && plantss[mid].location.y == y)
          {
            fprintf(ofp, "%d %d found at rank %d\n", x, y, mid+1);
            printf("%d %d found at rank %d\n", x, y, mid+1);
            return;
          }
        }
        while(dist == plantss[mid].dist && x == plantss[mid].location.x)
        {
          while(dist == plantss[mid].dist && x == plantss[mid].location.x && y < plantss[mid].location.y)
          {
            if(plantss[--mid].location.x == x && plantss[mid].location.y == y)
            {
              fprintf(ofp, "%d %d found at rank %d\n", x, y, mid+1);
              printf("%d %d found at rank %d\n", x, y, mid+1);
              return;
            }
          }
          while(dist == plantss[mid].dist && x == plantss[mid].location.x && y > plantss[mid].location.y)
          {
            if(plantss[++mid].location.x == x && plantss[mid].location.y == y)
            {
              fprintf(ofp, "%d %d found at rank %d\n", x, y, mid+1);
              printf("%d %d found at rank %d\n", x, y, mid+1);
              return;
            }
          }
          fprintf(ofp, "%d %d not found\n", x, y);
          printf("%d %d not found\n", x, y);
          return;
        }
      }
    }
    else if(dist<plantss[mid].dist)
    {
      high = mid - 1;
    }
    else
    {
      low = mid + 1;
    }
  }
  fprintf(ofp, "%d %d not found\n", x, y);
  printf("%d %d not found\n", x, y);
}
