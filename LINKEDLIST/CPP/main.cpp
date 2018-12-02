#include <iostream>

//const int nullptr = 0; // In the future this should be known to compiler

template <class T>
struct node
{
  T item;     // Item in list
  node* next; // Pointer to next node
  
  // Constructor takes args 
  node(T item){this->item = item;this->next = nullptr;}
  node(T item,node<T>* next){this->item = item;this->next = next;}
  node() = delete; // No one can use w/o compiler error
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
     
      if(cursor == nullptr) // If the list is empty, return
      {
        return;
      }
      else {
        while(cursor!=nullptr)
        {
          next_cursor = cursor->next; // Save next pointer before deleting the node
          delete cursor;
          cursor = next_cursor;
        }
      }
    }

    // Append element at the end of the list
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
   
    // Insert element at the head of list
    void insert(T item)
    {
      head = new node<T>(item,head);
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

  list <int> mylist;

  mylist.insert(1);
  mylist.insert(10);
  mylist.insert(20);
  mylist.insert(30);
  mylist.append(0);

  mylist.print();

  return 0;

}
