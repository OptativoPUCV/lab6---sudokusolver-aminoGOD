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

int is_valid(Node* n) {
    int seen[10]; 

   for (int i = 0; i < 9; i++) {
        for (int k = 0; k < 10; k++) seen[k] = 0; 
        for (int j = 0; j < 9; j++) {
            int num = n->sudo[i][j];
            if (num != 0) {
                if (seen[num]) return 0; 
                seen[num] = 1; 
            }
        }
   }

   for (int j = 0; j < 9; j++) {
        for (int k = 0; k < 10; k++) seen[k] = 0;
        for (int i = 0; i < 9; i++) {
            int num = n->sudo[i][j];
            if (num != 0) {
                if (seen[num]) return 0; 
                seen[num] = 1; 
            }
        }
   }

   for (int k = 0; k < 9; k++) {
        for (int p = 0; p < 10; p++) seen[p] = 0;
        for (int p = 0; p < 9; p++) {
            int i = 3 * (k / 3) + (p / 3);
            int j = 3 * (k % 3) + (p % 3);
            int num = n->sudo[i][j];
            if (num != 0) {
                if (seen[num]) return 0;
                seen[num] = 1; 
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
   for(int i = 0; i < 9; i++){
      for(int j = 0; j < 9; j++){
         if(n->sudo[i][j] == 0) return 0;
      }
   }
   return is_valid(n);
}

Node* DFS(Node* initial, int* cont) {
    (*cont)++;

    if (is_final(initial)) {
        return copy(initial);  
    }

    List* adj_nodes = get_adj_nodes(initial);
    Node* result = NULL;

    if (is_empty(adj_nodes)) {
        clean(adj_nodes);  
        return NULL;
    }

    for (void* node = first(adj_nodes); node != NULL; node = next(adj_nodes)) {
        result = DFS((Node*)node, cont);

        if (result != NULL) {
            break;
        }
    }

  
    while (!is_empty(adj_nodes)) {
        Node* to_free = (Node*)front(adj_nodes);
        free(to_free);  
        popFront(adj_nodes);  
    }
    clean(adj_nodes);  

    return result;  
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