/* Author: Julia Chung
Spring 2020 Semester at Stevens Institute of Technology
Linked List C++ program with functions of insert at head, insert at specific position, 
remove, and display contents of list.
*/ 

#include <iostream>
using namespace std;

class Chunk {
public:
  int value;
  Chunk *next;

  Chunk() {
    value = 0;
    next = NULL;
  }
};

class LinkedList {
public:
  Chunk *head;
  int length;

  LinkedList() {
    head = NULL;
    length = 0;
  }
  
 
  
  void insertAtHead(int value) {
    //insert at position 1
    Chunk *temp = new Chunk;
    temp->value = value;
    
    temp->next = head;
    head = temp;
    length++;
  }
  
  //1. Add something to the list
  void insertAtPosition(int position, int value) {
    //check if position is valid
    if (position > 0 && position <= length + 1) {
      Chunk *temp = new Chunk;
      temp->value = value;

      if(position == 1) {
	temp->next = head;
	head = temp;
      }
      else if(position > 1 && position <= length) {
	Chunk *helper = head;
	//take helper to (position - 1)
	for(int i = 1; i < position - 1; i++)
	{
	  helper = helper->next;
	  cout << "Helper @: " << helper->value << endl; //prints out where helper is exactly
	}
	
	temp->next = helper->next;
	helper->next = temp;	
      }
      else {
	Chunk *helper = head;
	while(helper->next != NULL)
	    helper = helper->next;
        helper->next = temp;
      }
      length++; //DO NOT FORGET
    }
    else
    {
      cout << "Can't do that, invalid position" << endl;
    }
  }
  

  
  //2. Remove something from the list
  void removeFromPosition(int position) {
    if(position > 0 && position <= length+1) {
      if(position == 1 && length == 1) {
	delete head;
	head = NULL;
      }
      else if(position == 1 && length > 1) {
	Chunk *temp = head;
	head = head->next;
	delete temp;
      }
      else if(position > 1 && position <= length)
	{
	  Chunk *temp, *slow;
	  temp = slow = head;

	  for(int i = 1; i < position; i++) {
	    slow = temp;
	    temp = temp->next; //makes sure temp is always in front of slow
	  }
	  slow->next = temp->next;
	  delete temp;
	}
      length--;
    }
    else
    {
      cout << "Will not delete: invalid position" << endl;
    }
  }

  //3. Display contents
  void displayContents() {
    if(head==NULL) {
      cout << "Empty list, nothing to display" << endl;
    }
    else {
      Chunk *temp;
      temp = head;
      cout << "head-->";
      while (temp != NULL) {
	cout << temp->value << "-->";
	temp = temp->next;
      }
      cout << "NULL" << endl;
    }
  }
};

int main() {
  LinkedList LL;
  int choice, value, position;

  LL.displayContents();

  while(1) {
    cout << "Press 1 to insert at head" << endl;
    cout << "Press 2 to insert at specific position" << endl;
    cout << "Press 3 to remove from specific position" << endl;
    cout << "Press 4 to display" << endl;
    cout << "Anything else to quit" << endl;
    cin >> choice;

    switch(choice) {
    case 1: cout << "Insert what?" << endl;
      cin >> value;
      LL.insertAtHead(value);
      break;
    case 2: cout << "Insert what?" << endl;
      cin >> value;
      cout << "Insert where?" << endl;
      cin >> position;
      LL.insertAtPosition(position, value);
      break;
    case 3: cout << "Remove from where?" << endl;
      cin >> position;
      LL.removeFromPosition(position);
      break;
    case 4: cout << "-----------" << endl;
      LL.displayContents();
      cout << "-----------" << endl;
      break;
    default: cout << "Goodbye!" << endl;
      exit(1);
    }
  }
  
}
