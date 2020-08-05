/* Author: Julia Chung
Spring 2020 Semester at Stevens Institute of Technology
Binary Search Tree C++ program
*/ 
#include <iostream>
using namespace std;

class TreeChunk {
 public:
  int data;
  TreeChunk *left;
  TreeChunk *right;

  TreeChunk() {
    data = 0;
    left = right = NULL;
  }
};

class BST {
 public:
  TreeChunk *root;

  BST() {
    root = NULL;
  }

  //1. Add new values to the tree
  void add(int x) {
    if(root == NULL) { //empty tree!
      root = new TreeChunk;
      root->data = x;
      cout << "Just added value: " << x << endl;
      return;
    }

    TreeChunk *slow, *fast; //slow= will NOT fall off tree, fast= will fall off, then gets added
    slow = fast = root;

    while(fast != NULL) {
      if(x < fast->data) {
	slow = fast;
	fast = fast->left;
      }
      else if(x > fast->data) {
	slow = fast;
	fast = fast->right;
      }
      else {
	cout << "We do not allow duplicates" << endl;
	return;
      }
    }
    
    if(x < slow->data) {
      slow->left = new TreeChunk;
      slow->left->data = x;
    }
    else {
      slow->right = new TreeChunk;
      slow->right->data = x;
    }
    cout << "Successfully added: " << x << endl;
  }
  
  //2. Search for a value
  bool search(int key, TreeChunk *start) {
    //anchor value
    if(start == NULL) {
      cout << "Could not find the value you are looking for" << endl;
      return false;
    }
    //recursive step
    else {
	if(key == start->data) {
	  cout << "Success! Value found in tree" << endl;
	  return true;
	}
	if(key < start->data) {
	  return search(key, start->left);
	}
	else {
	  return search(key, start->right);
	}
    }	
  }
    
  //3. Display contents
  void preorder(TreeChunk *start) {
    //anchor value
    if(start == NULL)
      return;
    else {
      //root, left, right
      cout << start->data << endl;
      preorder(start->left);
      preorder(start->right);
    }
  }

  void postorder(TreeChunk *start) {
    //anchor value
    if(start == NULL)
      return;
    else {
      //left, right, root
      postorder(start->left);
      postorder(start->right);
      cout << start->data << endl;
    }
  }

  void inorder(TreeChunk *start) {
    //anchor value
    if(start == NULL)
      return;
    else {
      //left, root, right
      inorder(start->left);
      cout << start->data << endl;
      inorder(start->right);
    }
  }
  
  //4. Deleting values from the tree
  void deleteNode(int key) {
    //empty tree test
    if(root == NULL) {
      cout << "Empty tree, nothing to delete" << endl;
      return;
    }
    
    // 1) search and find that node
    TreeChunk *slow, *fast;
    slow = fast = root;

    while(fast != NULL && fast->data != key) {
      //keep going left or right
      if(key < fast->data) {
	slow = fast;
	fast = fast->left;
      }
      else {
	slow = fast;
	fast = fast->right;
      }
    }
    if(fast == NULL) {
      cout << "This node does not exist in this tree" << key << endl;
      return;
    }

    // 2) begin to classify the case for delete (1, 2, or 3)
    cout << "Found the node, now trying to classify the type of delete!" << endl;
    
    //CASE 1: both the left and right points are NULL (No children)
    if(fast->right == NULL && fast->left == NULL) {
      cout << "Looks like a Case-I delete " << endl;
      if(slow->right == fast) {
	slow->right = NULL;
	cout << "About to delete: " << fast->data << endl;
	delete fast;
      }
      else {
	//the node is to the left
	slow->left = NULL;
	cout << "About to delete: " << fast->data << endl;
	delete fast;
      }
    }
    //CASE 2: has ONE child
    else if ((fast->right == NULL && fast->left != NULL) || (fast->right != NULL && fast->left == NULL)) {
      cout << "Case II delete" << endl;
      if(fast->left != NULL) {
	if(slow->left == fast) {
	  //fast is to the left of slow, and the lone child is to the left of fast
	  slow->left = fast->left;
	  cout << "About to delete: " << fast->data << endl;
	  delete fast;
	}
	else if(slow->right == fast) {
	  //fast is to the right of slow, and the lone child is to the left of fast
	  slow->right = fast->left;
	  cout << "About to delete: " << fast->data << endl;
	  delete fast;
	}
      }
      if(fast->right != NULL) {
	if(slow->left == fast) {
	  //fast is to the left of slow, and the lone child is to the right of fast
	  slow->left = fast->right;
	  cout << "About to delete: " << fast->data << endl;
	  delete fast;
	}
        else if(slow->right == fast) {
	  slow->right = fast->right;
	  cout << "About to delete: " << fast->data << endl;
	  delete fast;
	}
      }
    }
    // 3) proceed to delete
    else {
      cout << "This is a case III delete for " << key << endl;
      TreeChunk *temp;
      temp = fast->right;
      while(temp->left != NULL) {
	 temp = temp->left;
      }
      int key2 = temp->data;
      deleteNode(key2);
      fast->data = key2;
      }
    }

};




int main() {
  BST myTree;
  int choice1, choice2, x, key;

  cout << "HELLOOO, welcome to Julia's Binary Search Tree." << endl;
    
  while(1) {
    cout << " =======================" << endl;
     cout << "Choose a number:" << endl;
     cout << "1: ADD- Add new nodes to my tree!?" << endl;
     cout << "2: SEARCH- Looking for a certain node in my tree?" << endl;
     cout << "3: TRAVERSE- My tree is NOT empty so you can traverse it" << endl;
     cout << "4: DELETE- Do you want to delete a node? :(" << endl;
     cout << "ANYTHING ELSE TO QUIT!" << endl;
     cin >> choice1;
     
    switch(choice1) {
    case 1:
      cout << "What number do you want to add?" << endl;
      cin >> x;
      cout << " =======================" << endl;
      myTree.add(x);
      break;
    case 2:
      cout << "What node are you searching for?" << endl;
      cin >> key;
      cout << " =======================" << endl;
      myTree.search(key, myTree.root);
      break;
    case 3:
      cout << "Choose a traversal:" << endl;
      cout << "1: pre-order traversal" << endl;
      cout << "2: post-order traversal" << endl;
      cout << "3: in-order traversal" << endl;
      cin >> choice2;
      cout << " =======================" << endl;
      
      if (choice2 == 1) {
	myTree.preorder(myTree.root);
      }
      else if (choice2 == 2) {
	myTree.postorder(myTree.root);
      }
      else {
	myTree.inorder(myTree.root);
      }
      break;
    case 4:
      cout << "Please input the value you want to delete: " << endl;
      cin >> key;
      cout << " =======================" << endl;
      myTree.deleteNode(key);
      break;
    default:
      cout << "BYE BYE" << endl;
      exit(0);
    }
  }

  return 0;
}
