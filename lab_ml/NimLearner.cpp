/**
 * @file NimLearner.cpp
 * CS 225: Data Structures
 */

#include "NimLearner.h"
#include <ctime>
using std::stoi;
/**
 * Constructor to create a game of Nim with `startingTokens` starting tokens.
 *
 * This function creates a graph, `g_` representing all of the states of a
 * game of Nim with vertex labels "p#-X", where:
 * - # is the current player's turn; p1 for Player 1, p2 for Player2
 * - X is the tokens remaining at the start of a player's turn
 *
 * For example:
 *   "p1-4" is Player 1's turn with four (4) tokens remaining
 *   "p2-8" is Player 2's turn with eight (8) tokens remaining
 *
 * All legal moves between states are created as edges with initial weights
 * of 0.
 *
 * @param startingTokens The number of starting tokens in the game of Nim.
 */
NimLearner::NimLearner(unsigned startingTokens) : g(true, true) {
    for (int i = startingTokens; i >= 0; --i) {
        g.insertVertex("p1-" + to_string(i));
        g.insertVertex("p2-" + to_string(i));
    }
    for (int i = startingTokens; i >= 0; --i) {
        Vertex a = "p1-" + to_string(i);
        Vertex b = "p2-" + to_string(i);
        if (i - 1 >= 0) {
            Vertex a1 = "p1-" + to_string(i - 1);
            Vertex b1 = "p2-" + to_string(i - 1);
            g.insertEdge(a, b1);
            g.insertEdge(b, a1);
            g.setEdgeWeight(a, b1, 0);
            g.setEdgeWeight(b, a1, 0);
        }
        if (i - 2 >= 0) {
        Vertex a2 = "p1-" + to_string(i - 2);
        Vertex b2 = "p2-" + to_string(i - 2);
        g.insertEdge(a, b2);
        g.insertEdge(b, a2);
        g.setEdgeWeight(a, b2, 0);
        g.setEdgeWeight(b, a2, 0);
        }
    }
}

/**
 * Plays a random game of Nim, returning the path through the state graph
 * as a vector of `Edge` classes.  The `origin` of the first `Edge` must be
 * the vertex with the label "p1-#", where # is the number of starting
 * tokens.  (For example, in a 10 token game, result[0].origin must be the
 * vertex "p1-10".)
 *
 * @returns A random path through the state space graph.
 */
vector<Edge> NimLearner::playRandomGame() const {
    vector<Edge> path;
    int tokens = g.getVertices().size() / 2 - 1;
    Vertex start = "p1-" + to_string(tokens);
    vector<Vertex> next = g.getAdjacent(start);

    while (!next.empty()) {
      Random R(1);
      R.shuffle(next);
      Edge temp = g.getEdge(start, next[0]);
      path.push_back(temp);
      // set up for the next loop;
      start = next[0];
      next = g.getAdjacent(start);
    }
    return path;
}

/*
 * Updates the edge weights on the graph based on a path through the state
 * tree.
 *
 * If the `path` has Player 1 winning (eg: the last vertex in the path goes
 * to Player 2 with no tokens remaining, or "p2-0", meaning that Player 1
 * took the last token), then all choices made by Player 1 (edges where
 * Player 1 is the source vertex) are rewarded by increasing the edge weight
 * by 1 and all choices made by Player 2 are punished by changing the edge
 * weight by -1.
 *
 * Likewise, if the `path` has Player 2 winning, Player 2 choices are
 * rewarded and Player 1 choices are punished.
 *
 * @param path A path through the a game of Nim to learn.
 */
void NimLearner::updateEdgeWeights(const std::vector<Edge> & path) {
    int plus = 1;
    for (int i = path.size() - 1; i >= 0; --i) {
        Edge edge = path[i];
        if (plus == 1)
            g.setEdgeWeight(edge.source, edge.dest, edge.getWeight() + 1);
        else
            g.setEdgeWeight(edge.source, edge.dest, edge.getWeight() - 1);
        plus *= -1;
    }
}

/**
 * Label the edges as "WIN" or "LOSE" based on a threshold.
 */
void NimLearner::labelEdgesFromThreshold(int threshold) {
  for (const Vertex & v : g.getVertices()) {
    for (const Vertex & w : g.getAdjacent(v)) {
      int weight = g.getEdgeWeight(v, w);

      // Label all edges with positve weights as "WINPATH"
      if (weight > threshold)           { g.setEdgeLabel(v, w, "WIN"); }
      else if (weight < -1 * threshold) { g.setEdgeLabel(v, w, "LOSE"); }
    }
  }
}

/**
 * Returns a constant reference to the state space graph.
 *
 * @returns A constant reference to the state space graph.
 */
const Graph & NimLearner::getGraph() const {
  return g;
}
