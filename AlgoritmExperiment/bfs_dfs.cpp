#include <stdio.h>
#include <string>
#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>
#include <queue>

using namespace std;

// const int V = 
// vector< pair<int, int> > Adj[V];

const int inf = numeric_limits <int> :: max()/2;

int V = 1000; // at most have 1000 nodes
vector< pair<int, int> > adj[1000];
int weight[1000][1000];

void initWeight(int V) {
    for (int i = 0; i < V; ++i) {
        for (int j = 0; j < V; ++j) {
            weight[i][j] = inf;
        }
    }
    return;
}

void addEdge(int x, int y, int Weight = 1, bool directed = false) {
    adj[x].push_back(make_pair(y, Weight));
    if (directed == false) {
        adj[y].push_back(make_pair(x, Weight));
        weight[y][x] = Weight;
    } 
    weight[x][y] = Weight;
    return;
}

void DFS(int node, bool visited[]) {
    visited[node] = true;
    cout << "DFS visit node: " << node << endl;
    for (int i = 0; i < adj[node].size(); ++i) {
        if (visited[ adj[node][i].first ] == false) {
            DFS(adj[node][i].first, visited);
        }
    }
    return;
}

void BFS(int node, bool visited[]) {
    queue <int> Q;
    Q.push(node);
    cout << "BFS visit node: " << node << endl;
    visited[node] = true;
    while(!Q.empty()) {
        node = Q.front();
        Q.pop();
        for (int i = 0; i < adj[node].size(); ++i) {
            if (visited[ adj[node][i].first ] == false) {
                visited[ adj[node][i].first ] = true;
                cout << "BFS visit node: " << adj[node][i].first << endl;
                Q.push(adj[node][i].first);
            }
        }
    }
    return;
}

void BFSinit(int V) {
    bool visited[V];
    for (int i = 0; i < V; ++i) {
        visited[i] = false;
    }
    for (int i = 0; i < V; ++i) {
        if (visited[i] == false) {
            BFS(i, visited);
        }
    }
    return;
}

void DFSinit(int V) {
    bool visited[V];
    for (int i = 0; i < V; ++i) {
        visited[i] = false;
    }
    for (int i = 0; i < V; ++i) {
        if (visited[i] == false) {
            DFS(i, visited);
        }
    }
    return;
}

// minist generative tree
// void Kruskal(int V) {
//     void tree
// }


void Prim(int V, int node) {
    // init the all node
    int dis[V];
    for (int i = 0; i < V; ++i) {
        dis[i] = inf;
    }
    dis[node] = 0;
    int min_len = 0;
   
    for (int it = 0; it < V-1; ++it) {
        min_len += dis[node];
        // use the node to relax the dis
        for (int i = 0; i < V; ++i) {
            if (dis[i] > weight[node][i]) {
                dis[i] = weight[node][i];
            }
        }
        // update the dis
        dis[node] = -inf;
        // use the new_dis to find the nearst node
        int min_dis = inf;
        for (int i = 0; i < V; ++i) {
            if (dis[i] != -inf && min_dis >= dis[i]) {
                min_dis = dis[i];
                node = i;
            }
        }
        cout << "node: " << node << " dis: " << dis[node] <<  endl;      
    }
    min_len += dis[node];
    cout << "  <<<<<MinLength>>>>>" << endl;
    cout << "         " << min_len << endl;
    return;
}


int main() {
    cin >> V;
    initWeight(V);
    addEdge(0, 4, 8);
    addEdge(0, 3, 4);
    addEdge(0, 1, 5);
    addEdge(1, 2, 7);
    addEdge(4, 3, 9);
    addEdge(2, 0, 3);
    cout << "..........DFS........." << endl;
    DFSinit(V);
    cout << "..........BFS........." << endl;
    BFSinit(V);
    cout << "..........Prim........" << endl;
    Prim(V, 0);
    return 0;
}