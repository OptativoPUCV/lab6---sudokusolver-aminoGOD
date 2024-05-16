#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"


typedef struct{
   int sudo[9][9];
}Node;

Node* createNode(){
  Node* n=(Node*) malloc(sizeof(Node));
  return n;
}

Node* copy(Node* n){
    Node* new=(Node*) malloc(sizeof(Node));
    *new = *n;
    return new;
}

Node* read_file (char* file_name){
  Node* n = createNode();
  FILE* file = fopen (file_name, "r");
  int i,j;
  for(i=0;i<9;i++){
       for(j=0;j<9;j++){
          if(!fscanf (file, "%d", &n->sudo[i][j]))
            printf("failed to read data!");
       }
  }

  fclose (file);
  return n;
}

void print_node(Node* n){
    int i,j;
    for(i=0;i<9;i++){
       for(j=0;j<9;j++)
          printf("%d ", n->sudo[i][j]);
       printf("\n");
    }
    printf("\n");
}

int is_valid(Node* n){
   int row[10], col[10], box[10];

   for(int i = 0; i < 9; i++){
      memset(row, 0, sizeof(row));
      memset(col, 0, sizeof(col));
      for(int j = 0; j < 9; j++){
         int numRow = n->sudo[i][j];
         int numCol = n->sudo[j][i];

         if(numRow != 0){
            if(row[numRow]) return 0;
            row[numRow] = 1;
         }
         if(numCol != 0){
            if(col[numCol]) return 0;
            col[numCol] = 1;
         }
      }
   }

   for(int block = 0; block < 9; block++){
      int startRow = 3 * (block / 3);
      int startCol = 3 * (block % 3);
      memset(box, 0, sizeof(box));
      for(int i = 0; i < 3; i++){
         for(int j = 0; j < 3; j++){
            int num = n->sudo[startRow + i][startCol + j];
            if(num != 0){
               if(box[num]) return 0;
               box[num] = 1;
            }
         }
      }
   }
   return 1;
}



List* get_adj_nodes(Node* n){
   List* list = createList();
   for(int i = 0; i < 9; i++){
      for(int j = 0; j < 9; j++){
         if(n->sudo[i][j] == 0){
            for(int num = 1; num <= 9; num++){
               n->sudo[i][j] = num;
               if(is_valid(n)){
                  Node* newNode = copy(n);
                  pushBack(list, newNode);
               }
            }
            n->sudo[i][j] = 0;
            return list;
         }
      }
   }
   return list;
}


int is_final(Node* n){
    return 0;
}

Node* DFS(Node* initial, int* cont){
  return NULL;
}



/*
int main( int argc, char *argv[] ){

  Node* initial= read_file("s12a.txt");;

  int cont=0;
  Node* final = DFS(initial, &cont);
  printf("iterations:%d\n",cont);
  print_node(final);

  return 0;
}*/