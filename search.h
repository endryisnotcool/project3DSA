#ifndef PROJECT3DSA_SEARCH_H
#define PROJECT3DSA_SEARCH_H

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include "redblacktree.h"

using namespace std;

string toLowerCase(string s);

string search(const string& query, const unordered_map<string, vector<song>>& artistMap,
            const unordered_map<string, vector<song>>& genreMap, RBTree songTree,
            RBTree albumTree, bool includeExplicit, const string& searchType);

#endif // PROJECT3DSA_SEARCH_H
