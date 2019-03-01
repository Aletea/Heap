#include <iostream>
#include <cstring>
#include <fstream>
#include <iomanip>
#include "Heap.h"
#include <stdlib.h> //for char->int conversion 

void printTree(Node** headNode);

int main() {
  //get file/manual input
  cout << "would you like to use a file or manual input? (enter 'file' for file, and 'manual' for manual input" << endl;
  char input[80];
  cin.get(input, 80);
  cin.get();
  while (strcmp(input,"file") != 0 && strcmp(input, "manual") != 0) {
    cout << "invalid input" << endl;
    cin.get(input, 80);
    cin.get();
  }
  //keeps track of numbers
  int list[200];
  int index = 0;
  //if file
  if (strcmp(input, "file") == 0) {
    //get file path
    cout << "enter file path" << endl;
    char newFilePath[100];
    cin.get(newFilePath, 100);
    cin.get();
    //GET DIRECTORY
    ifstream textFile;
    textFile.open(newFilePath);
    while (!textFile) {
      cout << "File Destination Not Found. Please Reneter" << endl;
      cin.get(newFilePath, 100);
      cin.get();
      textFile.open(newFilePath);
    }
    //get file length
      textFile.seekg(0, textFile.end);
      int length = textFile.tellg();
      textFile.seekg(0, textFile.beg);
      //run through new file and add to int array list
      char charArray[100];
      for (int i = 0; i < length; i++) {
	charArray[i] = textFile.get();
      }
      //convert characters to numbers and add to list
      for (int i = 0; i < length; i++) {
	char number[10];
	int count = 0;
	while (charArray[i] != ' ' && i < length) {
	  number[count] = charArray[i];
	  i++;
	  count++;
	}
	number[count] = '\0';
	int newNum = atoi(number);
	list[index] = newNum;
	index++;
      }
  }
  //if manual input
  else {
    bool stillEntering = true;
    //continuously get number input and add it to the list until user says they don't wanna keep entering numbers
    while (stillEntering == true) {
    cout << "Input Number: ";
    int Number;
    cin >> Number;
    cin.ignore();
    list[index] = Number;
    index++;
    cout << "Would you like to enter again? (y/n) ";
    char input2[10];
    cin.get(input2, 10);
    cin.get();
    if (strcmp(input2, "n") == 0) {
	stillEntering = false;
    }
    }
  }
  //create heap
  Heap* maxheap = new Heap();
  int counting = 0;
  //insert nodes
  while (counting < index) {
    Node* newNode = new Node();
    newNode->number = list[counting];
    maxheap->insertNode(newNode);
    counting++;
  }
  //print tree
  Node** headNode = maxheap->getArray();
  printTree(headNode);
  int output[200];
  int outputIndex = 0;
  //whilw the top node is not null, remove that node and add it to the output
  while (maxheap->getHead() != NULL) {
    Node* outputNode = new Node();
    outputNode = maxheap->removeMax();
    output[outputIndex] = outputNode->number;
    outputIndex++;
  }
  int counting2 = 0;
  //print output
  cout << "Output: " << endl;
  while (counting2 < outputIndex) {
    cout << output[counting2] << " ";
    counting2++;
  }
  return 0;
}

//print the tree
void printTree(Node** headNode) {
  cout << "Tree: " << endl;
  bool stillGoing = true;
  //number of nodes in the current row
  int counter = 1;
  //index of array
  int place = 0;
  //keep printing nodes until there are none left
  while (stillGoing == true) {
    //for the number of nodes there should be 
    for (int i = 0; i < counter; i++) {
      //if null, end of array, return
      if (headNode[place] == NULL) {
	cout << endl;
	return;
      }
      //if even node, then add extra spaces to separate node pairs
      if (place%2 == 0) {
	cout << headNode[place]->number << "   ";
      }
      else {
	cout << headNode[place]->number << " ";
      }
      //add index
      place++;
    }
    //next number of nodes in the next sequence :)
    counter = counter*2;
    cout << endl;
  }
}
