#include "calculator/TokenEmplacerForRpn.h"

#include <iostream>

void TokenEmplacerForRpn::reset() { queue.clear(); }

void TokenEmplacerForRpn::emplace(TokenPtr&& token) { queue.push_back(token); }

TokenQueue TokenEmplacerForRpn::extract() { return std::move(queue); }