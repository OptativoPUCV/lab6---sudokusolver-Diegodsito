#include <stdio.h>
#include <stdlib.h>
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

   for(int i = 0 ; i < 9 ; i++){ //Verificacion filas y columnas
      for(int j = 0 ; j < 9 ; j++){
         
         if(n->sudo[i][j] == 0) continue;
         for(int k = 0 ; k < 9 ; k++){
            if(k == j) continue;
            if(n->sudo[i][k] == n->sudo[i][j]) return 0;
         }
         for(int k = 0 ; k < 9 ; k++){
            if(i == k) continue;
            if(n->sudo[k][j] == n->sudo[i][j]) return 0;
         }
      }
   }

   //Verificacion de submatrices

   for(int k = 0 ; k < 9 ; k++){
      int inicio_fila = 3 * (k/3);
      int inicio_col = 3 * (k%3);

      int nums[10] = {0};

      for(int p = 0 ; p < 9 ; p++){
         int i = inicio_fila + (p / 3);
         int j = inicio_col + (p % 3);
         
         if(n->sudo[i][j] != 0){
            if(nums[ n->sudo[i][j]] == 1) return 0;
         }
      }
   }

    return 1;
}


List* get_adj_nodes(Node* n){
   
   List* list=createList();
   
   for(int num = 1 ;num <= 9; num++){
      Node* nuevoNodo = copy(n);

      int i,j;
      for(i = 0 ; i < 9 ; i++){
         for(j = 0 ; j < 9 ; j++){
            if(nuevoNodo->sudo[i][j] == 0){
               nuevoNodo->sudo[i][j] = num;
               
               if(is_valid(nuevoNodo)){
                  Node* adjNode = copy(nuevoNodo);
                  pushBack(list, adjNode);
               }
            }
            
         }
      }
      free(nuevoNodo);
   }
   return list;
}


int is_final(Node* n){

   for(int i = 0 ; i < 9 ; i++){
      for(int j = 0 ; j < 9 ; j++){
         if(n->sudo[i][j] == 0) return 0;
      }
   }
   
   return 1;
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