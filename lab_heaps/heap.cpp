
/**
 * @file heap.cpp
 * Implementation of a heap class.
 */
using std::swap;

template <class T, class Compare>
size_t heap<T, Compare>::root() const
{
    return 1;
}

template <class T, class Compare>
size_t heap<T, Compare>::leftChild(size_t currentIdx) const
{
    return (currentIdx * 2);
}

template <class T, class Compare>
size_t heap<T, Compare>::rightChild(size_t currentIdx) const
{
    return (currentIdx * 2 + 1);
}

template <class T, class Compare>
size_t heap<T, Compare>::parent(size_t currentIdx) const
{
    size_t idx = currentIdx / 2;
    if (idx >= 1)
        return idx;
    else
        return currentIdx;
}

template <class T, class Compare>
bool heap<T, Compare>::hasAChild(size_t currentIdx) const
{
    return (2 * currentIdx) <= _elems.size() - 1;
}

template <class T, class Compare>
size_t heap<T, Compare>::maxPriorityChild(size_t curr) const
{
    if (!hasAChild(curr))
        return size_t();

    size_t left = 2 * curr, right = left + 1;
    if (right <= _elems.size() - 1) {
        if (higherPriority(_elems[left], _elems[right])) {
            return left;
        }else{
            return right;
        }
    }else{
        return left;
    }
}

template <class T, class Compare>
void heap<T, Compare>::heapifyDown(size_t curr)
{
    if (!hasAChild(curr))
        return;

    size_t child = maxPriorityChild(curr);
    if (higherPriority(_elems[child], _elems[curr])) {
        swap(_elems[child], _elems[curr]);
        heapifyDown(child);
    }
}

template <class T, class Compare>
void heap<T, Compare>::heapifyUp(size_t curr)
{
    if (curr <= 1)
        return;

    size_t p = parent(curr);
    if (higherPriority(_elems[curr], _elems[p])) {
        swap(_elems[curr], _elems[p]);
        heapifyUp(p);
    }
}

template <class T, class Compare>
heap<T, Compare>::heap()
{
    _elems.push_back(T());
}

template <class T, class Compare>
heap<T, Compare>::heap(const vector<T>& elems)
{
    _elems.push_back(T());
    for (auto e : elems)
        _elems.push_back(e);

    size_t none_leaf = _elems.size() - 1;
    while (!hasAChild(none_leaf) && none_leaf != 1) {
        --none_leaf;
    }
    for (size_t i = none_leaf; i >= 1; --i)
        heapifyDown(i);
}

template <class T, class Compare>
T heap<T, Compare>::pop()
{
    if (empty())
        return T();

    T ret = _elems[1];
    swap(_elems[1], _elems[_elems.size() - 1]);
    _elems.pop_back();

    if (!empty())
        heapifyDown(1);
    return ret;
}

template <class T, class Compare>
T heap<T, Compare>::peek() const
{
    if (!empty())
        return _elems[1];
    else
        return T();
}

template <class T, class Compare>
void heap<T, Compare>::push(const T& elem)
{
    _elems.push_back(elem);
    heapifyUp(_elems.size() - 1);
}

template <class T, class Compare>
void heap<T, Compare>::updateElem(const size_t & idx, const T& elem)
{
    T curr = _elems[idx];
    _elems[idx] = elem;
    if (higherPriority(elem, curr))
        heapifyUp(idx);
    else
        heapifyDown(idx);
}


template <class T, class Compare>
bool heap<T, Compare>::empty() const
{
    return _elems.size() == 1;
}

template <class T, class Compare>
void heap<T, Compare>::getElems(vector<T> & heaped) const
{
    for (size_t i = root(); i < _elems.size(); i++) {
        heaped.push_back(_elems[i]);
    }
}
