/**
 * @file lphashtable.cpp
 * Implementation of the LPHashTable class.
 */
#include "lphashtable.h"
using hashes::hash;

template <class K, class V>
LPHashTable<K, V>::LPHashTable(size_t tsize)
{
    if (tsize <= 0)
        tsize = 17;
    size = findPrime(tsize);
    table = new pair<K, V>*[size];
    should_probe = new bool[size];
    for (size_t i = 0; i < size; i++) {
        table[i] = NULL;
        should_probe[i] = false;
    }
    elems = 0;
}

template <class K, class V>
LPHashTable<K, V>::~LPHashTable()
{
    for (size_t i = 0; i < size; i++)
        delete table[i];
    delete[] table;
    delete[] should_probe;
}

template <class K, class V>
LPHashTable<K, V> const& LPHashTable<K, V>::operator=(LPHashTable const& rhs)
{
    if (this != &rhs) {
        for (size_t i = 0; i < size; i++)
            delete table[i];
        delete[] table;
        delete[] should_probe;

        table = new pair<K, V>*[rhs.size];
        should_probe = new bool[rhs.size];
        for (size_t i = 0; i < rhs.size; i++) {
            should_probe[i] = rhs.should_probe[i];
            if (rhs.table[i] == NULL)
                table[i] = NULL;
            else
                table[i] = new pair<K, V>(*(rhs.table[i]));
        }
        size = rhs.size;
        elems = rhs.elems;
    }
    return *this;
}

template <class K, class V>
LPHashTable<K, V>::LPHashTable(LPHashTable<K, V> const& other)
{
    table = new pair<K, V>*[other.size];
    should_probe = new bool[other.size];
    for (size_t i = 0; i < other.size; i++) {
        should_probe[i] = other.should_probe[i];
        if (other.table[i] == NULL)
            table[i] = NULL;
        else
            table[i] = new pair<K, V>(*(other.table[i]));
    }
    size = other.size;
    elems = other.elems;
}

template <class K, class V>
void LPHashTable<K, V>::insert(K const& key, V const& value)
{
    int idx = hash(key, size);
    for (int i = 0; i < (int)size; ++i) {
        idx = (idx + i) % size;
        if (table[idx] == NULL) {
            table[idx] = new pair<K, V>(key, value);
            should_probe[idx] = true;
            ++elems;
            break;
        }
    }

    if (shouldResize()) {
        resizeTable();
    }
}

template <class K, class V>
void LPHashTable<K, V>::remove(K const& key)
{
    if (size == 0)  return;

    int idx = findIndex(key);
    if (idx != -1) {
        delete table[idx];
        table[idx] = NULL;
        --elems;
        should_probe[idx] = false;
    }
}

template <class K, class V>
int LPHashTable<K, V>::findIndex(const K& key) const
{
    size_t idx = hash(key, size);
    for (int i = 0; i < (int)size; ++i) {
        idx = (idx + i) % size;
        if (table[idx] != NULL && table[idx]->first == key)
            return idx;
    }
    // not in the table
    return -1;
}

template <class K, class V>
V LPHashTable<K, V>::find(K const& key) const
{
    int idx = findIndex(key);
    if (idx != -1)
        return table[idx]->second;
    else
        return V();
}

template <class K, class V>
V& LPHashTable<K, V>::operator[](K const& key)
{
    // First, attempt to find the key and return its value by reference
    int idx = findIndex(key);
    if (idx == -1) {
        // otherwise, insert the default value and return it
        insert(key, V());
        idx = findIndex(key);
    }
    return table[idx]->second;
}

template <class K, class V>
bool LPHashTable<K, V>::keyExists(K const& key) const
{
    return findIndex(key) != -1;
}

template <class K, class V>
void LPHashTable<K, V>::clear()
{
    for (size_t i = 0; i < size; i++)
        delete table[i];
    delete[] table;
    delete[] should_probe;
    table = new pair<K, V>*[17];
    should_probe = new bool[17];
    for (size_t i = 0; i < 17; i++)
        should_probe[i] = false;
    size = 17;
    elems = 0;
}

template <class K, class V>
void LPHashTable<K, V>::resizeTable()
{
    size_t newSize = findPrime(2 * size);
    pair<K, V>** new_tab = new pair<K, V>* [newSize];
    delete[] should_probe;
    should_probe = new bool [newSize];
    for (size_t i = 0; i < newSize; ++i) {
        new_tab[i] = NULL;
        should_probe[i] = false;
    }

    for (size_t i = 0; i < size; ++i) {
        if (table[i] != NULL) {
            size_t idx = hash(table[i]->first, newSize);
            while (new_tab[idx] != NULL) {
                idx = (idx + 1) % newSize;
            }
            new_tab[idx] = table[i];
            should_probe[idx] = true;
        }
    }
    delete[] table;
    size = newSize;
    table = new_tab;
}


/*

template <class K, class V>
void LPHashTable<K, V>::insert(K const& key, V const& value)
{
    size_t idx = hash(key, size);
    for (size_t i = 0; i < size; ++i){
        idx = (idx + i) % size;
        if (table[idx] == NULL) {
            table[idx] = new pair<K, V>(key, value);
            should_probe[idx] = true;
            break;
        }
    }
    ++elems;
    if (shouldResize())
        resizeTable();
}

template <class K, class V>
void LPHashTable<K, V>::remove(K const& key)
{
    if (size == 0)
        return;

    if(keyExists(key)){
        size_t idx = findIndex(key);
        delete table[idx];
        table[idx] = NULL;
        should_probe[idx] = false;
        --elems;
    }
}

template <class K, class V>
int LPHashTable<K, V>::findIndex(const K& key) const
{
    size_t idx = hash(key, size);
    for (size_t i = 0; i < size; ++i){
        idx = (idx + i) % size;
        if (table[idx] != NULL && table[idx]->first == key)
            return idx;
    }
    // loop after "size" times, can't find
    return -1;
}

template <class K, class V>
V LPHashTable<K, V>::find(K const& key) const
{
    int idx = findIndex(key);
    if (idx != -1)
        return table[idx]->second;
    return V();
}

template <class K, class V>
V& LPHashTable<K, V>::operator[](K const& key)
{
    // First, attempt to find the key and return its value by reference
    int idx = findIndex(key);
    if (idx == -1) {
        // otherwise, insert the default value and return it
        insert(key, V());
        idx = findIndex(key);
    }
    return table[idx]->second;
}

template <class K, class V>
bool LPHashTable<K, V>::keyExists(K const& key) const
{
    return findIndex(key) != -1;
}

template <class K, class V>
void LPHashTable<K, V>::clear()
{
    for (size_t i = 0; i < size; i++)
        delete table[i];
    delete[] table;
    delete[] should_probe;
    table = new pair<K, V>*[17];
    should_probe = new bool[17];
    for (size_t i = 0; i < 17; i++)
        should_probe[i] = false;
    size = 17;
    elems = 0;
}

template <class K, class V>
void LPHashTable<K, V>::resizeTable()
{
    pair<K, V>** temp = new pair<K, V>* [size];
    size_t i;
    for (i = 0; i < size; i++) {
        temp[i] = NULL;
        if (table[i] != NULL)
            temp[i] = new pair<K, V>(*table[i]);
        delete table[i];
        table[i] = NULL;
    }
    delete[] table;
    delete[] should_probe;
    // store old size
    size_t old_size = size;
    // resize and set default value
    size = findPrime(2 * size);
    table = new pair<K, V>* [size];
    should_probe = new bool[size];
    for (i = 0; i < size; ++i) {
        table[i] = NULL;
        should_probe[i] = false;
    }
    // rehash
    for (i = 0; i < old_size; ++i) {
        if (temp[i] != NULL)
            insert(temp[i]->first, temp[i]->second);
    }
    // clean-up
    for (i = 0; i < old_size; i++) {
        delete temp[i];
    }
    delete[] temp;
}
*/
