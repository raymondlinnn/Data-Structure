/**
 * @file anagram_dict.cpp
 * Implementation of the AnagramDict class.
 *
 * @author Matt Joras
 * @date Winter 2013
 */

#include "anagram_dict.h"

#include <algorithm> /* I wonder why this is included... */
#include <fstream>

using std::string;
using std::vector;
using std::ifstream;
using std::sort;
using std::map;

/**
 * Constructs an AnagramDict from a filename with newline-separated
 * words.
 * @param filename The name of the word list file.
 */
AnagramDict::AnagramDict(const string& filename)
{
    vector<string> words;
    ifstream File(filename);
    string word;
    if (File.is_open()) {
        while (getline(File, word)) {
            words.push_back(word);
        }
    }
    for (string& w : words) {
        string temp = w;
        sort(temp.begin(), temp.end());
        dict[temp].push_back(w);
    }
}

/**
 * Constructs an AnagramDict from a vector of words.
 * @param words The vector of strings to be used as source words.
 */
AnagramDict::AnagramDict(const vector<string>& words)
{
    for (auto w : words) {
        string temp = w;
        sort(temp.begin(), temp.end());
        dict[temp].push_back(w);
    }
}

/**
 * @param word The word to find anagrams of.
 * @return A vector of strings of anagrams of the given word. Empty
 * vector returned if no anagrams are found or the word is not in the
 * word list.
 */
vector<string> AnagramDict::get_anagrams(const string& word) const
{
    string temp = word;
    sort(temp.begin(), temp.end());
    auto it = dict.find(temp);
    if (it != dict.end()){
        return it->second;
    }else{
        vector<string> v;
        return v;
    }
}

/**
 * @return A vector of vectors of strings. Each inner vector contains
 * the "anagram siblings", i.e. words that are anagrams of one another.
 * NOTE: It is impossible to have one of these vectors have less than
 * two elements, i.e. words with no anagrams are ommitted.
 */
vector<vector<string>> AnagramDict::get_all_anagrams() const
{
    vector<vector<string>> v;
    for (auto it : dict) {
        if (it.second.size() >= 2)
            v.push_back(it.second);
    }
    return v;
}
