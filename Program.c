/*..

Miar Taweel

*/


#include <stdio.h>
#include <stdlib.h>
#include <limits.h> // Required for INT_MAX

//The prototypes for all functions

typedef struct node* arrow;

int findIndex(char [][100], int , char [] );

int* di( int [100][100], int  , int ,int,char[][100] );

int* bfs(int [100][100], int , int , int, char [] [100]);

int whereToGoToNext(int [] ,int [],int );

int main(){

FILE *f,*p; // declaring the files pointers


//initialising values
int x=10,i=0,j=0,o=0;
int count = 0, size = 0;
char tryout[100][100];

char cities[100][100];//declaring an array to store all of the cities
char cityOne[100];//declaring an array to store the first city
char cityTwo[100];//declaring an array to store the second city
char ciOne[100];
char ciTwo[100];

//Initialising the files pointers
p = fopen("shortest_distance.txt", "w");
f = fopen("cities.txt", "r");

//checking if the file exists
if (f == NULL) {

        printf("Failed to open the input file.\n");
        return 1;

}

//Calculating the size of the file
while (fgets(tryout[size], 100, f) != NULL && size < 100) {
        size++;
}

fclose(f);


//Declaration of arrays of strings for the given information
char a[size][1000];

//declaration if the graph
int graph[100][100];

//declaring some arrays as empty
a[0][0]=NULL;
cityOne[0]=NULL;
int* result1;
int* result2;
int b=0;

//A loop for printing the menu and executing the operations
while(1){
printf("\n\nPlease Choose one of the following:\n1.Load Cities \n2.Enter source\n3.Enter destination\n4.Exit\n");

scanf("%d",&x);

//if conditions for each case(operation) of the menu
if (x == 1) {
    i = 0;
    char city1[100];
    char city2[100];
    int d;
    char dis[100];

    f = fopen("cities.txt", "r");

    //checking if the file exist
    if (a[0][0] != NULL)
        printf("The file has already been read");

    else { // Reading the values from the file, placing them in an array then the graph, and printing them on the screen

        while (fgets(a[i],size,f)!=NULL&&(i<size)) {// A loop to read the file
            sscanf(a[i], "%s\t%s\t%d%s", &city1,&city2,&d,&dis);

            if(j==0){
                strcpy(cities[j], city1);
                j++;
            } else if (strcmp(cities[j - 1], city1) != 0) {
                strcpy(cities[j], city1);
                j++;
            }
            i++;
        }

        for (int l = 0; l < size; l++) {// A loop to divide the string into multiple variables and place them into the graph
            sscanf(a[l], "%s\t%s\t%d%s", &city1, &city2, &d, &dis);
            graph[findIndex(cities, j, city1)][findIndex(cities, j, city2)] = d;
        }

        //A loop to print the graph
        for (int k = 0; k < j; k++) {
            printf("\n\n%d.%s is connected to:\n", k + 1, cities[k]);
            for (int l = 0; l < j; l++) {

                if (graph[k][l] != 0)
                    printf("\n        %s by distance %dkm", cities[l], graph[k][l]);
            }
        }
    }
}


// Reading the first city case
else if (x==2){

     if (a[0][0]!=NULL){//Checking if the file has been read

            int cityTest[100];
            printf("Enter the source city:");
            scanf("%s",&cityTest);
            int e=1;
            for(int k=0; k<j;k++){//A loop to check if the entered city exists
            if (strcmp(cities[k],cityTest)==0)
                    e=0;
                }

            if(e==1){
            printf("city does not exist\n");}
            else {// if exists the city is stored

                strcpy(cityOne,cityTest);
                printf("\nSource entered = %s \n",cityOne);
            }

     }else
     printf("Please load the file first");

// Reading the second city case
}else if(x==3){

    if (a[0][0]!=NULL){//Checking if the file has been read
        if (cityOne[0]!=NULL){//Checking if the source city has been entered

            int cityTest[100];
            printf("Enter the source city:");
            scanf("%s",&cityTest);
            int e=1;

            //A loop to check if the entered city exists
            for(int k=0; k<j;k++){
              if (strcmp(cities[k],cityTest)==0)
                e=0;
            }

            if(e==1){
            printf("city does not exist\n");}
            else {// if exists both the dijkstra and BFS algorithms are applied
                 b=1;
                strcpy(cityTwo,cityTest);
                strcpy(ciTwo,cityTest);
                strcpy(ciOne,cityOne);
                printf("\nSource entered = %s \n",cityTwo);
                printf("\nBFS from %s city to %s city : \n", cityOne,cityTwo);

                //A call of the BFS algorithm function and saving the answer in result1
                result1 =bfs(graph,j,findIndex(cities,j,cityOne),findIndex(cities,j,cityTwo),cities);
                printf("\nDijkstra from %s city to %s city : \n", cityOne,cityTwo);
                //A call of the dijkstra algorithm function and saving the answer in result2
                result2= di( graph,j,findIndex(cities,j,cityOne) ,findIndex(cities,j,cityTwo),cities);



            }
         }

     else
     printf("Please Enter a Source first");
    }else
     printf("Please load the file first");

}
//Exit and printing case
else if(x==4){// breaks the infinite loop to stop the program and prints the content from the previous step by closing the file

    if (a[0][0]!=NULL&&b!=0){//Checking if a path had been calculated



                //Moving info to the file (BFS)
                int cost= result1[0];
                int D= result1[1];
                fprintf(p,"\n\nFrom %s city to %s city:\n",ciOne,ciTwo);
                fprintf(p,"\n-BFS Algorithm \n");
                if (cost!=0){//Checking if a path exists
                    int i=2;

                    fprintf(p,"\nDistance = %dkm(%d edges)\n",cost,D);//printing the distance to the file

                    while (result1[i]==-2){
                        i++;
                    }

                    int n=result1[i];
                    i++;
                    fprintf(p,"Path: %s",cities[n]);
                    while(result1[i]!=-1){//A loop to print the path from result 1 to the file

                        if (result1[i]!=-2){
                            fprintf(p," -(%dkm)->%s ",graph[n][result1[i]],cities[result1[i]]);
                            n=result1[i];
                        }
                        i++;

                    }

                }
                else fprintf(p,"\nPATH DOESNT EXIST\n");

                cost= result2[0];

                fprintf(p,"\n\n-Dijkstra Algorithm\n");
                if (cost!=0){


                     fprintf(p,"\nDistance = %dkm\n",cost);//printing the distance
                     int i=1;

                     while (result2[i]==-2){
                        i++;
                    }

                     int n=result2[i];
                     i++;
                     fprintf(p,"Path: %s",cities[n]);
                     while(result2[i]!=-1){//A loop to print the path from result 2 to the file

                        if (result2[i]!=-2){
                           fprintf(p," -(%dkm)->%s ",graph[n][result2[i]],cities[result2[i]]);
                           n=result2[i];
                        }
                        i++;

                    }
                   fprintf(p,"\n");
                }else fprintf(p,"\nPATH DOESNT EXIST\n");





     printf("\nThe distance and path has been printed to the file succesfully\n");
    }else printf("\nNo paths have been tracked\n");

     break;
}

//Invalid input case
else printf("invalid input please enter again");

}
//Closing the input and output files
fclose(p);
fclose(f);

  return 0;

}

int findIndex(char a[][100], int size, char component[]) {//A loop that finds the index of a city in the graph
    for (int i=0; i<size;i++) {
        if (strcmp(a[i], component)==0) {
            return i;
        }
    }
    return -1;
}

int* di( int graph[100][100], int size , int startI,int desI, char cities[][100]){// A function that applies the Dijkstra algorithm
int discovered[size];//An array to mark the passed cities
int values[size];//An array to mark the total distance to all cities
int father[size];//An array to mark the predecessors of different cities

for(int i =0; i<size ;i++){//Initialising all arrays
   values[i]=INT_MAX;
   father[i]=-1;
   discovered[i]=0;

}

values[startI]=0;//initialising the starting cities' value

for(int i=0;i<size-1;i++){

int node = whereToGoToNext(values,discovered,size);//finding the next node
discovered[node]=1;

    for(int j=0;j<size ;j++){// a loop to traverse all the adjacents of the current city nodes

        // a condition to update the distance if a shorter path distance is found
        if(graph[node][j]!=0 && discovered[j]!=1 && values[node]!=INT_MAX && (values[node] + graph[node][j] < values[j])){

          father[j]=node;//updating its predecessor
          values[j]=values[node]+graph[node][j];//updating its distance

        }
    }
}

 int n = desI;
 int cityd=n;
 //An array that holds the distance and path to return to the main
 int* path = malloc((size+2)* sizeof(int));
 int p=size;

 for(int i =0; i<size+2 ;i++){//initialising the array
           path[i]=-2;
        }

 if(values[desI]!=INT_MAX){//checking if the path exist
   if(startI==desI)
        printf("\nYou are already in the required destination\n");
    printf("Path :%s ", cities[n]);
    path[p]=n;
    p--;

    while (father[n] != -1) {//A loop to print the path

       n = father[n];
       path[p]=n;// filling the result array
       p--;
       printf(" <-(%dkm)- %s ", graph[n][cityd],cities[n]);
       cityd=n;

    }

     path[size+1]=-1;
     path[0]=values[desI];
     printf("\nDistance= %dkm\n", values[desI]);

}else {printf("PATH DOESNT EXIST");//checking if the path exist
      path[0]=0;}

  printf("\n");
  return path;
}

int whereToGoToNext(int values[] ,int discovered[],int size){//A function that returns the next node to move on to in the Dijkstra algorithm

int x=INT_MAX;
int indexV;
for(int i=0;i<size;i++){

    if ((values[i]<=x) && (discovered[i]==0)){
        x=values[i];
        indexV=i;
    }


}
return indexV;

}

int* bfs( int graph[100][100], int size , int startI,int desI,char cities[][100]){// A function that applies the BFS algorithm

int discovered[size];//An array to mark the passed cities
int values[size];//An array to mark the total distance to all cities
int father[size];//An array to mark the predecessors of different cities
int Q[100];//A queue that holds the nodes to be accessed in order
int front =0;
int rear=0;

for(int i =0; i<size ;i++){//Initialising all arrays
   values[i]=INT_MAX;
   father[i]=-1;
   discovered[i]=0;

}

Q[rear++]=startI;//enqueue the starting city
values[startI]=0;//initialising the starting cities' value

while (front<rear){//A loop to access a

int node = Q[front++];//dequeue to visit all of its connected cities
discovered[node]=1;

    for(int j=0;j<size ;j++){// a loop to traverse all the adjacents of the current city nodes

        // a condition to update the distance if a shorter path distance is found
        if(graph[node][j]!=0 && discovered[j]!=1 && values[node]!=INT_MAX && (values[node] + 1 < values[j])){

           father[j]=node;//updating its predecessor
           Q[rear++]=j;//Enqueue the node to visit it
           values[j]=values[node]+1;//updating its distance

        }

      }

    }

     int n = desI;
     int cost =0;
     int citycost=n;
      //An array that holds the distance and path to return to the main
     int* path = malloc((size+3)* sizeof(int));
     int p=size+1;
     for(int i =0; i<size+3 ;i++){//initialising the array

           path[i]=-2;

        }

    if(values[desI]!=INT_MAX ){//checking if the path exists

         if(startI==desI)
            printf("\nYou are already in the required destination\n");
         printf("Path :%s ", cities[n]);
         path[p]=n;
         p--;

         while (father[n] != -1) {//A loop to print the path

               n = father[n];
               path[p]=n;// filling the result array
               p--;
               cost=cost+graph[n][citycost];

               printf(" <-(%dkm)- %s ",graph[n][citycost],cities[n]);
               citycost=n;
            }

        path[1]=values[desI];
        path[0]=cost;
        path[size+2]=-1;
        printf("\nDistance= %dkm ( %d edges) \n ", cost,values[desI]);

    }else {printf("PATH DOESNT EXIST");
           path[0]=0;}

       printf("\n");
    return path;
}




