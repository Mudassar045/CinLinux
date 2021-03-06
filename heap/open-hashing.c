#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define SIZE 20

struct DataNode {
   int data;
   int key;
};

struct DataNode* hashArray[SIZE];
struct DataNode* myHashTable;
struct DataNode* item;

int hashCode(int key) {
   return key % SIZE;
}

struct DataNode *search(int key) {
   //get the hash
   int hashIndex = hashCode(key);

   //move in array until an empty
   while(hashArray[hashIndex] != NULL) {

      if(hashArray[hashIndex]->key == key)
         return hashArray[hashIndex];

      //go to next cell
      ++hashIndex;

      //wrap around the table
      hashIndex %= SIZE;
   }

   return NULL;
}

void insert(int key,int data) {

  // allocating memory
   struct DataNode *item = (struct DataNode*) malloc(sizeof(struct DataNode));
   item->data = data;
   item->key = key;

   //get the hash
   int hashIndex = hashCode(key);

   //move in array until an empty or deleted cell
   while(hashArray[hashIndex] != NULL && hashArray[hashIndex]->key != -1) {
      //go to next cell
      ++hashIndex;

      //wrap around the table
      hashIndex %= SIZE;
   }

   hashArray[hashIndex] = item;
}

struct DataNode* delete(struct DataNode* item) {
   int key = item->key;

   //get the hash
   int hashIndex = hashCode(key);

   //move in array until an empty
   while(hashArray[hashIndex] != NULL) {

      if(hashArray[hashIndex]->key == key) {
         struct DataNode* temp = hashArray[hashIndex];

         //assign a dummy item at deleted position
         hashArray[hashIndex] = myHashTable;
         return temp;
      }

      //go to next cell
      ++hashIndex;

      //wrap around the table
      hashIndex %= SIZE;
   }

   return NULL;
}

void display() {
   int i = 0;

   for(i = 0; i<SIZE; i++) {

      if(hashArray[i] != NULL)
         printf(" (%d,%d)",hashArray[i]->key,hashArray[i]->data);
      else
         printf("--");
   }

   printf("\n");
}

int main() {

   myHashTable = (struct DataNode*) malloc(sizeof(struct DataNode));
   myHashTable->data = -1;
   myHashTable->key = -1;
   // Inserting data into Linked List
   insert(1, 20);
   insert(2, 70);
   insert(42, 80);
   insert(4, 25);
   insert(12, 44);
   insert(14, 32);
   insert(17, 11);
   insert(13, 78);
   insert(37, 97);
   // displaying data
   display();

   //Searching in linked list
   item = search(37);

   if(item != NULL) {
      printf("Item found: %d\n", item->data);
   } else {
      printf("Item not found\n");
   }
   // deleting an item
   delete(item);
   // searching again to verify data node deleted
   item = search(37);
   if(item != NULL) {
      printf("Item found: %d\n", item->data);
   } else {
      printf("Item not found\n");
   }
}
