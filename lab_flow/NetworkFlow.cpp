/**
 * @file NetworkFlow.cpp
 * CS 225: Data Structures
 */

#include <vector>
#include <algorithm>
#include <set>

#include "graph.h"
#include "edge.h"

#include "NetworkFlow.h"

int min(int a, int b) {
  if (a<b)
    return a;
  else return b;
}

NetworkFlow::NetworkFlow(Graph & startingGraph, Vertex source, Vertex sink) :
  g_(startingGraph), residual_(Graph(true,true)), flow_(Graph(true,true)), source_(source), sink_(sink) {
    vector<Vertex> vtxs = g_.getVertices();
    for (auto& src : vtxs) {
        if (!residual_.vertexExists(src))
            residual_.insertVertex(src);
        if (!flow_.vertexExists(src))
            flow_.insertVertex(src);
        vector<Vertex> neighbors = g_.getAdjacent(src);
        for (auto& dest : neighbors) {
            residual_.insertEdge(src, dest);
            residual_.insertEdge(dest, src);
            residual_.setEdgeWeight(src, dest, g_.getEdge(src, dest).getWeight());
            residual_.setEdgeWeight(dest, src, 0);
            // single-way edge for flow graph
            flow_.insertEdge(src, dest);
            flow_.setEdgeWeight(src, dest, 0);
        }
    }
}

  /**
   * findAugmentingPath - use DFS to find a path in the residual graph with leftover capacity.
   *  This version is the helper function.
   *
   * @param source  The starting (current) vertex
   * @param sink    The destination vertex
   * @param path    The vertices in the path
   * @param visited A set of vertices we have visited
   */

bool NetworkFlow::findAugmentingPath(Vertex source, Vertex sink,
  std::vector<Vertex> &path, std::set<Vertex> &visited) {

  if (visited.count(source) != 0)
    return false;
  visited.insert(source);

  if (source == sink) {
    return true;
  }

  vector<Vertex> adjs = residual_.getAdjacent(source);
  for(auto it = adjs.begin(); it != adjs.end(); it++) {
    if (visited.count(*it) == 0 && residual_.getEdgeWeight(source,*it) > 0) {
      path.push_back(*it);
      if (findAugmentingPath(*it,sink,path,visited))
        return true;
      else {
        path.pop_back();
      }
    }
  }

  return false;
}

  /**
   * findAugmentingPath - use DFS to find a path in the residual graph with leftover capacity.
   *  This version is the main function.  It initializes a set to keep track of visited vertices.
   *
   * @param source The starting (current) vertex
   * @param sink   The destination vertex
   * @param path   The vertices in the path
   */

bool NetworkFlow::findAugmentingPath(Vertex source, Vertex sink, std::vector<Vertex> &path) {
   std::set<Vertex> visited;
   path.clear();
   path.push_back(source);
   return findAugmentingPath(source,sink,path,visited);
}

  /**
   * pathCapacity - Determine the capacity of a path in the residual graph.
   *
   * @param path   The vertices in the path
   */

int NetworkFlow::pathCapacity(const std::vector<Vertex> & path) const {
    int min = INT_MAX;
    int start = 0, end = 1;
    while (end != (int)path.size()) {
        const Vertex& src = path[start], dest = path[end];
        if (min > residual_.getEdge(src, dest).getWeight()) {
            min = residual_.getEdge(src, dest).getWeight();
        }
        start = end++;
    }
    return min;
}

  /**
   * calculuateFlow - Determine the capacity of a path in the residual graph.
   * Sets the member variable "maxFlow_" to be the flow, and updates the
   * residual graph and flow graph according to the algorithm.
   *
   * @return The network flow graph.
   */

const Graph & NetworkFlow::calculateFlow() {
    vector<Vertex> path;
    while (findAugmentingPath(source_, sink_, path)) {
        int cp = pathCapacity(path);
        // modify the two graphs at the same time
        int start = 0, end = 1;
        while (end != (int)path.size()) {
            Vertex& src = path[start], dest = path[end];
            residual_.setEdgeWeight(src, dest, residual_.getEdge(src, dest).getWeight() - cp);
            residual_.setEdgeWeight(dest, src, residual_.getEdge(src, dest).getWeight() + cp);
            // add if the direction is correct, minus otherwise
            if (flow_.edgeExists(src, dest)){
                flow_.setEdgeWeight(src, dest, flow_.getEdge(src, dest).getWeight() + cp);
            }else{
                flow_.setEdgeWeight(dest, src, flow_.getEdge(dest, src).getWeight() - cp);
            }
            start = end++;
        }
        // set the max flow;
        maxFlow_ = 0;
        path = flow_.getAdjacent(source_);
        for (auto& dest : path) {
            maxFlow_ += flow_.getEdgeWeight(source_, dest);
        }
    }
    return flow_;
}

int NetworkFlow::getMaxFlow() const {
  return maxFlow_;
}

const Graph & NetworkFlow::getGraph() const {
  return g_;
}

const Graph & NetworkFlow::getFlowGraph() const {
  return flow_;
}

const Graph & NetworkFlow::getResidualGraph() const {
  return residual_;
}
