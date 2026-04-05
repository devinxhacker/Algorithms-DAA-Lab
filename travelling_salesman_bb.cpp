#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <algorithm>

using namespace std;

struct Node {
    vector<int> path;    // visited cities in order
    vector<bool> seen;   // visited flags
    int level;           // number of cities visited
    int cost;            // cost so far
    int bound;           // lower bound estimate
    Node(int n = 0): path(), seen(n,false), level(0), cost(0), bound(0) {}
};

// Compute a simple lower bound: cost so far + (edges remaining)*minEdge
int computeBound(const Node &u, int n, const vector<vector<int>> &dist, int minEdge) {
    if (u.level == n) return u.cost;
    // remaining edges (rough estimate) = (n - u.level) + 1 (to return)
    int remEdges = (n - u.level) + 1;
    return u.cost + remEdges * minEdge;
}

// compare for priority_queue (smallest bound first)
struct Cmp {
    bool operator()(const Node &a, const Node &b) const {
        return a.bound > b.bound;
    }
};

int main() {
    int n;
    cout << "Enter number of cities: ";
    cin >> n;
    if(n <= 0) return 0;

    cout << "Enter distance matrix (n x n):\n";
    vector<vector<int>> dist(n, vector<int>(n));
    for (int i = 0; i < n; ++i){
        for (int j = 0; j < n; ++j){
            cin >> dist[i][j];
        }
    }

    // find minimum non-zero edge
    int INF = 999;
    int minEdge = INF;
    for (int i = 0; i < n; ++i){
        for (int j = 0; j < n; ++j){
            if (i != j && dist[i][j] > 0)
                minEdge = min(minEdge, dist[i][j]);
        }
    }
    if(minEdge == INF) minEdge = 0;

    // best solution
    int bestCost = INF;
    vector<int> bestPath;

    // start from city 0
    Node start(n);
    start.path.push_back(0);
    start.seen[0] = true;
    start.level = 1;
    start.cost = 0;
    start.bound = computeBound(start, n, dist, minEdge);

    priority_queue<Node, vector<Node>, Cmp> pq;
    pq.push(start);

    while (!pq.empty()) {
        Node u = pq.top(); pq.pop();

        if (u.bound >= bestCost) continue; // prune

        if (u.level == n) {
            // complete tour: add return cost to start
            int last = u.path.back();
            if (dist[last][0] > 0) {
                int total = u.cost + dist[last][0];
                if (total < bestCost) {
                    bestCost = total;
                    bestPath = u.path;
                }
            }
            continue;
        }

        int last = u.path.back();
        // branch: try all unvisited cities
        for (int v = 0; v < n; ++v) {
            if (u.seen[v]) continue;
            if (dist[last][v] <= 0) continue; // no edge

            Node child = u;
            child.path.push_back(v);
            child.seen[v] = true;
            child.level = u.level + 1;
            child.cost = u.cost + dist[last][v];
            child.bound = computeBound(child, n, dist, minEdge);

            if (child.bound < bestCost) {
                pq.push(child);
            }
        }
    }

    if (bestCost == INF) {
        cout << "No Hamiltonian tour found." << '\n';
        return 0;
    }

    // print result: cost and tour (returning to start)
    cout << "Minimum cost: " << bestCost << '\n';
    cout << "Tour: ";
    for (int x : bestPath) cout << x << " ";
    cout << 0 << '\n'; // return to start

    return 0;
}

/*
4
0 10 15 20
10 0 35 25
15 35 0 30
20 25 30 0
*/