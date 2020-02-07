#include "Graph.h"
#include "Edge.h"
#include "Vertex.h"

#include <string>
#include <iostream>
using std::list;
using std::string;
using std::find;
using std::reference_wrapper;
/**
* @return The number of vertices in the Graph
*/
template <class V, class E>
unsigned int Graph<V,E>::numVertices() const {
  return vertexMap.size();
}


/**
* The degree of the vertex. For directed: Sum of in-degree and out-degree
* @return Returns the degree of a given vertex.
* @param v Given vertex to return degree.
*/
template <class V, class E>
unsigned int Graph<V,E>::degree(const V & v) const {
    unsigned int deg = 0;
    // out-degree
    deg += adjList.at(v.key()).size();
    // in-degree
    for (auto& vtx : adjList) {
        // skip its own list
        if (vtx.first == v.key())
            continue;
        // iterate through each list
        for (auto& edgeIter : vtx.second) {
            if ((*edgeIter).get().directed() && (*edgeIter).get().dest() == v)
                ++deg;
        }
    }
    return deg;
}


/**
* Inserts a Vertex into the Graph.
* @param key The key of the Vertex to insert
* @return The inserted Vertex
*/
template <class V, class E>
V & Graph<V,E>::insertVertex(string key) {
    // if key already exists, clean up
    if (vertexMap.find(key) != vertexMap.end()) {
        removeVertex(key);
    }

    V & v = *(new V(key));
    V_byRef temp(v);
    vertexMap.emplace(key, temp);
    adjList[key] = list<edgeListIter>();
    return v;
}

/**
* Inserts an Edge into the Graph.
* @param v1 The source Vertex
* @param v2 The destination Vertex
* @return The inserted Edge
*/
template <class V, class E>
E & Graph<V,E>::insertEdge(const V & v1, const V & v2) {
    E & e = *(new E(v1, v2));
    E_byRef temp(e);
    // set up edgeList
    edgeList.push_back(temp);
    // set up source's adjList
    edgeListIter temp_iter = edgeList.end();
    --temp_iter;
    adjList[v1.key()].push_back(temp_iter);
    // undirected, add one more
    if (!e.directed())
        adjList[v2.key()].push_back(temp_iter);
    return e;
}


/**
* Removes a given Vertex
* @param v The Vertex to remove
*/
template <class V, class E>
void Graph<V,E>::removeVertex(const string & key) {
    Vertex v1("key1"), v2("key2");
    E e(v1, v2);

    for (auto& vtx : adjList) {
        if (vtx.first == key) {
            for (auto listIter = vtx.second.begin(); listIter != vtx.second.end();) {
                auto temp = listIter;
                ++temp;
                removeEdge((**listIter).get().source().key(), (**listIter).get().dest().key());
                listIter = temp;
            }
        }else{
            if (e.directed()) {
                // clean up other list contains edge whose dest = key
                for (auto& edgeIter : vtx.second) {
                    if ((*edgeIter).get().dest().key() == key) {
                        removeEdge((*edgeIter).get().source().key(), (*edgeIter).get().dest().key());
                        break;
                    }
                }
            }
        }
    }
    adjList.erase(key);
    delete &(vertexMap.at(key).get());
    vertexMap.erase(key);
}

/**
* Removes an Edge from the Graph. Consider both the undirected and directed cases.
* min(degree(key1), degree(key2))
* @param key1 The key of the source Vertex
* @param key2 The key of the destination Vertex
*/
template <class V, class E>
void Graph<V,E>::removeEdge(const string key1, const string key2) {
    list<edgeListIter>& list1 = adjList[key1];
    list<edgeListIter>& list2 = adjList[key2];

    for (auto iter = list1.begin(); iter != list1.end(); ++iter) {
        if ((**iter).get().dest().key() == key2){
            // remove the same edge in key2's list when undirected
            if (!(**iter).get().directed()) {
                for (auto iter2 = list2.begin(); iter != list2.end(); ++iter2) {
                    if (((**iter2).get().dest().key() == key1 && (**iter2).get().source().key() == key2)
                        || ((**iter2).get().dest().key() == key2 && (**iter2).get().source().key() == key1)) {
                        list2.erase(iter2);
                        break;
                    }
                }
            }
            removeEdge(*iter);
            list1.erase(iter);
            break;
        }
    }
}


/**
* Removes an Edge from the Graph given by the location of the given iterator into the edge list.
* @param it An iterator at the location of the Edge that
* you would like to remove
*/
template <class V, class E>
void Graph<V,E>::removeEdge(const edgeListIter & it) {
    delete &(*it).get();
    edgeList.erase(it);
}


/**
* Return the list of incident edges from a given vertex.
* For the directed case, consider all edges that has the vertex as either a source or destination.
* @param key The key of the given vertex
* @return The list edges (by reference) that are adjacent to the given vertex
*/
template <class V, class E>
const list<reference_wrapper<E>> Graph<V,E>::incidentEdges(const string key) const {
    list<reference_wrapper<E>> edges;
    for (auto& vtx : adjList) {
        if (vtx.first == key) {
            for (auto& edgeIter : vtx.second) {
                edges.push_back(*edgeIter);
            }
        }else{
            for (auto& edgeIter : vtx.second) {
                E& e = (*edgeIter).get();
                if (e.directed() && e.dest().key() == key)
                    edges.push_back(*edgeIter);
            }
        }
    }
    return edges;
}


/**
* Return whether the two vertices are adjacent to one another. Consider both the undirected and directed cases.
* When the graph is directed, v1 and v2 are only adjacent if there is an edge from v1 to v2.
* @param key1 The key of the source Vertex
* @param key2 The key of the destination Vertex
* @return True if v1 is adjacent to v2, False otherwise
*/
template <class V, class E>
bool Graph<V,E>::isAdjacent(const string key1, const string key2) const {
    Vertex v1(key1), v2(key2);
    E e(v1, v2);
    if (e.directed()) {
        const list<edgeListIter>& key_list = adjList.at(key1);
        for (auto& edgeIter : key_list) {
            if ((*edgeIter).get().dest().key() == key2)
                return true;
        }
    }else{
        // undirected: choose the vertex with smaller degree
        int deg1 = degree(key1), deg2 = degree(key2);
        string key_less, key_more;
        if (deg1 <= deg2) {
            key_less = key1, key_more = key2;
        }else{
            key_less = key2, key_more = key1;
        }
        for (auto& edgeIter : adjList.at(key_less)) {
            if ((*edgeIter).get().dest().key() == key_more)
                return true;
            if ((*edgeIter).get().source().key() == key_more && (*edgeIter).get().dest().key() == key_less)
                return true;
        }
    }
    return false;
}
