#include <iostream>

//const int nullptr = 0; // In the future this should be known to compiler

template <class T>
class node
{
  public:
    T item;     // Item in list
    node* next; // Pointer to next node
    node() = delete; // No one can use w/o compiler error
    node(T item){this->item = item;this->next = nullptr;}
    ~node(){std::cout << "Node destructor called" << std::endl;}
}; 

template <class T>
class list
{

  node<T>* head; // private by default

  public:
   
    // Default Constructor
    list() {head = nullptr;}

    // Destructor
    ~list()
    {
      node<T>* cursor = head; // Start off pointing @ head
      node<T>* next_cursor; // Next cursor
     
      std::cout << "Destructor called" << std::endl;

      if(cursor == nullptr) // If the list is empty, return
      {
        return;
      }
      else {
        while(cursor!=nullptr)
        {
          std::cout << "Deleting node" << std::endl;
          next_cursor = cursor->next;
          delete cursor;
          cursor = next_cursor;
        }
      }
    }

    // Insert element at the end of the list
    void append(T item)
    {
      node<T>* cursor = head; // Start off pointing @ head
      if(cursor == nullptr) // If the list is empty, initialize
      {
        std::cout << "Allocating from empty" << std::endl; 
        head = new node<T>(item);
      }
      else
      {  
        while(cursor->next != nullptr) // Traverse the list to the last item
        {
          cursor = cursor->next;
        }
        std::cout << "Allocating later" << std::endl; 
        cursor->next = new node<T>(item);
      }
      return;
    }
    
    // Print the list
    void print()
    {
      node<T>* cursor = head; // Start off pointing @ head
      if(cursor == nullptr) // If the list is empty, initialize
      {
        std::cout << "The list is empty!" << std::endl;
      }
      else
      {  
        while(cursor != nullptr) // Traverse the list to the last item
        {
          std::cout << cursor->item << " -> ";
          cursor = cursor->next;
        }
        std::cout << "NULL" << std::endl;
      }
      return;
    }
};

int main ()
{

  int val;  // Variable to hold data

  list <int> mylist;

  mylist.append(10);
  mylist.append(20);
  mylist.append(30);

  mylist.print();

  return 0;

}
