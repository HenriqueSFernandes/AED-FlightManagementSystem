/*
 * Graph.h
 */
#ifndef GRAPH_H_
#define GRAPH_H_

#include <cstddef>
#include <vector>
#include <queue>
#include <stack>
#include <list>
#include "Flight.h"

using namespace std;

template<class T>
class Edge;

template<class T>
class Graph;

template<class T>
class Vertex;


/****************** Provided structures  ********************/

template<class T>
class Vertex {
    T info;                // contents
    vector<Edge<T> > adj;  // list of outgoing edges
    bool visited;          // auxiliary field
    bool processing;       // auxiliary field
    int indegree;          // auxiliary field
    int outdegree;
    int distance;

private:
    // auxiliary field
    int num;               // auxiliary field
    int low;               // auxiliary field

    void addEdge(Vertex<T> *dest, set<Airline> airlines, double w);

    bool removeEdgeTo(Vertex<T> *d);

public:
    Vertex(T in);

    T getInfo() const;

    void setInfo(T in);

    bool isVisited() const;

    void setVisited(bool v);

    bool isProcessing() const;

    void setProcessing(bool p);

    const vector<Edge<T>> &getAdj() const;

    void setAdj(const vector<Edge<T>> &adj);

    int getIndegree() const;

    void setIndegree(int indegree);

    int getNum() const;

    void setNum(int num);

    int getLow() const;

    void setLow(int low);

    int getOutdegree() const {
        return outdegree;
    }

    void setOutdegree(int outdegree) {
        Vertex::outdegree = outdegree;
    }

    friend class Graph<T>;

    int getDistance() const {
        return distance;
    }

    void setDistance(int distance) {
        Vertex::distance = distance;
    }
};

template<class T>
class Edge {
    Vertex<T> *dest;      // destination vertex
    double weight;         // edge weight
    set<Airline> airlines;
public:
    Edge(Vertex<T> *d, set<Airline> airlines, double w);

    Vertex<T> *getDest() const;

    void setDest(Vertex<T> *dest);

    double getWeight() const;

    void setWeight(double weight);

    set<Airline> getAirlines();

    void addAirline(Airline airline);

    friend class Graph<T>;

    friend class Vertex<T>;
};

template<class T>
class Graph {
    vector<Vertex<T> *> vertexSet;      // vertex set
    int _index_;                        // auxiliary field
    stack<Vertex<T>> _stack_;           // auxiliary field
    list <list<T>> _list_sccs_;        // auxiliary field

    void dfsVisit(Vertex<T> *v, vector<T> &res) const;

    bool dfsIsDAG(Vertex<T> *v) const;

public:
    Vertex<T> *findVertex(const T &in) const;

    int getNumVertex() const;

    bool addVertex(const T &in);

    bool removeVertex(const T &in);

    bool addEdge(const T &sourc, const T &dest, set<Airline> airlines, double w = 0);

    bool removeEdge(const T &sourc, const T &dest);

    vector<Vertex<T> *> getVertexSet() const;

    vector<T> dfs() const;

    vector<T> dfs(const T &source) const;

    vector<T> bfs(const T &source) const;

    vector<T> topsort() const;

    bool isDAG() const;

    vector<T> dfsLimited(const T &source, int k) const;

    void dfsVisitLimited(Vertex<T> *v, vector<T> &res, int k) const;

    vector<T> bfsLimited(const T &source, int k) const;
};

/****************** Provided constructors and functions ********************/

template<class T>
Vertex<T>::Vertex(T in): info(in), indegree(0), outdegree(0) {}

template<class T>
Edge<T>::Edge(Vertex<T> *d, set<Airline> airlines, double w): dest(d), airlines(airlines), weight(w) {}


template<class T>
int Graph<T>::getNumVertex() const {
    return vertexSet.size();
}

template<class T>
vector<Vertex<T> *> Graph<T>::getVertexSet() const {
    return vertexSet;
}

template<class T>
T Vertex<T>::getInfo() const {
    return info;
}

template<class T>
void Vertex<T>::setInfo(T in) {
    Vertex::info = in;
}

template<class T>
bool Vertex<T>::isProcessing() const {
    return processing;
}

template<class T>
void Vertex<T>::setProcessing(bool p) {
    Vertex::processing = p;
}

template<class T>
Vertex<T> *Edge<T>::getDest() const {
    return dest;
}

template<class T>
void Edge<T>::setDest(Vertex<T> *d) {
    Edge::dest = d;
}

template<class T>
double Edge<T>::getWeight() const {
    return weight;
}

template<class T>
void Edge<T>::setWeight(double weight) {
    Edge::weight = weight;
}

template<class T>
set<Airline> Edge<T>::getAirlines() {
    return airlines;
}

template<class T>
void Edge<T>::addAirline(Airline airline) {
    Edge::airlines.insert(airline);

}

/*
 * Auxiliary function to find a vertex with a given content.
 */
template<class T>
Vertex<T> *Graph<T>::findVertex(const T &in) const {
    for (auto v: vertexSet)
        if (static_cast<const Airport>(v->info) == in)
            return v;
    return NULL;
}

template<class T>
bool Vertex<T>::isVisited() const {
    return visited;
}

template<class T>
int Vertex<T>::getIndegree() const {
    return indegree;
}

template<class T>
void Vertex<T>::setIndegree(int indegree) {
    Vertex::indegree = indegree;
}

template<class T>
int Vertex<T>::getNum() const {
    return num;
}

template<class T>
void Vertex<T>::setNum(int num) {
    Vertex::num = num;
}

template<class T>
int Vertex<T>::getLow() const {
    return low;
}

template<class T>
void Vertex<T>::setLow(int low) {
    Vertex::low = low;
}

template<class T>
void Vertex<T>::setVisited(bool v) {
    Vertex::visited = v;
}

template<class T>
const vector<Edge<T>> &Vertex<T>::getAdj() const {
    return adj;
}

template<class T>
void Vertex<T>::setAdj(const vector<Edge<T>> &adj) {
    Vertex::adj = adj;
}


/*
 *  Adds a vertex with a given content or info (in) to a graph (this).
 *  Returns true if successful, and false if a vertex with that content already exists.
 */
template<class T>
bool Graph<T>::addVertex(const T &in) {
    if (findVertex(in) != NULL)
        return false;
    vertexSet.push_back(new Vertex<T>(in));
    return true;
}


/*
 * Adds an edge to a graph (this), given the contents of the source and
 * destination vertices and the edge weight (w).
 * Returns true if successful, and false if the source or destination vertex does not exist.
 */
template<class T>
bool Graph<T>::addEdge(const T &sourc, const T &dest, set<Airline> airlines, double w) {
    auto v1 = findVertex(sourc);
    auto v2 = findVertex(dest);
    if (v1 == NULL || v2 == NULL)
        return false;
    v1->addEdge(v2, airlines, w);
    return true;
}

/*
 * Auxiliary function to add an outgoing edge to a vertex (this),
 * with a given destination vertex (d) and edge weight (w).
 */
template<class T>
void Vertex<T>::addEdge(Vertex<T> *d, set<Airline> airlines, double w) {
    adj.push_back(Edge<T>(d, airlines, w));
}


/*
 * Removes an edge from a graph (this).
 * The edge is identified by the source (sourc) and destination (dest) contents.
 * Returns true if successful, and false if such edge does not exist.
 */
template<class T>
bool Graph<T>::removeEdge(const T &sourc, const T &dest) {
    auto v1 = findVertex(sourc);
    auto v2 = findVertex(dest);
    if (v1 == NULL || v2 == NULL)
        return false;
    return v1->removeEdgeTo(v2);
}

/*
 * Auxiliary function to remove an outgoing edge (with a given destination (d))
 * from a vertex (this).
 * Returns true if successful, and false if such edge does not exist.
 */
template<class T>
bool Vertex<T>::removeEdgeTo(Vertex<T> *d) {
    for (auto it = adj.begin(); it != adj.end(); it++)
        if (it->dest == d) {
            adj.erase(it);
            return true;
        }
    return false;
}

/*
 *  Removes a vertex with a given content (in) from a graph (this), and
 *  all outgoing and incoming edges.
 *  Returns true if successful, and false if such vertex does not exist.
 */
template<class T>
bool Graph<T>::removeVertex(const T &in) {
    for (auto it = vertexSet.begin(); it != vertexSet.end(); it++)
        if ((*it)->info == in) {
            auto v = *it;
            vertexSet.erase(it);
            for (auto u: vertexSet)
                u->removeEdgeTo(v);
            delete v;
            return true;
        }
    return false;
}


/****************** DFS ********************/
/*
 * Performs a depth-first search (dfs) traversal in a graph (this).
 * Returns a vector with the contents of the vertices by dfs order.
 * Follows the algorithm described in theoretical classes.
 */
template<class T>
vector<T> Graph<T>::dfs() const {
    vector<T> res;
    for (auto v: vertexSet)
        v->visited = false;
    for (auto v: vertexSet)
        if (!v->visited)
            dfsVisit(v, res);
    return res;
}

/*
 * Auxiliary function that visits a vertex (v) and its adjacent, recursively.
 * Updates a parameter with the list of visited node contents.
 */
template<class T>
void Graph<T>::dfsVisit(Vertex<T> *v, vector<T> &res) const {
    v->visited = true;
    res.push_back(v->info);
    for (auto &e: v->adj) {
        auto w = e.dest;
        if (!w->visited)
            dfsVisit(w, res);
    }
}

template<class T>
void Graph<T>::dfsVisitLimited(Vertex<T> *v, vector<T> &res, int k) const {
    if (k > 0) {
        v->visited = true;
        res.push_back(v->info);

        for (auto &e: v->adj) {
            auto w = e.dest;
            if (!w->visited)
                dfsVisitLimited(w, res, k - 1);
        }
    }
}



/****************** DFS ********************/
/*
 * Performs a depth-first search (dfs) in a graph (this).
 * Returns a vector with the contents of the vertices by dfs order,
 * from the source node.
 */
template<class T>
vector<T> Graph<T>::dfs(const T &source) const {
    vector<T> res;
    auto s = findVertex(source);
    if (s == nullptr)
        return res;

    for (auto v: vertexSet)
        v->visited = false;

    dfsVisit(s, res);
    return res;
}

template<class T>
vector<T> Graph<T>::dfsLimited(const T &source, int k) const {
    vector<T> res;
    auto s = findVertex(source);
    if (s == nullptr)
        return res;

    for (auto v: vertexSet)
        v->visited = false;

    dfsVisitLimited(s, res, k);
    return res;
}


/****************** BFS ********************/
/*
 * Performs a breadth-first search (bfs) in a graph (this), starting
 * from the vertex with the given source contents (source).
 * Returns a vector with the contents of the vertices by bfs order.
 */
template<class T>
vector<T> Graph<T>::bfs(const T &source) const {
    vector<T> res;
    auto s = findVertex(source);
    if (s == NULL)
        return res;
    queue<Vertex<T> *> q;
    for (auto v: vertexSet)
        v->visited = false;
    q.push(s);
    s->visited = true;
    while (!q.empty()) {
        auto v = q.front();
        q.pop();
        res.push_back(v->info);
        for (auto &e: v->adj) {
            auto w = e.dest;
            if (!w->visited) {
                q.push(w);
                w->visited = true;
            }
        }
    }
    return res;
}

template<class T>
vector<T> Graph<T>::bfsLimited(const T &source, int k) const {
    vector<T> res;
    auto s = findVertex(source);
    if (s == NULL)
        return res;
    queue<Vertex<T> *> q;
    for (auto v: vertexSet) {
        v->visited = false;
        v->setNum(0);

    }
    q.push(s);
    s->visited = true;
    s->setNum(0);
    while (!q.empty()) {
        auto v = q.front();
        q.pop();
        for (auto &e: v->adj) {
            auto w = e.dest;
            if (!w->visited) {
                q.push(w);
                w->visited = true;
                w->setNum(v->getNum() + 1);
                if (w->getNum() <= k) {
                    res.push_back(w->info);
                }
            }
        }
    }
    return res;
}


/****************** isDAG  ********************/
/*
 * Performs a depth-first search in a graph (this), to determine if the graph
 * is acyclic (acyclic directed graph or DAG).
 * During the search, a cycle is found if an edge connects to a vertex
 * that is being processed in the stack of recursive calls (see theoretical classes).
 * Returns true if the graph is acyclic, and false otherwise.
 */

template<class T>
bool Graph<T>::isDAG() const {
    for (auto v: vertexSet) {
        v->visited = false;
        v->processing = false;
    }
    for (auto v: vertexSet)
        if (!v->visited)
            if (!dfsIsDAG(v))
                return false;
    return true;
}

/**
 * Auxiliary function that visits a vertex (v) and its adjacent, recursively.
 * Returns false (not acyclic) if an edge to a vertex in the stack is found.
 */
template<class T>
bool Graph<T>::dfsIsDAG(Vertex<T> *v) const {
    v->visited = true;
    v->processing = true;
    for (auto &e: v->adj) {
        auto w = e.dest;
        if (w->processing)
            return false;
        if (!w->visited)
            if (!dfsIsDAG(w))
                return false;
    }
    v->processing = false;
    return true;
}


/****************** toposort ********************/
//=============================================================================
// Exercise 1: Topological Sorting
//=============================================================================
// TODO
/*
 * Performs a topological sorting of the vertices of a graph (this).
 * Returns a vector with the contents of the vertices by topological order.
 * If the graph has cycles, returns an empty vector.
 * Follows the algorithm described in theoretical classes.
 */

template<class T>
vector<T> Graph<T>::topsort() const {
    vector<T> res;
    queue<Vertex<T> *> toProcess;
    if (!this->isDAG()) return {};
    for (auto vertex: this->vertexSet) {
        vertex->setIndegree(0);
    }
    for (auto v: vertexSet) {
        for (Edge<T> &e: v->adj) {
            e.dest->indegree++;
        }
    }
    for (auto v: vertexSet) {
        if (v->indegree == 0) {
            toProcess.push(v);
        }
    }
    while (!toProcess.empty()) {
        auto processing = toProcess.front();
        for (Edge<T> e: processing->adj) {
            e.dest->indegree -= 1;
            if (e.dest->indegree == 0) {
                toProcess.push(e.dest);
            }
        }
        toProcess.pop();
        res.push_back(processing->getInfo());
    }

    return res;
}

#endif /* GRAPH_H_ */
