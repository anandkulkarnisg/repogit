#include<iostream> 
#include<string>
#include<vector>
#include<unordered_set>
#include<algorithm>

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

void isCompleteInternal(const Node* node, int& violation)
{
  if(node==nullptr)
    return;    
  if(node->left==nullptr && node->right!=nullptr)
  {
    ++violation;
    return;
  }    
  if(node->left)
    isCompleteInternal(node->left, violation);
  if(node->right)
    isCompleteInternal(node->right, violation);  
}

bool isComplete(const Node* node)
{
  int violation=0;
  isCompleteInternal(node, violation);
  return(violation==0);
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
    isPerfectInternal(node->left, violation, hashSet, ++currentLevel);
  if(node->right)
    isPerfectInternal(node->right, violation, hashSet, ++currentLevel);
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
  displayNodeInfo(node, leftSubTreeHeight, rightSubTreeHeight, heightDiff);

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

int main(int argc, char* argv[]) 
{ 
  Node* root=newNode(1); 
  root->left=newNode(2); 
  root->right=newNode(3); 
  root->left->left=newNode(4); 
  root->left->left->left=newNode(5); 
  
  if(isBalanced(root))
    cout<<"Yes it is a Balanced binaryTree"<<endl;
  else
    cout<<"No it is not a Balanced binaryTree"<<endl;
  return(0); 
}
