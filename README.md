# Algorithm_Project
# Social Network Analysis – Design and Analysis of Algorithms (Fall 2024)

This project is part of **CS-2009 Design and Analysis of Algorithms**
  

The project analyzes a social network dataset using graph algorithms and dynamic programming techniques.  

---

## 📂 Project Structure
- **Part 1 – Graph-Based (Shortest Path)**
  - Construct an **undirected weighted graph** from the dataset.
  - Implement:
    - **Dijkstra’s Algorithm** (baseline solution).
    - **A\*** Algorithm (bonus) using heuristic:  
      `h(n) = number of direct connections (neighbors) of user n`.
  - Compute shortest paths between users.

- **Part 2 – Dynamic Programming on Graph (Influence Analysis)**
  - Each user has an **influence score**.
  - Find the **longest increasing chain of influence** such that each next user has a strictly greater influence score.
  - Return:
    - Maximum chain length.
    - Sequence of users forming this chain.

---

## 📊 Dataset
The dataset contains two files:
1. **Connections File**  
   Format:  
- `user1`, `user2` → users in the network.  
- `weight` → distance (lower = stronger connection).

---

## 🚀 Features
- Build undirected weighted graph from dataset.
- Efficient shortest path search using **Dijkstra** and **A\***.
- Heuristic-driven A\* implementation for performance bonus.
- Dynamic programming solution for **longest influence chain**.
- Outputs:
- Shortest path distance + path reconstruction.
- Maximum influence chain length + sequence of users.

---

## ⚙️ Implementation Details
- **Language:** C++ (mandatory).  
- **Files:**
- `part1.cpp` → Graph creation + Dijkstra/A\* shortest path.
- `part2.cpp` → Dynamic programming solution for longest influence chain.
- **Report:**  
- PDF including:
 - Pseudocode for each algorithm.
 - Asymptotic time complexity analysis.

---

## 📌 Usage
### Compile
```bash
g++ part1.cpp -o part1
g++ part2.cpp -o part2

