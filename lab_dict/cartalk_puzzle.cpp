/**
 * @file cartalk_puzzle.cpp
 * Holds the function which solves a CarTalk puzzler.
 *
 * @author Matt Joras
 * @date Winter 2013
 */

#include <fstream>
#include <iostream>
#include "cartalk_puzzle.h"

using namespace std;

/**
 * Solves the CarTalk puzzler described here:
 * http://www.cartalk.com/content/wordplay-anyone.
 * @return A vector of (string, string, string) tuples
 * Returns an empty vector if no solutions are found.
 * @param d The PronounceDict to be used to solve the puzzle.
 * @param word_list_fname The filename of the word list to be used.
 */
vector<tuple<string, string, string>> cartalk_puzzle(PronounceDict d,
                                    const string& word_list_fname)
{
    vector<string> puzzles;
    ifstream wordsFile(word_list_fname);
    string word;
    if (wordsFile.is_open()) {
        /* Reads a line from `wordsFile` into `word` until the file ends. */
        while (getline(wordsFile, word)) {
            puzzles.push_back(word);
        }
    }

    vector<tuple<string, string, string>> ret;
    for (string& w : puzzles) {
        if (w.length() >= 3){
            string word1 = w.substr(1);
            string word2 = w.substr(0, 1) + w.substr(2);
            if (d.homophones(w, word1) && d.homophones(w, word2)) {
                tuple<string, string, string> temp = make_tuple(w, word1, word2);
                ret.push_back(temp);
            }
        }
    }
    return ret;
}
