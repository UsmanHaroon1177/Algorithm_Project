/* Name: Usman Haroon
   Roll No: 22i-1177
   Name: Hussain Mehmood
   Roll NO: 22i-1706
   ALGO CY(D)
   Submitted to Maam Amina Siddique
   ALGO PROJECT
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <queue>
#include <climits>
using namespace std;

// Read the graph from a file and create an adjacency list
unordered_map<int, vector<pair<int, int>>> readGraph(const string& filePath)
{
    unordered_map<int, vector<pair<int, int>>> adjacencyList;
    ifstream file(filePath);
    string line;

    if (!file.is_open())
    {
        cerr << "Error: Unable to open file " << filePath << endl;
        exit(1);
    }
    // Reads file 
    while (getline(file, line))
    {
        stringstream ss(line);
        int node1, node2, weight;
        ss >> node1 >> node2 >> weight;
        // undireceted Graph
        adjacencyList[node1].push_back({ node2, weight });
        adjacencyList[node2].push_back({ node1, weight });
    }

    return adjacencyList;
}

// Dijkstra's find the shortest path and distance 
void dijkstra(int source, int destination, unordered_map<int, vector<pair<int, int>>>& adjList)
{
    unordered_map<int, int> distances;
    unordered_map<int, int> previous;
    // Intilize all the nodes with infinity 
    for (auto& entry : adjList)
    {
        distances[entry.first] = INT_MAX;
        previous[entry.first] = -1;
    }
    // Source node is equal to 0
    distances[source] = 0;

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
    pq.push({ 0, source });
    // As piority Queue is created and source node is pushed into it
    while (!pq.empty())
    {
        pair<int, int> topElement = pq.top();
        // Select smaalest node aslo known as current node
        int currentDistance = topElement.first;
        int currentNode = topElement.second;
        pq.pop();
        // Checks if distance is optimal or not
        if (currentDistance > distances[currentNode]) continue;
        // Explores the neighbouring node
        for (auto& neighbor : adjList[currentNode])
        {
            int neighborNode = neighbor.first;
            int weight = neighbor.second;
            // If shortest path is found it updates the distance
            int newDist = currentDistance + weight;
            if (newDist < distances[neighborNode])
            {
                distances[neighborNode] = newDist;
                previous[neighborNode] = currentNode;
                pq.push({ newDist, neighborNode });
            }
        }
    }

    // Reconstruct the shortest path from source to destination
    vector<int> path;
    int currentNode = destination;
    // Traverse back from destination to source 
    while (currentNode != -1)
    {
        path.push_back(currentNode);
        currentNode = previous[currentNode];
    }
    // Then reverses it
    reverse(path.begin(), path.end());

    // Output the shortest distance and path
    cout << "Shortest Path from Node " << source << " to Node " << destination << ":\n";
    // Prints result
    if (distances[destination] == INT_MAX)
    {
        cout << "No path exists!\n";
    }
    else
    {
        cout << "Distance: " << distances[destination] << endl;
        cout << "Path: ";
        for (int node : path)
        {
            cout << node << " -> ";
        }
        cout << "END\n";
    }
}

// Main Function
int main() {
    string graphFile = "social-network-proj-graph.txt";

    // Load the graph
    auto graphWithWeights = readGraph(graphFile);

    // Get user input for start and end nodes
    int startNode, endNode;
    cout << "Enter the start node: ";
    cin >> startNode;
    cout << "Enter the end node: ";
    cin >> endNode;

    // Part 1: Shortest Path (Dijkstra)
    cout << "\n--------------Part 1: Shortest Path (Dijkstra)--------------\n";
    dijkstra(startNode, endNode, graphWithWeights);

    return 0;
}