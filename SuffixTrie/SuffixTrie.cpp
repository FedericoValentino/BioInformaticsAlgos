#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<string>
#include "TrieNode.h"


TrieNode* followPath(TrieNode *root, const std::string& input)
{
    TrieNode* currentNode = root;
    for(char c : input)
    {
        int index = currentNode->getIndex(c);
        if(!currentNode->pointer[index])
        {
            return NULL;
        }
        currentNode = currentNode->pointer[index];
    }
    return currentNode;
}

void insert(TrieNode *root, const std::string& input)
{
    TrieNode* currentNode = root;
    for(char c : input)
    {
        int index = currentNode->getIndex(c);
        if(!currentNode->pointer[index])
        {
            currentNode->pointer[index] = new TrieNode();
        }
        currentNode = currentNode->pointer[index];
    }
}


TrieNode* BuildSuffixTrie(const std::string& input)
{
    auto *root = new TrieNode();
    for(int i = 0; i < input.size(); i++)
    {
        std::string suffix = input.substr(i, input.size() - i);
        insert(root, suffix);
    }
    return root;
}




int main()
{
    std::string input = "mississippi$";
    TrieNode* root = BuildSuffixTrie(input);

    root->hasSubstring("ciao")? printf("true\n") : printf("false\n");

    root->hasSubstring("missi")? printf("true\n") : printf("false\n");
}
