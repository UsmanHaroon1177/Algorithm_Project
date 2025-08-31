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
#include <vector>
#include <unordered_map>
#include <queue>
#include <algorithm>
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
    // Read from all over the file
    while (getline(file, line))
    {
        stringstream ss(line);
        int node1, node2, weight;
        ss >> node1 >> node2 >> weight;

        // For undirected graph
        adjacencyList[node1].push_back({ node2, weight });
        adjacencyList[node2].push_back({ node1, weight });
    }

    return adjacencyList;
}

// Read influence scores from a file
unordered_map<int, int> readInfluences(const string& filePath)
{
    unordered_map<int, int> influences;
    ifstream file(filePath);
    string line;
    // Error if not opened
    if (!file.is_open())
    {
        cerr << "Error: Unable to open file " << filePath << endl;
        exit(1);
    }

    while (getline(file, line))
    {
        stringstream ss(line);
        int user, score;
        ss >> user >> score;

        influences[user] = score;
    }

    return influences;
}

// Recursive function with memoization to find the longest chain and track predecessors
int dfs(int node, const unordered_map<int, vector<int>>& graph,
    const unordered_map<int, int>& influences, unordered_map<int, int>& memo,
    unordered_map<int, int>& predecessor)
{
    if (memo.find(node) != memo.end())
    {
        return memo[node];
    }
    // The node itself is a chain of length 1
    int maxLength = 1;
    // Explored all neighbours of current node
    for (int neighbor : graph.at(node))
    {
        // Only consider nodes with hifher influence value
        if (influences.at(neighbor) > influences.at(node))
        {
            // Recursively find Longest chain
            int currentLength = 1 + dfs(neighbor, graph, influences, memo, predecessor);
            //Finds it and update it
            if (currentLength > maxLength)
            {
                maxLength = currentLength;
                predecessor[node] = neighbor;
            }
        }
    }

    memo[node] = maxLength;
    return maxLength;
}

//Find the global longest chain of influence (Whole Graph)
int findLongestChain(const unordered_map<int, vector<int>>& graph,
    const unordered_map<int, int>& influences,
    unordered_map<int, int>& predecessor)
{
    unordered_map<int, int> memo;
    int maxChainLength = 0;

    for (const auto& entry : graph)
    {
        int node = entry.first;
        // Calls Dfs for each node
        maxChainLength = max(maxChainLength, dfs(node, graph, influences, memo, predecessor));
    }

    return maxChainLength;
}

//Reconstruct the sequence of the longest chain
vector<int> reconstructSequence(int startNode, const unordered_map<int, int>& predecessor) {
    vector<int> sequence;
    int currentNode = startNode;

    while (predecessor.find(currentNode) != predecessor.end())
    {
        sequence.push_back(currentNode);
        currentNode = predecessor.at(currentNode);
    }

    // Add the last node
    sequence.push_back(currentNode);
    reverse(sequence.begin(), sequence.end());

    return sequence;
}

// Finds the longest chain between two given nodes
int findLongestChainBetweenTwoNodes(int startNode, int endNode, const unordered_map<int, vector<int>>& graph,
    const unordered_map<int, int>& influences, unordered_map<int, int>& predecessor) {
    unordered_map<int, int> memo;

    // Get the longest chain starting from the start node
    int longestChainFromStart = dfs(startNode, graph, influences, memo, predecessor);

    // Clear memoization for the second DFS calculation
    memo.clear();

    // Get the longest chain starting from the end node
    int longestChainFromEnd = dfs(endNode, graph, influences, memo, predecessor);

    return min(longestChainFromStart, longestChainFromEnd);
}

// Main Function
int main()
{
    string graphFile = "social-network-proj-graph.txt";
    string influenceFile = "social-network-proj-Influences.txt";

    // Load the graph and influence scores
    auto graphWithWeights = readGraph(graphFile);

    // Create a simplified graph for the longest chain (no weights)
    unordered_map<int, vector<int>> graph;
    for (const auto& entry : graphWithWeights)
    {
        int node = entry.first;
        for (const auto& neighbor : entry.second)
        {
            graph[node].push_back(neighbor.first); // Add only the neighbor, ignore the weight
        }
    }

    auto influences = readInfluences(influenceFile);

    // Get user input for start and end nodes
    int startNode, endNode;
    cout << "Enter the start node: ";
    cin >> startNode;
    cout << "Enter the end node: ";
    cin >> endNode;

    // Part 2: Longest Chain of Influence
    cout << "\n--------------Part 2: Longest Chain of Influence--------------\n";
    unordered_map<int, int> predecessor;
    int longestChain = findLongestChain(graph, influences, predecessor);
    cout << "Maximum Length of Influence Chain in the Whole Graph: " << longestChain << endl;

    // Reconstruct and print the sequence for the longest chain in the graph
    vector<int> longestChainSequence = reconstructSequence(startNode, predecessor);
    cout << "Longest Chain Sequence in the Graph: ";
    for (int node : longestChainSequence) {
        cout << node << " -> ";
    }
    cout << "END" << endl;

    int longestChainBetweenTwoNodes = findLongestChainBetweenTwoNodes(startNode, endNode, graph, influences, predecessor);
    cout << "Maximum Length of Influence Chain between Nodes " << startNode << " and " << endNode << ": "
        << longestChainBetweenTwoNodes << endl;

    vector<int> longestChainBetweenTwoNodesSequence = reconstructSequence(startNode, predecessor);
    cout << "Longest Chain Sequence between Nodes " << startNode << " and " << endNode << ": ";
    for (int node : longestChainBetweenTwoNodesSequence) {
        cout << node << " -> ";
    }
    cout << "END" << endl;

    return 0;
}