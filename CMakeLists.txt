cmake_minimum_required(VERSION 3.22)
project(BioInformatics)

set(CMAKE_CXX_STANDARD 23)

add_executable(HierHolzer HierHolzer/HierHolzer.cpp)

add_executable(Edit EditDistance/EditDistance.cpp)

add_executable(Trie SuffixTrie/SuffixTrie.cpp SuffixTrie/TrieNode.cpp SuffixTrie/TrieNode.h)


add_executable(SuffixArray SuffixArray/SuffixArray.cpp)

add_executable(Bwa BWA/bwa.cpp)

add_executable(burrows BurrowsWheeler/burrows.cpp BurrowsWheeler/Burrow.cpp BurrowsWheeler/Burrow.h)