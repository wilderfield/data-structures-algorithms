#include <iostream>
#include <vector>

// CPP should always use vector instead of normal arrays

const int SIZE = 8;

int main ()
{

  int val;  // Variable to hold data

  // Static Array
  std::vector<int> sarray (SIZE);
  
  for(int i=0;i<SIZE;i++)
  {
    val = i*i; 
    std::cout << "Setting static array element " << i << " to " <<  val << std::endl;
    sarray[i] = val;
  }
  
  for(int i=0;i<SIZE;i++)
  {
    val = sarray[i];
    std::cout << "Getting static array element " << i << " as " <<  val << std::endl;
  }
 
  // Dynamic Array
  std::vector<int> darray;

  for(int i=0;i<SIZE;i++)
  {
    val = i+i; 
    std::cout << "Setting static array element " << i << " to " <<  val << std::endl;
    darray.push_back(val);
  }

  for(int i=0;i<SIZE;i++)
  {
    val = darray[i];
    std::cout << "Getting static array element " << i << " as " <<  val << std::endl;
  }
 
  std::cout << "No need to free or delete std::vector\n";

  return 0;

}
