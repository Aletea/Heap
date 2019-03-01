#include <iostream>
#include <cstring>
#include "Node.h"
#include "Heap.h"

using namespace std;

Heap::Heap() {
  head = NULL;
  array = new Node*[200];
  for (int i = 0; i < 100; i++) {
    array[i] = NULL;
  }
  int finalIndex = 0;
}

Heap::~Heap() {
  head = NULL;
  for (int i = 0; i < 100; i++) {
    array[i] = NULL;
  }
  delete array;
}

Node** Heap::getArray() {
  return array;
}

Node* Heap::getHead() {
  return head;
}

void Heap::insertNode(Node* &newNode) {
  //insert node at bottom of tree using array
  //location is one more than the index of the head node. Location will keep track of the slot this node is being put in
  if (head == NULL) {
    head = newNode;
    array[0] = newNode;
    return;
  }
  int location = 1;
  for (int i = 0; i < sizeof(array); i++) {
    //find the first empty slot of the array and set the location to that
    if (array[i] == NULL) {
      location = i+1;
      finalIndex = location;
      break;
    }
  }
  //set that index to the new Node
  array[location-1] = newNode;
  //if new node is now head
  if (location == 1) {
    //set head to new node and left and right to null
    head = newNode;
    return;
  }
  //make an array to keep track of directions to new node
  int directions[80];
  int count = 0;
  //in case I need to remember the original location
  int remember = location;
  while (location != 1) {
    //if the new node is in a left slot
    if (location % 2 == 0) {
      //set direction index to zero to represent going left
      directions[count] = 0;
      count++;
      //set location to the node above
      location = location/2;
    }
    else {
      //if node is in right slot, set index to 1 to represent going right
      directions[count] = 1;
      count++;
      //set location to node above
      location = (location-1)/2;
    }
  }
  //Note: location now equals 1
  Node* currentNode = head;
  //running through the directions backwards
  for (int i = count; i > 0; i--) {
    //if direction is left
    if (directions[i-1] == 0) {
      //if this is the empty slot, place Node there
      if (currentNode->left == NULL) {
	currentNode->left = newNode;
	break;
      }
      //otherwise, follow the direction
      else {
	currentNode = currentNode->left;
      }
    }
    //if direction is right
    if (directions[i-1] == 1) {
      //if this is the empty slot, place Node there
      if (currentNode->right == NULL) {
	currentNode->right = newNode;
	break;
      }
      //otherwise, go right
      else {
	currentNode = currentNode->right;
      }
    }
  }
  //swap upwards until in right place
  location = remember;
  //location is now where the node was placed
  while (location != 1) {
    //if number is on left side
    if (location %2 == 0) {
      //upper node location
      int nextLocation = location/2;
      //if the newNode number is greater than the upper node number
      if (array[location-1]->number >= array[nextLocation-1]->number) {
	if (nextLocation != 1 && nextLocation != 0) {
	//if the upper node's pair is greater, swap those two nodes first
	  int possibleOther = 0;
	  if (nextLocation%2 == 0) {
	    possibleOther = nextLocation+1;
	  }
	  else {
	    possibleOther = nextLocation-1;
	  }
	  //if the other node in the pair is lower
	  if (array[nextLocation-1]->number > array[possibleOther-1]->number) {
	    //exchange left and right
	    Node* otherLeft = NULL;
	    if (array[possibleOther-1]->left != NULL) {
	      otherLeft = array[possibleOther-1]->left;
	    }
	    Node* otherRight = NULL;
	    if (array[possibleOther-1]->right != NULL) {
	      otherRight = array[possibleOther-1]->right;
	    }
	    if (array[nextLocation-1]->left != NULL) {
	      array[possibleOther-1]->left = array[nextLocation-1]->left;
	    }
	    else {
	      array[possibleOther-1]->left = NULL;
	    }
	    if (array[nextLocation-1]->right != NULL) {
	      array[possibleOther-1]->right = array[nextLocation-1]->right;
	    }
	    else {
	      array[possibleOther-1]->right = NULL;
	    }
	    array[nextLocation-1]->left = otherLeft;
	    array[nextLocation-1]->right = otherRight;
	    //switch the order with the upper node
	    if (nextLocation%2 == 0) {
	      int upperNode = nextLocation/2;
	      array[upperNode-1]->left = array[possibleOther-1];
	      array[upperNode-1]->right = array[nextLocation-1];
	    }
	    else {
	      int upperNode = (nextLocation-1)/2;
	      array[upperNode-1]->left = array[possibleOther-1];
	      array[upperNode-1]->right = array[nextLocation-1];
	    }
	    //swap array positions
	    Node* temp = array[possibleOther-1];
	    array[possibleOther-1] = array[nextLocation-1];
	    array[nextLocation-1] = temp;
	}
	}
	int firstLocation = 0;
	if (nextLocation == 1) {
	  head = array[location-1];
	}
	//if upper node is a left node
	else if (nextLocation%2 == 0) {
	  //upper node location
	  firstLocation = nextLocation/2;
      	  //set upper node->left node to new Node
	  array[firstLocation-1]->left = array[location-1];
	}
	//if upper node is a right node
	else {
	  //upper node location
	  firstLocation = (nextLocation-1)/2;
	  //upper Node's right is new new node
	  array[firstLocation-1]->right = array[location-1];
	  
	}
	//get right and left nodes of new node
	Node* putLeft = NULL;
	if (array[location-1]->left != NULL) {
	  putLeft = array[location-1]->left;
	}
	Node* putRight = NULL;
	if (array[location-1]->right != NULL) {
	  putRight = array[location-1]->right;
	}
	//set newNode's left to upper node
	if (array[nextLocation-1] != NULL) {
	  array[location-1]->left = array[nextLocation-1];
	}
	else {
	  array[location-1]->left = NULL;
	}
	//set right to upper node's right
	if (array[nextLocation-1]->right != NULL) {
	  array[location-1]->right = array[nextLocation-1]->right;
	}
	else {
	  array[location-1]->right = NULL;
	}
	//set upper node's left and right to new node's previous left and right
	array[nextLocation-1]->left = putLeft;
	array[nextLocation-1]->right = putRight;
	//get the upper node in array position
	Node* temp = array[nextLocation-1];
	//set the upper node's array location to the newNode
	array[nextLocation-1] = array[location-1];
	//set new node's array location to upper node
	array[location-1] = temp;
	//set location to new location
	location = nextLocation;
      }
      
      //otherwise, number is in right place
      else {
	return;
      }
    }
    //if number is on right side of node
    else {
      //upper node location
      int nextLocation = (location-1)/2;
      //if lower node has higher number than upper node
      if (array[location-1]->number >= array[nextLocation-1]->number) {
	if (nextLocation != 1 && nextLocation != 0) {
	//if the upper node's pair is greater, swap those two nodes first
	  int possibleOther = 0;
	  if (nextLocation%2 == 0) {
	    possibleOther = nextLocation+1;
	  }
	  else {
	    possibleOther = nextLocation-1;
	  }
	  //if the other node in the pair is lower
	  if (array[nextLocation-1]->number > array[possibleOther-1]->number) {
	    //exchange left and right
	    Node* otherLeft = NULL;
	    if (array[possibleOther-1]->left != NULL) {
	      otherLeft = array[possibleOther-1]->left;
	    }
	    Node* otherRight = NULL;
	    if (array[possibleOther-1]->right != NULL) {
	      otherRight = array[possibleOther-1]->right;
	    }
	    if (array[nextLocation-1]->left != NULL) {
	      array[possibleOther-1]->left = array[nextLocation-1]->left;
	    }
	    else {
	      array[possibleOther-1]->left = NULL;
	    }
	    if (array[nextLocation-1]->right != NULL) {
	      array[possibleOther-1]->right = array[nextLocation-1]->right;
	    }
	    else {
	      array[possibleOther-1]->right = NULL;
	    }
	    array[nextLocation-1]->left = otherLeft;
	    array[nextLocation-1]->right = otherRight;
	    //switch the order with the upper node
	    if (nextLocation%2 == 0) {
	      int upperNode = nextLocation/2;
	      array[upperNode-1]->left = array[possibleOther-1];
	      array[upperNode-1]->right = array[nextLocation-1];
	    }
	    else {
	      int upperNode = (nextLocation-1)/2;
	      array[upperNode-1]->left = array[possibleOther-1];
	      array[upperNode-1]->right = array[nextLocation-1];
	    }
	    //swap array positions
	    Node* temp = array[possibleOther-1];
	    array[possibleOther-1] = array[nextLocation-1];
	    array[nextLocation-1] = temp;
	}
	}
	//if upper node is on left side
	int firstLocation = 0;
	if (nextLocation == 1) {
	  head = array[location-1];
	}
	else if (nextLocation%2 == 0) {
	  //upper upper node location
	  firstLocation = nextLocation/2;
	  //set upper upper node's left to the newNode
	  array[firstLocation-1]->left = array[location-1];
	}
	//otherwise, set upper upper node's right to newNode
	else {
	  firstLocation = (nextLocation-1)/2;
	  array[firstLocation-1]->right = array[location-1];
	}
	//get new node's left and right
	
	Node* putLeft = NULL;
	if (array[location-1]->left != NULL) {
	  putLeft = array[location-1]->left;
	}
	Node* putRight = NULL;
	if (array[location-1]->right != NULL) {
	  putRight = array[location-1]->right;
	}
	//set new node's right to previous upper node
	if (array[nextLocation-1] != NULL) {
	array[location-1]->right = array[nextLocation-1];
	}
	else {
	  array[location-1]->right = NULL;
	}
	//set new node's left to previous upper node's left
	if (array[nextLocation-1]->left != NULL) {
	array[location-1]->left = array[nextLocation-1]->left;
	}
	else {
	  array[location-1]->left = NULL;
	}
	//set previous upper node's right and left
	array[nextLocation-1]->right = putRight;
	array[nextLocation-1]->left = putLeft;
	//get new node
	Node* temp = array[location-1];
	//set new node's array position to the previous upper node
	array[location-1] = array[nextLocation-1];
	//set previous upper node's location to new node
	array[nextLocation-1] = temp;
	location = nextLocation;
      }
      //otherwise, return
      else {
	return;
      }
    }
  }
}


Node* Heap::removeMax() {
  if (head == NULL) {
    int newFinal = finalIndex-1;
    finalIndex = newFinal;
    return NULL;
  }
  if (head->left == NULL) {
    Node* temp = head;
    head = NULL;
    int newFinal2 = finalIndex-1;
    finalIndex = newFinal2;
    return temp;
  }
  Node* returnNode = head;
  //swap the top and bottom Nodes using the array
  //if the last index is a left node
  if (finalIndex%2 == 0) {
    //set upper node's left to null
    int index = (finalIndex/2)-1;
    array[index]->left = NULL;
  }
  else {
    //if right node, set upper node's right to null
    int index = ((finalIndex-1)/2)-1;
    array[index]->right = NULL;
  }
  if (head->left != NULL) {
    array[finalIndex-1]->left = head->left;
  }
  if (head->right != NULL) {
    array[finalIndex-1]->right = head->right;
  }
  head = array[finalIndex-1];
  array[0] = array[finalIndex-1];
  array[finalIndex-1] = NULL;
  //swap top Node
  Node* currentNode = head;
  int arrayLocation = 1;
  //if the left and right node both exist
  if (currentNode->left != NULL && currentNode->right != NULL) {
    //while they still both exist
    while (currentNode->left != NULL && currentNode->right != NULL) {
      //if one lower node has a higher number
      if (currentNode->left->number > currentNode->number || currentNode->right->number > currentNode->number) {
	int newIndex = 0;
	//if the left is greater than the right and greater than the current number
	if (currentNode->left->number > currentNode->right->number && currentNode->left->number > currentNode->number) {
	  //remember thelower node's left and right
	  Node* newLeft = NULL;
	  if (currentNode->left->left != NULL) {
	    newLeft = currentNode->left->left;
	  }
	  Node* newRight = NULL;
	  if (currentNode->left->right != NULL) {
	    newRight = currentNode->left->right;
	  }
	  //set currentNode's left's left to current node
	  currentNode->left->left = currentNode;
	  //if the currentNode's right isn't null, set lower node's right to that
	  if (currentNode->right != NULL) {
	    currentNode->left->right = currentNode->right;
	  }
	  else {
	    currentNode->left->right = NULL;
	  }
	  //reset current Node's left and right
	  currentNode->left = newLeft;
	  currentNode->right = newRight;
	  
	  //the new index of the current Node is the previous one times 2
	  newIndex = arrayLocation*2;
	}
	//if right node is higher
	else {
	  //get currentNode's right's left and right
	  Node* newLeft = NULL;
	  if (currentNode->right->left != NULL) {
	    newLeft = currentNode->right->left;
	  }
	  Node* newRight = NULL;
	  if (currentNode->right->right != NULL) {
	    newRight = currentNode->right->right;
	  }
	  //set currenNode's right's left and rights
	  currentNode->right->right = currentNode;
	  if (currentNode->left != NULL) {
	    currentNode->right->left = currentNode->left;
	  }
	  else {
	    currentNode->right->left = NULL;
	  }
	  //set currentNode's rights and lefts
	  currentNode->left = newLeft;
	  currentNode->right = newRight;
	  //new index for currentNode is array location times 2 plus one
	  newIndex = (arrayLocation*2)+1;
	}
	//get current node (this is kinda redundant but I'm keeping it :/) 
	Node* temp = array[arrayLocation-1];
	//set current node's node to new node
	array[arrayLocation-1] = array[newIndex-1];
	//place current node in new spot
	array[newIndex-1] = temp;
	if (arrayLocation == 1) {
	  head = array[0];
	}
	arrayLocation = newIndex;
      }
      //if both lower nodes are lower
      else {
	int newFinal3 = finalIndex-1;
	finalIndex = newFinal3;
	return returnNode;
      }
    }
  }
  //if right node is null but left node isn't and the number is greater
  if (currentNode->left != NULL) {
    if (currentNode->left->number > currentNode->number) {
      //just swap the two nodes
      currentNode->left->left = currentNode;
      currentNode->left = NULL;
      int newIndex = arrayLocation*2;
      array[arrayLocation-1] = array[newIndex-1];
      array[newIndex-1] = currentNode;
      if (arrayLocation == 1) {
	head = array[0];
      }
    }
  }
  int newFinal4 = finalIndex-1;
  finalIndex = newFinal4;
  return returnNode;
  
}
