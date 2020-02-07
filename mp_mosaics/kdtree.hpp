/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */

#include <utility>
#include <algorithm>
#include <cmath>

using namespace std;

template <int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim>& first,
                                const Point<Dim>& second, int curDim) const
{
    if (first[curDim] == second[curDim])
        return (first < second);
    else
        return (first[curDim] < second[curDim]);
}

template <int Dim>
double KDTree<Dim>::distance(const Point<Dim>& f, const Point<Dim>& s) const{
    double dst = 0;
    for (int i = 0; i < Dim; ++i)
        dst += (f[i] - s[i]) * (f[i] - s[i]);
    return dst;
}

template <int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim>& target,
                                const Point<Dim>& currentBest,
                                const Point<Dim>& potential) const
{

    if (distance(target, potential) == distance(target, currentBest))
        return (potential < currentBest);
    else
        return (distance(target, potential) < distance(target, currentBest));
}

// quickselect helper functions

template <int Dim>
int KDTree<Dim>::partition(vector<Point<Dim>>& vec, int L, int R, int d) {
    // choose the Right-most as pivot
    Point<Dim> pivot = vec[R];
    int i = L;
    // keep the pivot safe
    for (int j = L; j < R; ++j) {
        // i tries to point to a point which is bigger than pivot
        if (smallerDimVal(vec[j], pivot, d)){
            swap(vec[i], vec[j]);
            ++i;
        }
    }
    // at last, swap the pivot with its position
    swap(vec[i], vec[R]);
    return i; // return the final position
}

template <int Dim>
Point<Dim> KDTree<Dim>::KthSmallest(vector<Point<Dim>>& vec,int L, int R, int k, int d){
    int idx = partition(vec, L, R, d);
    if (idx - L + 1 == k) {
        return vec[idx];
    }else if (idx - L + 1 < k) {
        // work on right part
        return KthSmallest(vec, idx + 1, R, k - (idx - L + 1), d);
    }else{ // idx > k, work on the left part
        return KthSmallest(vec, L, idx - 1, k, d);
    }
}

template <int Dim>
void KDTree<Dim>::build_helper(KDTreeNode*& subroot, vector<Point<Dim>>& saved, int d)
{
    size_t size = saved.size();
    if (size == 0)
        return;

    if (size % 2 == 1)
        size++;

    size_t M = size / 2;
    Point<Dim> median = KthSmallest(saved, 0, saved.size() - 1 , M, d);
    subroot = new KDTreeNode(median);

    if (M > 1) {
        vector<Point<Dim>> left;
        left.assign(saved.begin(), saved.begin() + M - 1);
        build_helper(subroot->left, left, (d+1) % Dim);
        for (size_t i = 0; i < left.size(); ++i)
            swap(left[i], saved[i]);
    }
    if (M < saved.size()) {
        vector<Point<Dim>> right;
        right.assign(saved.begin() + M, saved.end());
        build_helper(subroot->right, right, (d+1) % Dim);
        for (size_t i = 0; i < right.size(); ++i)
            swap(right[i], saved[i + M]);
    }
}

template <int Dim>
KDTree<Dim>::KDTree(const vector<Point<Dim>>& newPoints)
{
    saved.assign(newPoints.begin(), newPoints.end());
    root = NULL;
    size = saved.size();
    build_helper(root, saved, 0);
}

template <int Dim>
KDTree<Dim>::KDTree(const KDTree<Dim>& other) {
    size = other.size;
    root = NULL;
    copy(root, other.root);
}

template <int Dim>
void KDTree<Dim>::copy(KDTreeNode*& subroot, const KDTreeNode* other)
{
    if (other == NULL)
        return;

    // when other != null
    subroot = new KDTreeNode (other->point);
    copy(subroot->left, other->left);
    copy(subroot->right, other->right);
}

template <int Dim>
const KDTree<Dim>& KDTree<Dim>::operator=(const KDTree<Dim>& rhs) {
    if (this != &rhs) {
        clear(root);
        size = rhs.size;
        copy_helper(root, rhs.root);
    }
    return *this;
}

template <int Dim>
void KDTree<Dim>::clear(KDTreeNode* subroot)
{
    if (subroot == NULL)
        return;

    // when other != null
    clear(subroot->left);
    clear(subroot->right);
    delete subroot;
}

template <int Dim>
KDTree<Dim>::~KDTree() {
    clear(root);
}

template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query)
{
    return neighbor(query, root, 0);
}

template <int Dim>
Point<Dim> KDTree<Dim>::neighbor(const Point<Dim>& query,
    const KDTreeNode* subroot, int d)
{

    // base case 1
    if (subroot->left == NULL && subroot->right == NULL)
        return subroot->point;
    // none leaf case
    Point<Dim> temp, currentBest;
    bool went_left = true;
    if (smallerDimVal(query, subroot->point, d)) {
        if (subroot->left != NULL)
            temp = neighbor(query, subroot->left, (d+1) % Dim);
    }else{
        if (subroot->right != NULL)
            temp = neighbor(query, subroot->right, (d+1) % Dim);
        went_left = false;
    }
    currentBest = temp;
    replace(query, currentBest, subroot->point);

    double dst1 = (query[d] - subroot->point[d]) * (query[d] - subroot->point[d]);
    double dst2 = distance(currentBest, query);

    if (dst1 <= dst2){
        KDTreeNode* check = went_left ? subroot->right : subroot->left;
        if (check != NULL) {
            temp = neighbor(query, check, (d+1) % Dim);
            replace(query, currentBest, temp);
        }
    }
    return currentBest;
}


template <int Dim>
void KDTree<Dim>::replace(const Point<Dim>& query,
    Point<Dim>& currentBest, const Point<Dim>& potential)
{
    if (shouldReplace(query, currentBest, potential)) {
        currentBest = potential;
    }
}
