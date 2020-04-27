#include <iostream>
#include <vector>
#include <unordered_set>
#include <stack>

enum class Color : short {RED,WHITE,BLUE}; 

// Graph Data Structure 
// Implemented as Adjacency list
class Graph
{
  public:
    
    // Construct Graph by resizing the neighbors to vertexCount
    Graph (int vertexCount) {neighbors_.resize(vertexCount);}
    
    // Method to create an edge from src, to dst
    // Note, for undirected graph, caller must ensure to call this twice (a,b) and (b,a)
    void addEdge (int src, int dst) {neighbors_[src].push_back(dst);}
   
    // Check if there is a path from src to dst
    bool isConnected (int src, int dst) const
    {
      for (const auto& n : neighbors_[src])
        if (n == dst)
          return true;
      return false;
    }

    // Return the neighbors who are adjacent to src
    std::vector<int> getNeighbors(int src) {return neighbors_[src];}

    // Overload << to print Graph
    friend std::ostream& operator<<(std::ostream& os, const Graph& graph);

  private:
    std::vector<std::vector<int>> neighbors_; // The Graph
};

// Overload << to print Graph, will print each vertex, and its neighbors
std::ostream& operator<< (std::ostream& os,const Graph& graph)
{
  for (int v=0;v<graph.neighbors_.size();++v)
  {
    os << "v: " << v << " -> ";
    for (const auto& n : graph.neighbors_[v])
      os << n << ", ";
    os << std::endl;
  }
  
  return os;
}

// This class will be an abstraction of the HEX game board
// It will be primarily composed of an instance of class Graph
// Additionally, it will construct  a baord of shape EXPANSExEXPANSE
// This class will provide methods for players to place a stone
// This class will provide a method to check if a given player has won
class Board
{

  public:

    // Construct a Board of size expanse by expanse
    // Positions in the board will have an (i,j) coordinate
    // Spanning from (0,0) to (expanse-1,expanse-1)
    // These coordinates will be converted to an offset in the graph's
    // adjacency list, by the m2k function (map i,j to k)
    // This function must take care of the corner cases of the board
    // But will connect most positions to 6 neighboring hexagons
    Board(int expanse) : graph_(expanse*expanse),expanse_(expanse) 
    {
      
      colors_.resize(expanse*expanse,Color::WHITE); // Initially all positions will be white or uncolored
      
      for (int i=0;i<expanse;++i)
        for (int j=0;j<expanse;++j)
        {
          // Upper Left Corner
          if ((i == 0) && (j == 0))
          {
            graph_.addEdge(m2k(i,j),m2k(i+1,j));
            graph_.addEdge(m2k(i,j),m2k(i,j+1));
          }
          // Lower Left Corner
          else if ((i == (expanse - 1)) && (j == 0))
          {
            graph_.addEdge(m2k(i,j),m2k(i,j+1));
            graph_.addEdge(m2k(i,j),m2k(i-1,j));
            graph_.addEdge(m2k(i,j),m2k(i-1,j+1));
          }
          // Lower Right Corner
          else if ((i == (expanse -1)) && (j == (expanse -1)))
          {
            graph_.addEdge(m2k(i,j),m2k(i-1,j));
            graph_.addEdge(m2k(i,j),m2k(i,j-1));
          }
          // Upper Right Corner
          else if ((i == 0) && (j == (expanse-1)))
          {
            graph_.addEdge(m2k(i,j),m2k(i+1,j));
            graph_.addEdge(m2k(i,j),m2k(i,j-1));
            graph_.addEdge(m2k(i,j),m2k(i+1,j-1));
          }
          // Upper Row
          else if (i == 0)
          {
            graph_.addEdge(m2k(i,j),m2k(i,j-1));
            graph_.addEdge(m2k(i,j),m2k(i,j+1));
            graph_.addEdge(m2k(i,j),m2k(i+1,j));
            graph_.addEdge(m2k(i,j),m2k(i+1,j-1));
          }
          // Lower Row
          else if (i == (expanse - 1))
          {
            graph_.addEdge(m2k(i,j),m2k(i,j-1));
            graph_.addEdge(m2k(i,j),m2k(i,j+1));
            graph_.addEdge(m2k(i,j),m2k(i-1,j));
            graph_.addEdge(m2k(i,j),m2k(i-1,j+1));
          }
          // Left Column
          else if (j == 0)
          {
            graph_.addEdge(m2k(i,j),m2k(i,j+1));
            graph_.addEdge(m2k(i,j),m2k(i-1,j));
            graph_.addEdge(m2k(i,j),m2k(i-1,j+1));
            graph_.addEdge(m2k(i,j),m2k(i+1,j));
          }
          // Right Column
          else if (j == (expanse - 1))
          {
            graph_.addEdge(m2k(i,j),m2k(i,j-1));
            graph_.addEdge(m2k(i,j),m2k(i-1,j));
            graph_.addEdge(m2k(i,j),m2k(i+1,j));
            graph_.addEdge(m2k(i,j),m2k(i+1,j-1));
          }
          // Middle nodes connect to 6 neighbors 
          else 
          {
            graph_.addEdge(m2k(i,j),m2k(i,j-1));
            graph_.addEdge(m2k(i,j),m2k(i,j+1));
            graph_.addEdge(m2k(i,j),m2k(i-1,j));
            graph_.addEdge(m2k(i,j),m2k(i-1,j+1));
            graph_.addEdge(m2k(i,j),m2k(i+1,j));
            graph_.addEdge(m2k(i,j),m2k(i+1,j-1));
          }
        }
    }

    // Place a stone of a chosen color at a given position
    // Return -1 if the move is illegal
    int placeStone (int i, int j, Color color) 
    {
      if (i < 0 || j < 0 || i >= expanse_ || j >= expanse_ || colors_[m2k(i,j)] != Color::WHITE)
        return -1;
      else
        colors_[m2k(i,j)] = color;
      return 0;
    }

    // Determine if a given player (Red or Blue player) has won the game
    // This is essentially a multisource , multidestination DFS, if a path is
    // found, someone won the game
    bool won (Color color) 
    {
      
      std::unordered_set<int> targets; // Nodes we are looking for
      std::unordered_set<int> visited; // Nodes we have visited
      std::stack<int> stack; // Stack for DFS

      // Red wins if they make it from North (i = 0) to South (i = expanse-1)
      if (color == Color::RED)
      {
        // Initialize the stack
        for (int j=0;j<expanse_;++j)
          if (colors_[m2k(0,j)] == color)
            stack.push(m2k(0,j));
        
        // Define the nodes we are looking for
        for (int j=0;j<expanse_;++j)
          if (colors_[m2k(expanse_-1,j)] == color)
            targets.insert(m2k(expanse_-1,j));
      }
      // Blue wins if they make it from East (j = expanse-1) To West (j = 0)
      else if (color == Color::BLUE)
      {
        // Initialize the stack
        for (int i=0;i<expanse_;++i)
          if (colors_[m2k(i,expanse_-1)] == color)
            stack.push(m2k(i,expanse_-1));
        
        // Define the nodes we are looking for
        for (int i=0;i<expanse_;++i)
          if (colors_[m2k(i,0)] == color)
            targets.insert(m2k(i,0));
      }
     
      // If we have no possible target, quit early
      if (targets.size() < 1)
        return false;

      while (!stack.empty())
      {
      
        int vertex = stack.top(); 
        stack.pop();

        visited.insert(vertex);

        if (colors_[vertex] == color && targets.find(vertex) != targets.end())
          return true;

        //for (int& neighbor : graph_.neighbors_[vertex])
        for (int& neighbor : graph_.getNeighbors(vertex))
          if (colors_[neighbor] == color && visited.find(neighbor) == visited.end())
            stack.push(neighbor);
      }

      return false; // No path found, return false
    }
    
    // Overload << to print Board
    friend std::ostream& operator<<(std::ostream& os, const Board& board);

  private:
    Graph graph_;
    int expanse_;
    std::vector<Color> colors_; // Maintain state/color of every vertex
   
    // Utilities to convert between 2D and 1D coordinates
    int m2k(int i,int j) const {return i*expanse_ + j;}
    int m2i(int k) const {return k/expanse_;}
    int m2j(int k) const {return k%expanse_;}

};

// Overload << to print Board as ASCII
// an O is printed for open positions
// an R is printed for red positions
// a  B is printed for blue positions
std::ostream& operator<< (std::ostream& os,const Board& board)
{
  for (int i=0;i<board.expanse_;++i)
  {
    for (int s=0;s<i;++s)
      os << "  ";
    for (int j=0;j<board.expanse_;++j)
    {
      if (board.colors_[board.m2k(i,j)] == Color::RED)
        os << "R";
      if (board.colors_[board.m2k(i,j)] == Color::WHITE)
        os << "O";
      if (board.colors_[board.m2k(i,j)] == Color::BLUE)
        os << "B";
      if (j < board.expanse_ - 1 && board.graph_.isConnected(board.m2k(i,j),board.m2k(i,j+1)))
        os << "---";
    }
    os << std::endl << " ";
    for (int s=0;s<i;++s)
      os << "  ";
    for (int j=0;j<board.expanse_;++j)
    {
      int l = (i+1)*board.expanse_ + j;
      if (j < board.expanse_  && board.graph_.isConnected(board.m2k(i,j),board.m2k(i+1,j)))
        os << "\\";
      else
        os << " ";
      os << " ";
      if ((i+1) < board.expanse_ && j < board.expanse_ - 1  && board.graph_.isConnected(board.m2k(i+1,j),board.m2k(i,j+1)))
        os << "/";
      else
        os << " ";
      os << " ";
    }
    os << std::endl;
  }
  return os;
}

int main ()
{

  Board board(11);

  board.placeStone(0,4,Color::RED);
  board.placeStone(1,4,Color::RED);
  board.placeStone(2,4,Color::RED);
  board.placeStone(3,4,Color::RED);
  board.placeStone(4,4,Color::RED);
  //board.placeStone(5,4,Color::RED);
  board.placeStone(6,4,Color::RED);
  board.placeStone(7,4,Color::RED);
  board.placeStone(8,4,Color::RED);
  board.placeStone(9,4,Color::RED);
  board.placeStone(10,4,Color::RED);

  board.placeStone(5,0,Color::BLUE);
  board.placeStone(5,1,Color::BLUE);
  board.placeStone(5,2,Color::BLUE);
  board.placeStone(5,3,Color::BLUE);
  board.placeStone(5,4,Color::BLUE);
  board.placeStone(5,5,Color::BLUE);
  board.placeStone(5,6,Color::BLUE);
  board.placeStone(5,7,Color::BLUE);
  board.placeStone(5,8,Color::BLUE);
  board.placeStone(5,9,Color::BLUE);
  board.placeStone(5,10,Color::BLUE);
  
  bool redWins = board.won(Color::RED);
  std::cout <<  redWins << std::endl;

  bool blueWins = board.won(Color::BLUE);
  std::cout <<  blueWins << std::endl;
  
  std::cout << std::endl << board << std::endl;

  return 0;

}
