#ifndef NODE_H
#define NODE_H
#include <iostream>

using namespace std;

struct Node {
  Node* left = NULL;
  Node* right = NULL;
  int number;
};
#endif
