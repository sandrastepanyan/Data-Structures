#ifndef GRAPH_H
#define GRAPH_H
#include <stack>

class Graph {
public:
    Graph() = default;
    Graph(std::size_t size);

    void addVertex();
    void addEdge(int src, int dest);

    void DFSRec();
    void DFSIter() const;
    void BFS(int start) const;

    Graph transpose();
    std::vector<int> topSortKhan();

    std::vector<std::vector<int>> sccKosaraju();
    std::vector<std::vector<int>> sccTarjan();

    std::vector<int> shortestPath(int src, int dest);
    std::vector<std::vector<int>> allPaths(int src, int dest);

private:
    void dfs(int start, std::vector<bool>& visited);
    void dfsIter(int start, std::vector<bool>& visited) const;
    void bfs(int src, int dest, std::vector<bool>& visited, std::vector<int>& parent, std::vector<int>& res);
    void helperPaths(int src, int dest, std::vector<std::vector<int>>& res, std::vector<int>& tmp, std::vector<bool>& visited);

    void kosarajuHelper1(int src, std::stack<int>& stack, std::vector<bool>& onStack);
    void kosarajuHelper2(int src, std::vector<int>& scc, std::vector<bool>& onStack);
    void tarjanHelper(int src, int& id, std::stack<int>& stack, std::vector<bool>& onStack, std::vector<int>& ids, std::vector<int>& ll, std::vector<std::vector<int>>& scc);

private:
    std::vector<std::vector<int>> graph;
};

#endif
