#include <iostream>
#include <vector>
#include <ctime>
#include <set>
#include <unordered_map>

// This class is an abstraction of a weighted undirected graph
// The adjacency list representation is used

class Graph
{
  
  private:
    std::vector<std::vector<std::pair<int,int>>> adjacency_; // Adjacency list: the pair holds (destination vertex,path cost)
    int edge_count_;

  public:
    // Construct Randomized Graph
    Graph(const int vertex_count,const int probability,const int max_distance)
    {
      adjacency_.resize(vertex_count); 
      for (int i=0;i<vertex_count;i++)
        for (int j=0;j<vertex_count;j++)
          if (i == j)
            continue;
          else if(std::rand()%100 < probability/2) // This loop will consider every possible edge twice, so dividing PROB by 2
          {
            int w = 1 + std::rand()%max_distance;
            this->add(i,j,w);
          }
    }
    
    // Overload << for graph printing
    friend std::ostream& operator<<(std::ostream& os, const Graph& g);
   
    // Test if two vertexes are adjacent
    bool adjacent(const int x, const int y)
    {
      for (auto p : adjacency_[x])
        if (p.first == y)
          return true;
      return false;
    }

    // Add an edge if it doesn't already exist
    int add(int x,int y,int w=0)
    {
      if (!adjacent(x,y))
      {
        adjacency_[x].push_back(std::make_pair(y,w)); // Since this is undirected, we need to make the connection in both directions
        adjacency_[y].push_back(std::make_pair(x,w));
        edge_count_ += 1;
      }
      return 0;
    }

  // Dijkstas
  // Get the shortest paths from vertex x,
  // To all other vertexes
  // Result will be in array... where array[y] represents
  // the shortest distance from x -> y
  std::vector<int> get_shortest_paths(int x)
  {
    std::vector<int> result(adjacency_.size(),-1); // Initialize all results to -1, indicating infinite distance
 
    std::set<std::pair<int,int>> open_set; // This is a self-balancing binary tree, it will maintain the open set in sorted order 
   
    std::unordered_map<int,int> closed_map; // This is a hashmap, mapping a given vertex to its shortest distance from the source

    // Add source vertex to open set (Simplifies code)
    open_set.insert(std::make_pair(0,x));
   
    while (open_set.size() > 0)
    {
      // Pick vertex n of least cost
      std::pair<int,int> p = *open_set.begin();
      int n = p.second;
      int n_cost = p.first;

      // Add this vertex to closed set
      closed_map[n] = n_cost;

      // Remove this vertex from open set
      open_set.erase(open_set.begin());

      // Examine each of vertex n's k neighbors
      for (auto edge : adjacency_[n])
      {
        int k = edge.first;
        int k_cost = n_cost + edge.second;
        if (closed_map.find(k) == closed_map.end()) // if k is not in the closed set
        {
          // Look for this neighbor in the open set
          auto osIt = open_set.begin();
          while (osIt != open_set.end())
            if ((*osIt).second == k) // Found neighbor in open set
              break;
            else
              osIt++;
          
          if (osIt != open_set.end() && k_cost < (*osIt).first) // if k is in the open set, and the new cost is less than the known cost
          {
            open_set.erase(osIt);
            open_set.insert(std::make_pair(k_cost,k)); // Update the path with the new shorter route
          }
          else if (osIt == open_set.end()) // if k is not in the open set, add it
            open_set.insert(std::make_pair(k_cost,k));
        }
      }
    }

    // For the paths we know of, update their shortest paths in the result table
    for (int i=0;i<result.size();i++)
      if (closed_map.find(i) != closed_map.end())
        result[i] = closed_map[i];
    
    return result;
  }
};

std::ostream& operator<< (std::ostream& os,const Graph& graph)
{
  os << "===========================" << std::endl;
  os << "Graph Properties:" << std::endl;
  os << "Number of vertexes: " << graph.adjacency_.size() << std::endl;
  os << "Number of edges: " << graph.edge_count_ << std::endl;
  for (int vertex=0;vertex<graph.adjacency_.size();vertex++)
  {
    os << "vertex(" << vertex << "): ";
    for (int edge=0;edge<graph.adjacency_[vertex].size();edge++)
      os << "(" << graph.adjacency_[vertex][edge].first << "," << graph.adjacency_[vertex][edge].second << "), ";
    os << std::endl;
  }
  os << "===========================" << std::endl;
  return os;
}


const bool DEBUG = false;
const int VERTEX_COUNT = 50;
const int MAXIMUM_DISTANCE = 10;

int main ()
{

  std::srand(std::clock()); 
  
  for (int g=1;g<3;g++)
  {
    Graph graph(VERTEX_COUNT,g*20,MAXIMUM_DISTANCE);

    std::cout << graph << std::endl;

    std::vector<int> result = graph.get_shortest_paths(0);

    if (DEBUG)
      for (int i=0;i<result.size();i++)
        std::cout << "From: " << 0 << " To: " << i << " Shortest Path is: " << result[i] << std::endl;

    int valid = 0;
    int sum = 0;
    for (int i=0;i<result.size();i++)
      if (result[i] > -1)
      {
        valid += 1;
        sum += result[i];
      }

    std::cout << "Graph: " << g << " has average shortest path as: " << static_cast<double>(sum)/valid << std::endl;
  }
  
  return 0;
}
