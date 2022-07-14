#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<string>


#ifndef BIOINFORMATICS_TRIENODE_H
#define BIOINFORMATICS_TRIENODE_H

#define ALPHABET_SIZE 27



class TrieNode{
public:
    TrieNode();
    TrieNode *pointer[ALPHABET_SIZE];
    int getIndex(char c);
    bool hasSubstring(const std::string& input);
private:
    TrieNode* followPath(TrieNode *root, const std::string& input);
};


#endif //BIOINFORMATICS_TRIENODE_H
