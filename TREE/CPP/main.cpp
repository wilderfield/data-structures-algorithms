#include <iostream>

template <class T>
struct node
{
  // Data Members
  T item;     // Item in tree
  node* left; // Pointer to next node
  node* right; // Pointer to next node
 
  // Constructor requires an argument
  node(T item){this->item = item;this->left = nullptr;this->right = nullptr;}
  node() = delete; // No one can construct a node without an element
}; 

template <class T>
class tree
{
  private:
  
    node<T>* root;

    void insert(node<T>** cursor, T item)
    {
      if(*cursor == nullptr)
      {
        *cursor = new node<T>(item);
      }
      else if(item <= (*cursor)->item)
      {  
        insert(&((*cursor)->left),item);
      }
      else
      {
        insert(&((*cursor)->right),item);
      }
      return;
    }

    void print(node<T>* cursor)
    {
      if(cursor == nullptr)
      {
        std::cout << "NULL" << std::endl; 
      }
      else 
      {  
        std::cout << cursor->item << std::endl;
        print(cursor->left);
        print(cursor->right);
      }
      return;
    }

    void deleteRecursive(node<T>* cursor)
    {
      if(cursor == nullptr)
      {
        return;
      }
      else
      {
        deleteRecursive(cursor->left);
        deleteRecursive(cursor->right);
        delete cursor;
      }
      return;
    }

  public:
   
    // Default Constructor
    tree() {root = nullptr;}

    ~tree()
    {
      deleteRecursive(root);
    }

    // Insert element into tree
    void insert(T item)
    {
      insert(&root,item);
      return;
    }
    
    // Print tree
    void print()
    {
      print(root);
      return;
    }
   
};

int main ()
{

  tree <int> mytree;

  mytree.insert(10);
  mytree.insert(5);
  mytree.insert(16);
  mytree.insert(1);
  
  mytree.print();

  return 0;

}
