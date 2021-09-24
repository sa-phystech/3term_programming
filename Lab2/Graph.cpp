#include <iostream>
#include <utility>
#include <vector>
#include <string>


struct Edge
{
    std::pair<int, int> E;
    bool passed = false;
};

struct Vertex
{
    std::string color;
    int number;
    std::vector<Edge> neighbours;

};
class Graph
{
public:
    int Vertexes;
    std::vector<Vertex> Nodes;
    std::vector< std::vector<int> > Adj;
    Graph()
    {
        int Vertexes = 0;

    }
    ~Graph()
    {
        Nodes.clear();
    }
    void AddVertex(Vertex v)
    {
        if(Vertexes != 0)
        {
            v.number = Nodes.size();
            Nodes.push_back(v);
            Vertexes += 1;
            //std::cout << "ADD" << std::endl;
        }
        else
        {
            Vertexes = 1;
            v.number = 0;
            Nodes.push_back(v);
            //std::cout << "ADD1" << std::endl;
        }

    }
    void AddEdge(Vertex v1, Vertex v2)
    {
        Edge e;
        e.E= {v1.number, v2.number};
        v1.neighbours.push_back(e);
        //std::cout << "ADDEDGE" << std::endl;
    }

};

class DFSVisitor
{
public:
    std::vector< Edge > path;
    std::vector< Edge > backedges;
    std::vector< Edge > forwardedges;

    void PrintPath()
    {
        for(int i = 0; i < path.size(); i++)
        {

            std::cout << path[i].E.first << ' ' << path[i].E.second << std::endl;
        }

        std::cout << std::endl;
    }


    void Initialize_vertex(Vertex v, Graph g)
    {
        v.color = "white";
        //std::cout << "white" << std::endl;
    }


    void Discover_vertex(Vertex v, Graph g)
    {
        v.color = "gray";
        //std::cout << "gray" << std::endl;
        //Examine_edge(v);
    }

    void Examine_edge(Vertex v, Graph g)
    {

    }

    void Tree_edge(Edge e, Graph g)
    {
        path.push_back(e);
        //std::cout << "treeedge" << std::endl;
    }

    void Back_edge(Edge e, Graph g)
    {
        backedges.push_back(e);
        //std::cout << "backedge" << std::endl;
    }
    void Forward_edge(Edge e, Graph g)
    {
        forwardedges.push_back(e);
        //std::cout << "forwardedge" << std::endl;
    }
    void Finish_edge(Edge e, Graph g)
    {
        e.passed = true;
        //std::cout << "finishedge" << std::endl;
    }
    void Finish_vertex(Vertex v, Graph g)
    {
        v.color = "black";
        //std::cout << "black" << std::endl;
    }




    void DFS(Graph g, Vertex start)
    {
        for(int i = 0; i < g.Nodes.size(); i++)
        {
            Vertex j = g.Nodes[i];
            Initialize_vertex(j, g);
        }
        DFS_Visit(start, g);
        PrintPath();
    }




    void DFS_Visit(Vertex v, Graph g)
    {
        Discover_vertex(v, g);

        for (int i = 0; i < v.neighbours.size(); i++)
        {
            Edge j = v.neighbours[i];
            if(g.Nodes[j.E.second].color == "white")
            {
                Tree_edge(j, g);
                DFS_Visit(g.Nodes[j.E.second], g);
            }
            else if(g.Nodes[j.E.second].color == "gray")
            {
                Back_edge(j, g);
            }
            else if(g.Nodes[j.E.second].color == "black")
            {
                Forward_edge(j, g);
            }
        }
        Finish_vertex(v, g);
        //path.pop_back(v.number);
        /*for (Edge i = v.neighbours.begin(); i != v.neighbours.end(), i++)
        {
            Finish_edge(i.to);
        }*/
    }

    void Start_vertex(Vertex v, Graph g)
    {
        DFS_Visit(v, g);
    }

};


int main()
{
    Graph g1;
    Vertex a, b, c, d, e, f;
    g1.AddVertex(a); //1
    g1.AddVertex(b); //2
    g1.AddVertex(c); //3
    g1.AddVertex(d); //4
    g1.AddVertex(e); //5
    g1.AddVertex(f); //6
    g1.AddEdge(a, b); // 1,2
    g1.AddEdge(b, e); // 2,5
    g1.AddEdge(a, f); // 1,6
    g1.AddEdge(e, d); // 5,4
    g1.AddEdge(b, d); // 2,4
    g1.AddEdge(c, f); // 3,6
    g1.AddEdge(f, e); // 6,5


    DFSVisitor visit;

    visit.DFS(g1, e);
    visit.PrintPath();
    for (int i = 0; i < 6; i++)
    {
        std::cout << g1.Nodes[i].number << std::endl;
    }
    std::cout << visit.path.size() << std::endl;
    std::cout << g1.Nodes.size() << std::endl;
    std::cout << g1.Nodes[0].neighbours.size() << std::endl;
    return 0;
}
