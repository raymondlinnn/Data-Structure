/**
 * @file schashtable.cpp
 * Implementation of the SCHashTable class.
 */

#include "schashtable.h"
using hashes::hash;

template <class K, class V>
SCHashTable<K, V>::SCHashTable(size_t tsize)
{
    if (tsize <= 0)
        tsize = 17;
    size = findPrime(tsize);
    table = new list<pair<K, V>>[size];
    elems = 0;
}

template <class K, class V>
SCHashTable<K, V>::~SCHashTable()
{
    delete[] table;
}

template <class K, class V>
SCHashTable<K, V> const& SCHashTable<K, V>::
operator=(SCHashTable<K, V> const& rhs)
{
    if (this != &rhs) {
        delete[] table;
        table = new list<pair<K, V>>[rhs.size];
        for (size_t i = 0; i < rhs.size; i++)
            table[i] = rhs.table[i];
        size = rhs.size;
        elems = rhs.elems;
    }
    return *this;
}

template <class K, class V>
SCHashTable<K, V>::SCHashTable(SCHashTable<K, V> const& other)
{
    table = new list<pair<K, V>>[other.size];
    for (size_t i = 0; i < other.size; i++)
        table[i] = other.table[i];
    size = other.size;
    elems = other.elems;
}

template <class K, class V>
void SCHashTable<K, V>::insert(K const& key, V const& value)
{
    size_t idx = hashes::hash(key, size);
    table[idx].push_front(make_pair(key, value));
    ++elems;
    if (shouldResize())
        resizeTable();
}

template <class K, class V>
void SCHashTable<K, V>::remove(K const& key)
{
    if (elems == 0)
        return;

    size_t idx = hashes::hash(key, size);
    typename list<pair<K, V>>::iterator it;
    for (it = table[idx].begin(); it != table[idx].end(); it++) {
        if (it->first == key){
            table[idx].erase(it);
            break;
        }
    }
    --elems;
}

template <class K, class V>
V SCHashTable<K, V>::find(K const& key) const
{
    size_t idx = hashes::hash(key, size);
    typename list<pair<K, V>>::iterator it;
    for (it = table[idx].begin(); it != table[idx].end(); it++) {
        if (it->first == key)
            return it->second;
    }
    // if the key is not found
    return V();
}

template <class K, class V>
V& SCHashTable<K, V>::operator[](K const& key)
{
    size_t idx = hash(key, size);
    typename list<pair<K, V>>::iterator it;
    for (it = table[idx].begin(); it != table[idx].end(); it++) {
        if (it->first == key)
            return it->second;
    }

    // was not found, insert a default-constructed version and return it
    ++elems;
    if (shouldResize())
        resizeTable();

    idx = hash(key, size);
    pair<K, V> p(key, V());
    table[idx].push_front(p);
    return table[idx].front().second;
}

template <class K, class V>
bool SCHashTable<K, V>::keyExists(K const& key) const
{
    size_t idx = hash(key, size);
    typename list<pair<K, V>>::iterator it;
    for (it = table[idx].begin(); it != table[idx].end(); it++) {
        if (it->first == key)
            return true;
    }
    return false;
}

template <class K, class V>
void SCHashTable<K, V>::clear()
{
    delete[] table;
    table = new list<pair<K, V>>[17];
    size = 17;
    elems = 0;
}

template <class K, class V>
void SCHashTable<K, V>::resizeTable()
{
    list<pair<K, V>>* temp_table;
    temp_table = new list<pair<K, V>> [size];
    typename list<pair<K, V>>::iterator it;
    // copy everything to the temporart table
    for (size_t i = 0; i < size; ++i){
        for (it = table[i].begin(); it != table[i].end(); ++it){
            temp_table[i].push_front(*it);
        }
    }
    // double the size of old table
    delete[] table;
    size_t old_size = size;
    size = findPrime(2 * size);
    table = new list<pair<K, V>> [size];
    for (size_t i = 0; i < old_size; ++i){
        for (it = temp_table[i].begin(); it != temp_table[i].end(); ++it){
            insert(it->first, it->second);
        }
    }
    delete[] temp_table;
}
