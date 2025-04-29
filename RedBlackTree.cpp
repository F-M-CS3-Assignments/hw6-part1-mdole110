#include "RedBlackTree.h"
#include <iostream>

using namespace std;
//COPY CONSTRUCTOR AND PRIVATE FUNCTIONS AND TESTS 

/*
ZYBOOKS REFERENCED:
15.5-15.10
16.1, 16.2
8.14 - copy constructor
*/

/*
struct RBTNode {
	int data;
	unsigned short int color;
	RBTNode *left = nullptr;
	RBTNode *right = nullptr;
	RBTNode *parent = nullptr;
	bool IsNullNode = false;
};
*/
RedBlackTree::RedBlackTree(){
    //constructor implementation
    //no data input so root is null and there are 0 itemsm
    root = nullptr;
    numItems = 0;
};

RedBlackTree::RedBlackTree(int newData){
    //constructor for when there's data input?
    root = new RBTNode; //set to root  cuz starting
    root->data = newData; //set data to new data 
    root->color = COLOR_BLACK; //root always black
    root->left = nullptr; //none yet
    root->right = nullptr; //none yet
    root->parent = nullptr; //root 
    numItems = 1; //b/c new data is 1 

}
RedBlackTree::RedBlackTree(const RedBlackTree &rbt){
    //do this last
    RBTNode* newRootNode = CopyOf(rbt.root);
    root = newRootNode;

}
RBTNode* RedBlackTree::CopyOf(const RBTNode *node){
    if(node == nullptr){
        return nullptr;
    }
    RBTNode* newNode = new RBTNode;
    //set up the data and color
    newNode->data = node ->data;
    newNode->color = node->color;
    newNode->parent = node->parent;
    //set children
    newNode->left =CopyOf(node->left);//recurse to asign left subtree values to new left subtree 
    newNode->right=CopyOf(node->right);

    return newNode;


}
string RedBlackTree::GetColorString(const RBTNode *n){
    string color_string; 
    //string color_string;
    if(n->color == COLOR_BLACK){
        color_string= "B";
    }
    else{
        color_string = "R";
    }
    //if(numItems>1){
    return color_string;
    //}
}
string RedBlackTree::GetNodeString(const RBTNode *n){
    return GetColorString(n) + to_string(n->data);
}
string RedBlackTree::ToInfixString(const RBTNode *n){
    
    //aka SHOULD BE RECURSIVE
    //return ToInfixString(root);
    if(n== nullptr){
        return "";
   }
   string infixoutput = "";
   infixoutput += ToInfixString(n->left);
   infixoutput += " " + GetNodeString(n) + " "; //tryonh to match spacing
   infixoutput +=ToInfixString(n->right);
   return infixoutput;
}


string RedBlackTree::ToPrefixString(const RBTNode *n){ 
    //make sure the node exists 
   //string prefixoutput;
   if(n== nullptr){
        return "";
   }
   string prefixoutput;
   prefixoutput = " " + GetNodeString(n) + " " + ToPrefixString(n->left) + ToPrefixString(n->right);
   return prefixoutput;
    
}


string RedBlackTree::ToPostfixString(const RBTNode *n){ 
    
    //make sure the node exists 
   //string prefixoutput;
   if(n== nullptr){
    return "";
}
    string postfixoutput;
    postfixoutput += ToPostfixString(n->left);
    postfixoutput += ToPostfixString(n->right);
    postfixoutput += " " + GetNodeString(n) + " ";
    return postfixoutput;
    
}
//string RedBlackTree::ToPostfixString();

void RedBlackTree::Insert(int newData){
    if(Contains(newData)){
        throw invalid_argument("Cannot add duplicate values");
    }

    RBTNode* node = new RBTNode;
    //color red, data = newData
    node->data = newData;
    node->color = COLOR_RED;
    //node->parent = nullptr; //trouble shooting segmentation error
    //node->left = nullptr;
    //node->right = nullptr;
    if(root==nullptr){
        node->color = COLOR_BLACK;
        root = node;
        //return
        //leaf node so
        numItems++;
       return;
    }
    BasicInsert(node);
    //if(node->parent == nullptr){
      //  cout << "RUNNING" << endl;
        //node->color = COLOR_BLACK;
    //}
    if(node -> parent != nullptr && node->parent->color == COLOR_RED){
        //cout << "CALLED IN INSERT FUNCTION" << endl;
        InsertFixUp(node);
    }
    numItems++;
    root->color = COLOR_BLACK;

}



void RedBlackTree::BasicInsert(RBTNode *node){
    RBTNode *curNode = root; //set current node to root to start at the root
    RBTNode *parentNode = nullptr; //there's no parent of a root node 

    while(curNode != nullptr){ //while the current node isn't empty
        parentNode = curNode; //switch current node to parent node
        if(node->data < curNode->data){ //if the number associateed with node (the one we want to insert as a leaf node) is less than the number assocuated with curNode, move on TO THE LEFT (BST)
            curNode = curNode->left;
        } else{
            curNode = curNode ->right;
        }
    }
    //parent node needs to be updated too
    node->parent = parentNode;
    //then once the curNode = nullptr
    if(parentNode == nullptr){
        root = node;
    } else if(node->data < parentNode->data){
        parentNode->left = node;
    }else{ 
        parentNode->right = node;
    }
    //node->left = nullptr;
    //node->right = nullptr;
    }
    



RBTNode* RedBlackTree::GetUncle(RBTNode *node) const{
    //uncle as in sibling or same row as parent 
    //so check where the patent is and then find the parent of the parent and then choose the other child
    //GPNode = node -> parent ->parent;
    if(node == nullptr || node->parent == nullptr || node -> parent -> parent == nullptr){
        return nullptr; //if there's no parent or no grand parent it doesnt work
    }
    RBTNode* GPNode = node -> parent ->parent;

    //check whether the node's parent is the left/right child of the grandparent and then return opposite one
    if(node->parent == GPNode ->left){
        return GPNode->right;
    }
    else{
        return GPNode->left;
    }


}


void RedBlackTree::InsertFixUp(RBTNode *newNode){
    while(newNode != root && newNode->parent!=nullptr &&newNode->parent->color == COLOR_RED){

    //if(newNode->parent->color != COLOR_RED){
      //  cout << "Node's parent is not red." <<endl;
        //return;
    //}
    //cout << "FIX UP CALLED AND RUNNING" << endl;
    //uncle parend and grand parent

    //if(newNode == nullptr || newNode->parent == nullptr){
      //  cout << "either new Node or parent of newNode is null...returning" << endl;
        //return;
    //}
    RBTNode *parentNode = newNode ->parent;
    RBTNode *GPNode = parentNode ->parent;
    //if(parentNode != nullptr){
      //  GPNode = parentNode->parent;
    //}
    RBTNode *uncleNode = GetUncle(newNode);
    if(newNode ->parent ->parent != nullptr){
        GPNode = newNode ->parent->parent;
    }
    else{
        GPNode = nullptr;
    }
    //if(parentNode==nullptr || parentNode ->parent == nullptr){
       // cout << "either parent node or parent of parent node is null" << endl;
        //return;
    //}
    

    if(uncleNode != nullptr && uncleNode->color == COLOR_RED){
        //set uncle and parent (its sibling to black)
        uncleNode->color = COLOR_BLACK;
        parentNode->color = COLOR_BLACK;
        if(GPNode !=nullptr){
        GPNode -> color = COLOR_RED;
            if(GPNode ->parent !=nullptr && GPNode ->parent->color == COLOR_RED){
                InsertFixUp(GPNode);
            }
        }
        newNode = GPNode;
    }
    //OTHERWISE (IF UNCLE IS NULL OR BLACK):
    //just rearrange


    else if(GPNode!=nullptr){
        //cout << "GPNode !=null...changing color to red " << endl;
        //cout << "printing GPNode " << GPNode << endl;
        GPNode->color = COLOR_RED;
    
        //(uncleNode == nullptr || uncleNode->color == COLOR_BLACK){ //if uncle is black and nullptr counts as black 
        //nullptr should also count as black

        //parentNode ->color = COLOR_BLACK;//change oarent and uncle to black
        //uncleNode->color = COLOR_BLACK;
        //GPNode -> color = COLOR_RED; //change gp to red (below...with check)
        //cout << "Uncle is null or black" << endl;


        
        if(IsLeftChild(newNode) && IsLeftChild(parentNode)){
            //cout << "new node is left child and parent node is left child" << endl;
            RightRotate(GPNode);
            parentNode->color = COLOR_BLACK;
        }
        else if(IsRightChild(newNode)&&IsRightChild(parentNode)){
            //cout << "new node is right child and parent node is right child" << endl;
            LeftRotate(GPNode);
            parentNode->color = COLOR_BLACK;
        }
        else if(IsLeftChild(newNode)&&IsRightChild(parentNode)){
            //cout << "new node is left child, parent  node is right child" << endl;
            RightRotate(parentNode);
            LeftRotate(GPNode);
            newNode->color = COLOR_BLACK;
            parentNode->color = COLOR_RED;
        }
        else if(IsRightChild(newNode) && IsLeftChild(parentNode)){
            //cout << " new node is right child, parent node is left child." <<endl;
            LeftRotate(parentNode);
            //cout << "left rotate completed" << endl;
            //cout << "printing root: " << root << endl;
            RightRotate(GPNode);
            //cout << "right rotate completed " << endl;
            //cout << "printing root: " << root << endl;
            newNode->color = COLOR_BLACK;
            //cout << newNode->color << endl; //complete and correct
            parentNode->color = COLOR_RED;
            //cout << parentNode->color << endl; //complete and correct
        }
        else{
            throw invalid_argument("impossible state!");
        }
    }

}
}/*
    else if(uncleNode != nullptr && uncleNode->color == COLOR_RED){
        //for when uncle is red
        cout << "IN THE ELSE IF CONDIITON" << endl;
        parentNode->color = COLOR_BLACK;
        uncleNode ->color = COLOR_BLACK;

        if(GPNode != nullptr){
            //GPNode ->color = COLOR_RED;
    
         if(root!=GPNode){
            GPNode ->color = COLOR_RED;
                if(GPNode->parent != nullptr){
                    if(GPNode ->parent->color == COLOR_RED){
                    //cout << "Inserting node: " + newNode->data << ", Parent: " <<  newNode ->parent->data << endl; 
                    InsertFixUp(GPNode);//recall
                    }
                }
            }
            
            }}
        root->color = COLOR_BLACK;
        }
    }
        */

    


/*
void RedBlackTree::LeftRotate(RBTNode *n){
    //find the parent, right child and right left grand child?
    RBTNode *parentNode = n->parent;
    RBTNode *rightChild = n->right;
    RBTNode *rlGrandChild = n->right->left;

    //if n is left child 
    if(parentNode->left == n){
        parentNode->left = rightChild;
    }
    //if parent node is right child
    else if (parentNode ->right == n){
        parentNode ->right = rightChild;
    }
    else{
        //must be the root if its not a child on either side 
        //so then the root
        root = rightChild;
    }
    rightChild ->parent = n->parent;

}
*/
bool RedBlackTree::IsLeftChild(RBTNode *node) const{
    //check if node is = to parent->left
    bool IsLeftChildReturn = false;
    if(node == node->parent->left && node != nullptr){
        IsLeftChildReturn = true;
    }
    return IsLeftChildReturn;

}
bool RedBlackTree::IsRightChild(RBTNode *node) const{
    bool IsRightChildReturn = false;
    if(node == node->parent->right && node != nullptr){
        IsRightChildReturn = true;
    }
    return IsRightChildReturn;
}
		
void RedBlackTree::LeftRotate(RBTNode *node){
    RBTNode *rightChild = node->right; //define right child because it;s gonna be the root eventually
    node->right = rightChild->left;//move the left subtree of the right child (now rightChild) to be the rightchild of current node
    if(rightChild->left != nullptr){
        rightChild->left->parent = node; //change the parent if there is a left rightChild
    }
    rightChild->parent = node->parent;

    if(node->parent == nullptr){
        root = rightChild;
    }
    else if(node==node->parent->left){
        node->parent->left = rightChild;
    }
    else{
        node->parent->right = rightChild;
    }
    rightChild->left = node;
    node->parent =rightChild;

}
    //finally make node the left child of the node->right (rotated to the left)
    //order of steps: trial and error 
    


void RedBlackTree::RightRotate(RBTNode *node){
    if(node == nullptr || node->left == nullptr){
        return;
    }
    RBTNode *leftChild = node->left;

    node ->left = leftChild->right;
    if(leftChild ->right != nullptr){
        leftChild ->right->parent = node;
    }

    leftChild ->parent = node ->parent;
    if(node ->parent == nullptr){
        root = leftChild;
        //root->color = COLOR_BLACK;
        //cout << "check in right rotate root color: " << root->color << endl; //color was changed to black! 
    }
    else if(node == node->parent->left){
        node->parent->left = leftChild;
    }
    else{
        node->parent->right = leftChild;
    }

    leftChild ->right = node;
    node->parent = leftChild;

}

int RedBlackTree::GetMin()const{
    //smallest int is the one most towards the left
    //start at root and traverse until null then when you get to where the next one is null its the one before
    RBTNode * leftmostNode = root;
    //may need to add  a catch invalid argyment 
    while(leftmostNode ->left != nullptr){
        leftmostNode = leftmostNode->left;
    }
    return leftmostNode->data;
    

}
bool RedBlackTree::Contains(int data) const{
    //bool doesContain =false;
    //start at root and move left or right based on whetehr data is bigger or smaller
    //if you hit nullptr without finding it then it shiuld stay false
    RBTNode* currentNode = root;
    while(currentNode != nullptr){
        //cout<< "running" <<endl;
        if(data == currentNode->data){ //gives int? or address
            return true;
        }
        else if(data < currentNode ->data){
            currentNode = currentNode->left;
        }
        else{
            currentNode = currentNode ->right;
        }
    }
    return false;

}
size_t RedBlackTree::Size() const{
    return numItems;
}


int RedBlackTree::GetMax() const{
    //same as min but get the one all tbe way to the right
    RBTNode *rightmostNode = root;
    //maybe need to catch an invalid argument??
    while(rightmostNode ->right != nullptr){
        rightmostNode = rightmostNode->right;
    }
    return rightmostNode->data;
}

RBTNode* RedBlackTree::Get(int data) const{
    //just return the node associated with the data?
    //start at root 
    RBTNode* currNode = root;
    while(currNode!=nullptr){
        if(data == currNode->data){
            return currNode;
        }
        else if(data<currNode->data){
            currNode= currNode->left; //explore to the left
        }
        else{
            currNode=currNode->right;
        }


    }
    return nullptr; //if not round 
}

//test get
/*
void TestsInFile(){
    RedBlackTree *rbt = new RedBlackTree();

	rbt = new RedBlackTree();
	rbt->Insert(1);
	rbt->Insert(2);
	rbt->Insert(3);
	
    //assert(RedBlackTree::IsLeftChild(1)==true);
    //assert(IsRightChild(3) == true);

}
*/
