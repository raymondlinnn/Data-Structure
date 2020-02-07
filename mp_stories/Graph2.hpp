#include <queue>
#include <algorithm>
#include <string>
#include <list>
#include <unordered_map>
using std::unordered_map;
using std::list;
using std::string;
using std::queue;

/**
 * Returns an std::list of vertex keys that creates any shortest path between `start` and `end`.
 *
 * This list MUST include the key of the `start` vertex as the first vertex in the list, the key of
 * the `end` vertex as the last element in the list, and an ordered list of all vertices that must
 * be traveled along the shortest path.
 *
 * For example, the path a -> c -> e returns a list with three elements: "a", "c", "e".
 *
 * You should use undirected edges. Hint: There are no edge weights in the Graph.
 *
 * @param start The key for the starting vertex.
 * @param end   The key for the ending vertex.
 */
template <class V, class E>
list<string> Graph<V,E>::shortestPath(const string start, const string end) {
    list<string> path;
    // store the parent and whether visited info of each vertex
    unordered_map<string, string> parent;
    // BFS
    queue<string> q;
    q.push(start);
    parent[start] = "START";
    string dest;
    while(!q.empty()) {
        string curr = q.front();
        q.pop();

        list<edgeListIter>& curr_list = adjList.at(curr);
        for (auto& edgeIter : curr_list) {
            // only consider the undirected case
            if ((*edgeIter).get().dest().key() != curr) {
                dest = (*edgeIter).get().dest().key();
            }else{
                dest = (*edgeIter).get().source().key();
            }
            if (parent.find(dest) == parent.end()) {
                // go next
                q.push(dest);
                // mark parent
                parent[dest] = curr;
            }
        }
    }

    path.insert(path.begin(), end);
    dest = parent[end];
    while (dest != start) {
        path.insert(path.begin(), dest);
        dest = parent[dest];
    }
    path.insert(path.begin(), start);

    return path;
}

template <class V, class E>
list<string> Graph<V,E>::dijkstra(const string start) {

}

template <class V, class E>
int Graph<V,E>::count() {
    // find # of connected components
    unordered_map<string, string> parent;
    int count = 0;
    for (auto& pair : adjList) {
        if (parent.find(pair.first) == parent.end()) {
            // do a BFS
            queue<string> q;
            q.push(pair.first);
            parent[pair.first] = "start";
            string dest;
            while (!q.empty()) {
                string curr = q.front();
                q.pop();
                auto& list = adjList.at(curr);
                for (auto& edgeIter : list) {
                    if ((*edgeIter).get().dest().key() != curr) {
                        dest = (*edgeIter).get().dest().key();
                    }else{
                        dest = (*edgeIter).get().source().key();
                    }
                    if (parent.find(dest) == parent.end()) {
                        parent[dest] = curr;
                        q.push(dest);
                    }
                }
            }
            ++count;
        }
    }
    return count;
}
