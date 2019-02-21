#include<string>
#include<iostream>

using namespace std;

struct tNode 
{
    int data;
    struct tNode* left;
    struct tNode* right;
};

enum class TraversalType { InOrder, preOrder };

struct tNode* newtNode(int data)
{
    struct tNode* node = new tNode;
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    return (node);
}

void MorrisInOrderTraversal(struct tNode* root, const TraversalType& type)
{
    if(root==NULL)
      return;
  
    tNode* current, *pre;
    current=root;
  
    while(current!=NULL)
    {
        if(current->left == NULL)
        {
          cout << current->data << endl;
          current=current->right;          
        }
      else
      {
         pre=current->left;
         while(pre->right != NULL && pre->right != current)
           pre=pre->right;
        
        if(pre->right == NULL)
        {
           pre->right=current;
           if(type == TraversalType::preOrder)
              cout << current->data << endl;
           current=current->left;          
        }
        else
        {
          pre->right=NULL;
          if(type == TraversalType::InOrder)
            cout << current->data << endl;
          current=current->right;          
        }
      }
    }
}

//This is Post Order :children before node( L ,R , N)
void morrisPostorderTraversal(tNode *root)
{

// Making our tree left subtree of a dummy Node
struct tNode* dummyRoot = newtNode(0);
dummyRoot->left = root;

//Think of P as the current node 
struct tNode *p = dummyRoot, *pred, *first, *middle, *last;
while(p!=NULL){        

    if(p->left == NULL){
        p = p->right;
    } else{
        /* p has a left child => it also has a predeccessor
           make p as right child predeccessor of p    
        */
        pred = p->left;
        while(pred->right!=NULL && pred->right != p){
            pred = pred->right;
        }

        if(pred->right == NULL){ 

            // predeccessor found for first time
            // modify the tree

            pred->right = p;    
            p = p->left;

        }else {                          

           // predeccessor found second time
           // reverse the right references in chain from pred to p
            first = p;
            middle = p->left;              
            while(middle!=p){            
                last = middle->right;
                middle->right = first;
                first = middle;
                middle = last;
            }

            // visit the nodes from pred to p
            // again reverse the right references from pred to p    
            first = p;
            middle = pred;
            while(middle!=p){

                cout<<" "<<middle->data;  
                last = middle->right;          
                middle->right = first;
                first = middle;
                middle = last;
            }

            // remove the pred to node reference to restore the tree structure
            pred->right = NULL;    
            p = p-> right;
        }
    }
}    
}
 
int main(int argc, char* argv[])
{
    struct tNode* root = newtNode(1);
    root->left = newtNode(2);
    root->right = newtNode(3);
    root->left->left = newtNode(4);
    root->left->right = newtNode(5);
    MorrisInOrderTraversal(root, TraversalType::preOrder);
    morrisPostorderTraversal(root);
    return 0;
}

