#include <stdio.h>
#include <string>
#include <cstring>

struct suffix{
    int index{};
    std::string suffix;
};
typedef struct suffix suffixNode;


int cmp(const suffixNode& a, const suffixNode& b)
{
    return strcmp(a.suffix.c_str(), b.suffix.c_str()) < 0 ? 1 : 0;
}

suffixNode* buildSuffixArray(const std::string& input)
{
    auto *suffixes = new suffixNode[input.size()];

    for(int i = 0; i < input.size(); i++)
    {
        suffixes[i].suffix = input.substr(i, input.size() - i);
        suffixes[i].index = i;
    }

    std::sort(suffixes, suffixes+input.size(), cmp);

    return suffixes;
}

char compute(std::string input, suffixNode node)
{
    if(node.index > 0)
    {
        return input[node.index-1];
    }
    else if(node.index == 0)
    {
        return '$';
    }
}


int main()
{
    //suffix array construction
    std::string input = "abracadabra$";
    suffixNode* array = buildSuffixArray(input);

    for(int i = 0; i < input.size(); i++)
    {
        printf("%d, %s\n", array[i].index, array[i].suffix.c_str());
    }

    //Burrows-Wheeler Transform from suffix array
    std::string BWT = "";

    for(int i = 0; i < input.size(); i++)
    {
        BWT += compute(input, array[i]);
    }

    printf("%s\n", BWT.c_str());
}