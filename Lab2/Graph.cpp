#include <iostream>
#include <vector>
#include <string>
#include <queue>

class Graph
{
private:
    unsigned int amount_of_nodes;
    std::vector<std::vector<int>> Adj;
public:
    Graph()
    {
        amount_of_nodes = 0;
    }
    Graph(std::vector<std::vector<int>> M)
    {
        int a = 0;
        for(int i = 0; i < M.size(); i++)
        {
            if(M.size() != M[i].size())
            {
                std::cerr << "The matrix must be square.";
                a = -1;
            }
        }
        if(a != -1)
        {
            amount_of_nodes = M.size();
            Adj = M;
        }
    }
    ~Graph()
    {

    }
    void Add_Edge(int from, int to)
    {
        Adj[from][to] = 1;
    }

    void Add_Node()
    {
        std::vector<int> NewNodeEdges;
        for(int i = 0; i < amount_of_nodes; i++)
        {
            Adj[i].push_back(0);
        }
        for(int i = 0; i < amount_of_nodes + 1; i++)
        {
            NewNodeEdges.push_back(0);
        }
        Adj.push_back(NewNodeEdges);
        amount_of_nodes++;
    }

    void PrintAdjMatrix()
    {
        for(int i = 0; i < amount_of_nodes; i++)
        {
            for(int j = 0; j < amount_of_nodes; j++)
            {
                std::cout << Adj[j][i] << ' ';
            }
            std::cout << std::endl;
        }
    }

    int get_amount_nodes()
    {
        return amount_of_nodes;
    }

    std::vector<std::vector<int>> get_adjacency_matrix()
    {
        return Adj;
    }
};

class Visitor
{
public:
    virtual void initialize_node(int node, Graph &G) = 0;

    virtual void start_node(int node, Graph &G) = 0;

    virtual void discover_node(int node, Graph &G) = 0;

    virtual void examine_edge(int from,int to, Graph &G) = 0;

    virtual void tree_edge(int from, int to, Graph &G) = 0;

    virtual void back_edge(int from, int to, Graph &G) = 0;

    virtual void forward_or_cross_edge(int from, int to, Graph &G) = 0;

    virtual void finish_edge(int from, int to, Graph &G) = 0;

    virtual void finish_node(int node, Graph &G) = 0;


    virtual ~Visitor()
    {

    };
};

class DFS: public Visitor
{
private:
    std::vector<std::string> color;
    std::vector<int> path;

    void Algorithm(int start, Graph &G)
    {
        std::cout << start << std::endl;
        discover_node(start, G);
        for(int i = 0; i < G.get_amount_nodes(); i++)
        {
            if(G.get_adjacency_matrix()[start][i] == 1)
            {
                examine_edge(start, i, G);
            }
        }

        finish_node(start, G);
    }
public:
    DFS(Graph &G)
    {
        path = std::vector<int> (G.get_amount_nodes());
        color = std::vector<std::string> (G.get_amount_nodes());
        for(int i = 0; i < G.get_amount_nodes(); i++)
        {
            initialize_node(i,G);
        }
    }
    DFS(int start, Graph &G): DFS(G)
    {
        start_node(start, G);
    }

    ~DFS()
    {
        color.clear();
        path.clear();
    }

    void initialize_node(int node, Graph &G)
    {
        color[node] = "White";
        path[node] = node;
    }

    void start_node(int node, Graph &G)
    {
        if(color[node] == "White")
        {
            Algorithm(node, G);
        }
    }

    void discover_node(int node, Graph &G)
    {
        color[node] = "Gray";
    }

    void examine_edge(int from, int to, Graph &G)
    {
        if(color[to] == "White")
        {
            tree_edge(from, to, G);
        }
        else if(color[to] == "Gray")
        {
            back_edge(from, to, G);
        }
        else if(color[to] == "Black")
        {
            forward_or_cross_edge(from, to, G);
        }
    }

    void tree_edge(int from, int to, Graph &G)
    {
        path[to] = from;
        start_node(to, G);
    }

    void back_edge(int from, int to, Graph &G)
    {
        return;
    }

    void forward_or_cross_edge(int from, int to, Graph &G)
    {
        return;
    }

    void finish_edge(int from, int to, Graph &G)
    {
        return;
    }

    void finish_node(int node, Graph &G)
    {
        color[node] = "Black";
    }

    std::vector<std::string> get_visited()
    {
        return color;
    }


};

class BFS: public Visitor
{
private:
    std::queue<int> q;
    std::vector<std::string> color;
    std::vector<int> path;

    Algorithm(int start, Graph &G)
    {
        discover_node(start, G);
        while (!q.empty())
        {
            int current_edge = q.front();
            std::cout << current_edge << std::endl;
            for (int i = 0; i < G.get_amount_nodes(); i++)
            {
                if (G.get_adjacency_matrix()[current_edge][i])
                {
                    examine_edge(current_edge, i, G);
                }
            }
            finish_node(current_edge, G);
        }
    }

public:

    BFS(Graph &G)
    {
        path = std::vector<int> (G.get_amount_nodes());
        color = std::vector<std::string> (G.get_amount_nodes());
        for (int i = 0; i < G.get_amount_nodes(); i++)
        {
            initialize_node(i, G);
        }
    }

    BFS(int start, Graph &G): BFS(G)
    {
        start_node(start, G);
    }

    void initialize_node(int node, Graph &G)
    {
        color[node] = "White";
        path[node] = node;
    }

    void start_node(int node, Graph &G)
    {
        if (color[node] == "White")
        {
            Algorithm(node, G);
        }
    }

    void discover_node(int node, Graph &G)
    {
        q.push(node);
        color[node] = "Gray";
    }

    void examine_edge(int from,int to, Graph &G)
    {
        if (color[to] == "White")
        {
            tree_edge(from, to, G);
        }
        else if (color[to] == "Gray")
        {
            back_edge(from, to, G);
        }
        else if (color[to] == "Balck")
        {
            forward_or_cross_edge(from, to, G);
        }
    }

    void tree_edge(int from, int to, Graph &G)
    {
        path[to] = from;
        discover_node(to, G);
    }

    void back_edge(int from, int to, Graph &G)
    {
        return;
    }

    void forward_or_cross_edge(int from, int to, Graph &G)
    {
        return;
    }

    void finish_edge(int from, int to, Graph &G)
    {
        return;
    }

    void finish_node(int node, Graph &G)
    {
        color[node] = "Black";
        q.pop();
    }

    ~BFS()
    {
        color.clear();
        path.clear();
    }
};

int main()
{
    std::vector<std::vector<int>> M;
    for(int i = 0; i < 4; i++)
    {
        std::vector<int> Vec = {0, 0, 0, 0};
        M.push_back(Vec);
    }
    M[0][2] = 1;
    M[3][1] = 1;
    M[1][3] = 1;
    M[2][0] = 1;
    M[2][1] = 1;
    M[1][2] = 1;
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
            std::cout <<M[i][j] << ' ';
        std::cout << std::endl;
    }
    std::cout << std::endl;
    Graph G(M);
    DFS visitor(1, G);
    return 0;
}
