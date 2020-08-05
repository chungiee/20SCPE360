/* Author: Julia Chung
Spring 2020 Semester at Stevens Institute of Technology
Stacks, queues, and linked list C++ program with functions of push, pop, and display contents of list
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
    if(position > 0 && position <= length) {
      if(position == 1 && length == 1) {
	delete head;
	head = NULL;
      }
      if(position == 1 && length > 1) {
	Chunk *temp = head;
	head = head->next;
	delete temp;
      }
      else if(position > 1 && position <= length)
	{
	  Chunk *temp, *slow;
	  temp = slow = head;

	  for(int i = 1; i <= position; i++) {
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
      while (temp != NULL) {
	cout << temp->value << "-->";
	temp = temp->next;
      }
      cout << "NULL" << endl;
    }
  }
};


// Stack of "Chunks"
class Stack {
public:
  Chunk *top;

  Stack() {
    top = NULL;
  }
  
  //1. PUSH: add a new element
  void push(int value) {
    // add this value into the structure
    Chunk *another;
    another = new Chunk;
    another->value = value;
    // case 1: structure is empty: simply make this new value the "top"
    if(top == NULL) { // there is only one element
      top = another;
    }
    else { // if there is more than one element
      another->next = top;
      top = another;
    }
  }
  
  //2. POP: remove an element
  void pop() {
    // stack empty: do nother
    if(top == NULL) {
      cout << "Empty, stack, nothing to delete" << endl;
      return;
    }
    else {
      Chunk *another;
      another = top;
      top = top-> next;

      cout << "About to delete: " << another->value << endl;
      delete another;
    }
  }
  
  //3. DISPLAY: show me the contents
  void displayContents() {
    if(top == NULL) {
      cout << "Empty Stack: nothing to display" << endl;
      return;
    }
    else {
      Chunk *another;
      another = top;

      while (another != NULL) {
	cout << another->value << "-->";
	another = another->next;
      }
      cout << "NULL" << endl;
    }
  }
};

//queue of "chunks"
class Queue {
public:
  Chunk *head; //located in the app space while all other queues are in the heap
  Queue() {
    head = NULL;
  }

  //1. Add chunks to the Q (enqueue)
  void enqueue(int value) {
    Chunk *temp = new Chunk; 
    temp->value = value; //take the input given by user and set it to a new variable temp 
    // check if the queue is empty or not
    if(head==NULL) {
      head = temp;
    }
    else {
      temp->next = head;
      head = temp;
    }		  
  }
  
  //2. Remove a chunk from the Q (dequeue)
  //remove from the end: find out the last chunk, and get rid of it
  void dequeue() {
    if(head==NULL) {
      cout << "Empty queue, nothing to delete" << endl;
    }
    else if(head->next == NULL) { //dealing with only one chunk
      delete head;
      head = NULL;
    }
    else {
      //we'll go find the last chunk
      Chunk *chase, *follow;
      chase = follow = head;
      while(chase->next != NULL)
	{
	  follow = chase;
	  chase = chase->next;
	}
      follow->next = NULL;
      cout << "Deleting: " << chase->value << endl;
      delete chase;  
    }	    
  }
  
  //3. Print the content of the Q
  void printContents() {
    if(head==NULL) {
      cout << "Empty Q, nothing to display" << endl;
    }
    else {
      Chunk *temp;
      temp = head;
      while (temp != NULL) {
	cout << temp->value << "-->";
	temp = temp->next;
      }
      cout << "NULL" << endl;
    }
  }
  
};


int main()
{
  LinkedList LL;
  int choice, value, position;
  LL.insertAtHead(3);
  LL.insertAtHead(7);
  LL.insertAtHead(2);
  LL.insertAtHead(1);
  LL.insertAtHead(4);
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
  
  Stack myStack;

  // add 5,6,3,9,10
  myStack.push(5);
  myStack.push(6);
  myStack.push(3);
  myStack.push(9);
  myStack.push(10);

  myStack.displayContents();

  while(1) {
    cout << "Press 1 to add" << endl;
    cout << "Press 2 to pop" << endl;
    cout << "Press 3 to display" << endl;
    cout << "Anything else to quit" << endl;
    cin >> choice;

    switch(choice) {
    case 1: cout << "Add what?" << endl;
      cin >> value;
      myStack.push(value);
      break;

    case 2: myStack.pop();
      break;
    case 3: cout << "-------------" << endl;
      myStack.displayContents();
      cout << "-----------------" << endl;
      break;
    default: cout << "Goodbye!" << endl;
      exit(1);
      
    }
  }
  Queue Q; //creates on object of the class Queue in the app space that has a head variable

  while(1) {
    cout << "Press 1 to add (enQ)" << endl;
    cout << "Press 2 to remove (deQ)" << endl;
    cout << "Press 3 to display" << endl;
    cout << "Anything else to quit" << endl;
    cin >> choice;

    switch(choice) {
      
    case 1 : cout << "Add what? " << endl;
      cin >> value;
      Q.enqueue(value);
      break;
      
    case 2 : Q.dequeue();
      break;

    case 3 : Q.printContents();
      break;

    default : cout << "Goodbye!" << endl;
      exit(1);
  }
  
}
}


