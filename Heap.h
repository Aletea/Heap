#ifndef HEAP_H
#define HEAP_H
#include <iostream>
#include "Node.h"

using namespace std;

class Heap {
 public:
  Heap();
  ~Heap();
  Node** getArray();
  Node* getHead();
  void insertNode(Node* &newNode);
  Node* removeMax();

 private:
  Node* head;
  Node** array;
  int finalIndex;

};
#endif
