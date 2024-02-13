#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <stack>
#include "graph.hpp"

Graph::Graph(std::size_t size) : graph(size) {}

void Graph::addVertex() {
    graph.push_back(std::vector<int>());
}

void Graph::addEdge(int src, int dest) {
    graph[src].push_back(dest);
    // graph[dest].push_back(src);
}

Graph Graph::transpose() {
    Graph newGraph(graph.size());
    for (int i = 0 ; i < graph.size(); ++i) {
        for (int j : graph[i]) {
            newGraph.graph[j].push_back(i);
        }
    }
    return newGraph;
}

std::vector<int> Graph::topSortKhan() {
    std::vector<int> inDegree(graph.size(), 0);
    for (int i = 0; i < graph.size(); ++i) {
        for (int u : graph[i]) {
            ++inDegree[u];
        }
    }
    std::queue<int> q;
    for (int i = 0; i < graph.size(); ++i) {
        if (inDegree[i] == 0) {
            q.push(i);
        }
    }
    std::vector<int> topSort;
    while (!q.empty()) {
        int tmp = q.front();
        q.pop();
        topSort.push_back(tmp);
        for (int u : graph[tmp]) {
            --inDegree[u];
            if (inDegree[u] == 0) {
                q.push(u);
            }
        }
    }
    if (topSort.size() != graph.size()) {
        return {};
    } 
    return topSort;
}

std::vector<std::vector<int>> Graph::sccKosaraju() {
    std::stack<int> stack;
    std::vector<bool> onStack(graph.size(), false);
    for (int i = 0; i < graph.size(); ++i) {
        if (!onStack[i]) {
            kosarajuHelper1(i, stack, onStack);
        }
    }
    
    Graph newGraph = this->transpose();

    std::vector<std::vector<int>> res;
    std::fill(onStack.begin(), onStack.end(), false);

    while (!stack.empty()) {
        int tmp = stack.top();
        stack.pop();
        if (!onStack[tmp]) {
            std::vector<int> SCC;
            newGraph.kosarajuHelper2(tmp, SCC, onStack);
            res.push_back(SCC);
        }
    }

    return res;
}

void Graph::kosarajuHelper1(int src, std::stack<int>& stack, std::vector<bool>& onStack) {
    onStack[src] = true;
    for (int i : graph[src]) {
        if (!onStack[i]) {
            kosarajuHelper1(i, stack, onStack);
        }
    }
    stack.push(src);
}

void Graph::kosarajuHelper2(int src, std::vector<int>& scc, std::vector<bool>& onStack) {
    scc.push_back(src);
    onStack[src] = true;
    for (int adj : graph[src]) {
        if (!onStack[adj]) {
            kosarajuHelper2(adj, scc, onStack);
        }
    }
}

std::vector<std::vector<int>> Graph::sccTarjan() {
    std::stack<int> stack;
    std::vector<bool> onStack(graph.size(), false);
    int id = 0;
    std::vector<int> ids(graph.size(), -1);
    std::vector<int> ll(graph.size());

    std::vector<std::vector<int>> res;
    for (int i = 0; i < graph.size(); ++i) {
        if (ids[i] == -1) {
            tarjanHelper(i, id, stack, onStack, ids, ll, res);
        }
    }
    return res;
}

void Graph::tarjanHelper(int src, int& id, std::stack<int>& stack, std::vector<bool>& onStack, std::vector<int>& ids, std::vector<int>& ll, std::vector<std::vector<int>>& res) {
    ids[src] = ll[src] = id++;
    onStack[src] = true;
    stack.push(src);
    for (int v : graph[src]) {
        if (ids[v] == -1) {
            tarjanHelper(v,  id, stack, onStack, ids, ll, res);
        }
        if (onStack[v]) {
            ll[src] = std::min(ll[src], ll[v]);
        }
    }
    if (ll[src] == ids[src]) {
        std::vector<int> SCC;
        for (int t = stack.top(); ; t = stack.top()) {
            SCC.push_back(t);
            onStack[t] = false;
            stack.pop();
            if (t == src) {
                break;
            }
        }
        res.push_back(SCC);
    }
}

void Graph::BFS(int start) const {
    std::vector<bool> visited(graph.size(), false);
    std::queue<int> q;
    q.push(start);
    visited[start] = true;
    while (!q.empty())
    {
        int tmp = q.front();
        q.pop();
        std::cout << tmp << " ";
        for (int i : graph[tmp]) {
            if (!visited[i]) {
                q.push(i);
                visited[i] = true;
            }
        }
    }
    std::cout << std::endl;
}

void Graph::DFSRec() {
    std::vector<bool> visited(graph.size(), false);
    for (int i = 0; i <  graph.size(); ++i) {
        if (!visited[i]) {
            dfs(i, visited);
        }
    }
    std::cout << std::endl;
}

void Graph::dfs(int start, std::vector<bool>& visited) {
    visited[start] = true;
    std::cout << start << " ";
    for (int u : graph[start]) {
        if (!visited[u]) {
            dfs(u, visited);
        }
    }
}

void Graph::DFSIter() const {
    std::vector<bool> visited(graph.size(), false);
    for (int i = 0; i < graph.size(); ++i) {
        if (!visited[i]) {
            dfsIter(i, visited);
        }
    }
    std::cout << std::endl;
}

void Graph::dfsIter(int start, std::vector<bool>& visited) const {
    std::stack<int> s;
    s.push(start);
    while (!s.empty()) {
        int tmp = s.top();
        s.pop();
        if (!visited[tmp]) {
            std::cout << tmp << " ";
            visited[tmp] = true;
        }
        for (int u : graph[tmp]) {
            if (!visited[u]) {
                s.push(u);
            }
        }
    }
}

std::vector<int> Graph::shortestPath(int src, int dest) {
    std::vector<int> res;
    std::vector<bool> visited(graph.size(), false);
    std::vector<int> parent(graph.size(), -1);
    bfs(src, dest, visited, parent, res);
    return res;
}

void Graph::bfs(int src, int dest, std::vector<bool>& visited, std::vector<int>& parent, std::vector<int>& res) {
    std::queue<int> q;
    visited[src] = true;
    q.push(src);
    while (!q.empty()) {
        int front = q.front();
        q.pop();
        for (int adj : graph[front]) {
            if (!visited[adj]) {
                q.push(adj);
                visited[adj] = true;
                parent[adj] = front;
                if (adj == dest) {
                    while (adj != -1) {
                        res.push_back(adj);
                        adj = parent[adj];
                    }
                    reverse(res.begin(), res.end());
                    return;
                }
            }
        }
    }
}

std::vector<std::vector<int>> Graph::allPaths(int src, int dest) {
    std::vector<bool> visited(graph.size(), false);
    std::vector<std::vector<int>> res;
    std::vector<int> tmp;
    helperPaths(src, dest, res, tmp, visited);
    return res;
}

void Graph::helperPaths(int src, int dest, std::vector<std::vector<int>>& res, std::vector<int>& tmp, std::vector<bool>& visited) {
    tmp.push_back(src);
    visited[src] = true;
    if (src == dest) {
        res.push_back(tmp);
    }
    else {
        for (int adj : graph[src]) {
            if (!visited[adj]) 
                helperPaths(adj, dest, res, tmp, visited);
        }
    }
    visited[src] = false;
    tmp.pop_back();
}