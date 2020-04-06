#include<iostream> 
#include<string>
#include<vector>
#include<unordered_set>
#include<algorithm>
#include<climits>

using namespace std; 
struct Node 
{ 
  int key; 
  struct Node *left, *right; 
}; 

Node * newNode(int k) 
{ 
  Node *temp=new Node; 
  temp->key=k; 
  temp->left=temp->right=NULL; 
  return temp; 
} 
void isCompleteInternal(const Node* node, int& violation, unordered_set<size_t>& levelHash, size_t level=0)
{
  if(node==nullptr)
    return;    
  if(node->left==nullptr && node->right!=nullptr)
  {
    ++violation;
    return;
  }    
  if(node->left!=nullptr && node->right==nullptr)
    levelHash.insert(level); // All level must be full and incompleteness must be at same level of leaves.    
  
  if(node->left)
    isCompleteInternal(node->left, violation, levelHash, level+1);
  if(node->right)
    isCompleteInternal(node->right, violation, levelHash, level+1);  
}

bool isComplete(const Node* node)
{
  int violation=0;
  unordered_set<size_t> levelHash;
  isCompleteInternal(node, violation, levelHash);
  return(violation==0 && levelHash.size()<=1);
}

bool isLeaf(const Node* node)
{
  return(node->left==nullptr&&node->right==nullptr);
}

void isFullInternal(const Node* node, size_t& violation)
{
  if(node==nullptr)
    return;
  
  if(isLeaf(node))
    return;
  
  if(node->left==nullptr||node->right==nullptr)
  {
    ++violation;
    return;    
  }
  
  if(node->left)
    isFullInternal(node->left, violation);
  if(node->right)
    isFullInternal(node->right, violation);    
}

bool isFull(const Node* node)
{
  size_t violation=0;
  isFullInternal(node, violation);
  return(violation==0);  
}

void isPerfectInternal(const Node* node, size_t& violation, unordered_set<size_t>& hashSet, size_t currentLevel=0)
{
  if(node==nullptr)
    return;  
  if(isLeaf(node))
  {
      hashSet.insert(currentLevel);
      return;
  }  
  if(node->left==nullptr||node->right==nullptr) // both cant be since leaf is covered above.
  {
    ++violation;
    return;
  }  
  if(node->left)
    isPerfectInternal(node->left, violation, hashSet, currentLevel+1);
  if(node->right)
    isPerfectInternal(node->right, violation, hashSet, currentLevel+1);
}

// A perfect binary tree is a binary tree in which all interior nodes have two 
// children and all leaves have the same depth or same level.

bool isPerfect(const Node* node)
{
  size_t violation=0;
  unordered_set<size_t> leafLevelSet;
  isPerfectInternal(node, violation, leafLevelSet);
  return(leafLevelSet.size()==1&&violation==0);
}

void isDegenerateInternal(const Node* node, size_t& leftChildCount, size_t& rightChildCount)
{
  if(node==nullptr)
    return;
  
  if(node->left)
  {
    leftChildCount+=1;
    isDegenerateInternal(node->left, leftChildCount, rightChildCount);
  }
  
  if(node->right)
  {
    rightChildCount+=1;
    isDegenerateInternal(node->right, leftChildCount, rightChildCount);
  }
}

bool isDegenerate(const Node* node)
{
  size_t leftChildCount=0, rightChildCount=0;
  isDegenerateInternal(node, leftChildCount, rightChildCount);
  if((leftChildCount>0&&rightChildCount==0)||(rightChildCount>0&&leftChildCount==0))
    return(true);
  return(false);
}

void displayNodeInfo(const Node* node, const size_t& leftSubTreeHeight, 
                     const size_t& rightSubTreeHeight, 
                     const long& heightDiff)
{
  cout<<"At the node="<<node->key<<", The HeightDiff="<<heightDiff;
  cout<<", LeftSubtreeHeight="<<leftSubTreeHeight<<" and rightSubTreeHeight="<<rightSubTreeHeight<<endl;  
}

long isBalancedInternal(const Node* node, size_t& violation)
{ 
  long leftSubTreeHeight=0,rightSubTreeHeight=0;
  
  if(node==nullptr||isLeaf(node))
    return(0);
  
  if(node->left)
    leftSubTreeHeight=1+isBalancedInternal(node->left, violation);
  
  if(node->right)
    rightSubTreeHeight=1+isBalancedInternal(node->right, violation);
  
  long heightDiff=abs(leftSubTreeHeight-rightSubTreeHeight);
  //displayNodeInfo(node, leftSubTreeHeight, rightSubTreeHeight, heightDiff);

  if(heightDiff>1)
    ++violation;

  return(max(leftSubTreeHeight, rightSubTreeHeight));
}

bool isBalanced(const Node* node)
{
  size_t violation=0;
  isBalancedInternal(node, violation);
  return(violation==0);
}

void binaryTreeSizeInternal(const Node* node, size_t& count)
{
  if(node==nullptr)
    return;
  
  if(node->left)
  {
    ++count;
    binaryTreeSizeInternal(node->left, count);
  }
  if(node->right)
  {
    ++count;
    binaryTreeSizeInternal(node->right, count);
  }
}

size_t getBinaryTreeSize(const Node* root)
{
  if(root==nullptr)
    return(0);
  size_t count=1; // counts the root.
  binaryTreeSizeInternal(root, count);
  return(count);
}

size_t getBinaryTreeHeight(const Node* node)
{
  if(node==nullptr||isLeaf(node))
    return(0);  
  
  size_t leftSubTreeHeight=0, rightSubTreeHeight=0;
  if(node->left)
    leftSubTreeHeight=1+getBinaryTreeHeight(node->left);
  if(node->right)
    rightSubTreeHeight=1+getBinaryTreeHeight(node->right); 
  return(max(leftSubTreeHeight, rightSubTreeHeight)); 
}

Node* generateWikiBinaryTree()
{
  Node* root=newNode(1); 
  root->left=newNode(2);
  root->right=newNode(3);
 
  root->left->left=newNode(4);
  root->left->right=newNode(5);
  root->left->left->left=newNode(8);
  root->left->left->right=newNode(9);
  
  root->left->right->left=newNode(10);
  root->left->right->right=newNode(11);
  
  root->right->left=newNode(6);
  root->right->right=newNode(7);
  root->right->left->left=newNode(12); 
  return(root);
}

Node* generateLeetCodeDiameterExample()
{
  
/*
          1
         / \
        2   3
       / \     
      4   5    
*/
  
  Node* root=newNode(1);
  root->left=newNode(2);
  root->right=newNode(3);
  root->left->left=newNode(4);
  root->left->right=newNode(5);  
  return(root);
}

Node* testIsCompleteCase()
{
  Node* root=newNode(1);
  root->left=newNode(2);
  root->right=newNode(3);
  root->left->left=newNode(4);
  root->left->right=newNode(5);
  root->right->left=newNode(6);  
  root->left->left->left=newNode(7);
  root->left->right->left=newNode(8);
  //root->right->right=newNode(9);
  return(root);
}

void getBinaryTreeDiameterInternal(const Node* node, size_t& maxSize)
{
  if(node==nullptr||isLeaf(node))
    return;    
  size_t leftSubTreeHeight=0,rightSubTreeHeight=0;
  if(node->left)
    leftSubTreeHeight=1+getBinaryTreeHeight(node->left);
  if(node->right)
    rightSubTreeHeight=1+getBinaryTreeHeight(node->right); 
  
  if((leftSubTreeHeight+rightSubTreeHeight)>maxSize)
    maxSize=leftSubTreeHeight+rightSubTreeHeight;
}

size_t getBinaryTreeDiameter(const Node* node)
{
  size_t height=0;
  getBinaryTreeDiameterInternal(node, height);
  return(height);  
}

int main(int argc, char* argv[]) 
{    
  Node* root=testIsCompleteCase();
  if(isComplete(root))
    cout<<"Yes it is a Complete binaryTree"<<endl;
  else
    cout<<"No it is not a Complete binaryTree"<<endl;
  return(0);
}
