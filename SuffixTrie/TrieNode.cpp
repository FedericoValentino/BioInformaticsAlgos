#include "TrieNode.h"

TrieNode::TrieNode()
{
    for(int i = 0; i < ALPHABET_SIZE; i++)
    {
        pointer[i] = nullptr;
    }
}


int TrieNode::getIndex(char c) {
    if(c == '$')
    {
        return 26;
    }
    return c - 'a';
}

TrieNode* TrieNode::followPath(TrieNode *root, const std::string& input)
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


bool TrieNode::hasSubstring(const std::string &input) {
    TrieNode* node = followPath(this, input);

    if(node == nullptr)
    {
        return false;
    }
    else
    {
        return true;
    }
}