#ifndef SEARCH_H
#define SEARCH_H

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include "redblacktree.h"

string toLowerCase(string s);

void search(const std::string& query, const std::unordered_map<std::string, std::vector<song>>& artistMap,
            const std::unordered_map<std::string, std::vector<song>>& genreMap, const RBTree& songTree,
            const RBTree& albumTree, bool includeExplicit, const std::string& searchType);

#endif // SEARCH_H
