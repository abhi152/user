#include<bits/stdc++.h>
#include<omp.h>
using namespace std;

void serialDFS(vector<vector<int>>& G, int curr, vector<bool>& visited) {
    visited[curr] = 1;
    cout << curr << " ";
    for(int adj : G[curr]) {
        if(!visited[adj]) {
            visited[adj] = 1;
            serialDFS(G, adj, visited);
        }
    }
}

void parallelDFS(vector<vector<int>>& G, int curr, vector<bool>& visited) {
    visited[curr] = 1;
    cout << curr << " ";
    #pragma omp parallel for
    for(int i=0; i<G[curr].size(); i++) {
        int adj = G[curr][i];
        if(!visited[adj]) {
            visited[adj] = 1;
            parallelDFS(G, adj, visited);
        }
    }
}

void serialBFS(vector<vector<int>>& G, int start, vector<bool>& visited) {
    queue<int> q;
    q.push(start);
    visited[start] = 1;
    while(!q.empty()) {
        for(int i=0; i<q.size(); i++) {
            int curr = q.front();
            cout << curr << " ";
            q.pop();
            for(int adj : G[curr]) {
                if(!visited[adj]) {
                    visited[adj] = 1;
                    q.push(adj);
                }
            }
        }
    }
}

void parallelBFS(vector<vector<int>>& G, int start, vector<bool>& visited) {
    queue<int> q;
    q.push(start);
    visited[start] = 1;
    while(!q.empty()) {
        #pragma omp parallel for
        for(int i=0; i<q.size(); i++) {
            int curr;
            #pragma omp critical
            {
                curr = q.front();
                cout << curr << " ";
                q.pop();
            }
            for(int adj : G[curr]) {
                #pragma omp critical
                {
                    if(!visited[adj]) {
                        visited[adj] = 1;
                        q.push(adj);
                    }
                }
            }
        }
    }
}

int main() {
    int n, e;
    cin >> n >> e;
    vector<vector<int>> G(n, vector<int>());
    for(int i = 0; i < e; i++) {
        int u, v;
        cin >> u >> v;
        G[u].push_back(v);
        G[v].push_back(u);
    }
    vector<bool> visited(n, 0);
    // Serial DFS:
    double start = omp_get_wtime();
    cout << "Serial DFS: ";
    serialDFS(G, 0, visited);
    double end = omp_get_wtime();
    printf("\nSerial DFS Time: %g", end - start);
    cout << endl;

    // Parallel DFS:
    visited = vector<bool>(n, 0);
    start = omp_get_wtime();
    cout << "Parallel DFS: ";
    parallelDFS(G, 0, visited);
    end = omp_get_wtime();
    printf("\nParallel DFS Time: %g", end - start);
    cout << endl;

    // Serial DFS:
    visited = vector<bool>(n, 0);
    start = omp_get_wtime();
    cout << "Serial BFS: ";
    serialBFS(G, 0, visited);
    end = omp_get_wtime();
    printf("\nSerial BFS Time: %g", end - start);
    cout << endl;

    // Parallel DFS:
    visited = vector<bool>(n, 0);
    start = omp_get_wtime();
    cout << "Parallel BFS: ";
    parallelBFS(G, 0, visited);
    end = omp_get_wtime();
    printf("\nParallel BFS Time: %g", end - start);

    return 0;
}

/*
Input:
7 9
0 1
0 4
1 2
1 6
2 3
2 4
2 5
3 4
5 6

Output:
Serial DFS: 0 1 2 3 4 5 6 
Serial DFS Time: 0
Parallel DFS: 0 1 4 2 3 5 6
Parallel DFS Time: 0
Serial BFS: 0 1 4 2 6 3 5
Serial BFS Time: 0
Parallel BFS: 0 1 4 2 6 3 5
Parallel BFS Time: 0
*/