//
// Created by valef on 18/07/2022.
//

#include "Burrow.h"
#include <cstring>
#include <list>


Burrow::Burrow(std::string input) {
    original = input + '$';
    buildBWM();
    buildBWT();
}

int cmp(const std::string& a, const std::string& b)
{
    return strcmp(a.c_str(), b.c_str()) < 0 ? 1 : 0;
}

void Burrow::buildBWM() {
    BWM = new std::string[original.size()];
    std::string temp = original;
    for(int i = 0; i < temp.size(); i++)
    {
        temp = temp[temp.size()-1] + temp;
        temp.replace(temp.size()-1, 1, "");
        BWM[i] = temp;
    }

    std::sort(BWM, BWM+original.size(), cmp);

    for(int i = 0; i < temp.size(); i++)
    {
        printf("%s\n", BWM[i].c_str());
    }
}

void Burrow::buildBWT() {
    for(int i = 0; i < original.size(); i++)
    {
        std::string temp = BWM[i];
        BWT += temp[temp.size()-1];
    }
    printf("%s\n", BWT.c_str());
}

int Burrow::Occ(char c, int pos)
{
    int totalOccurencies = 0;
    for(int i = 0; i <= pos; i++)
    {
        if(c == BWT[i])
        {
            totalOccurencies++;
        }
    }
    return totalOccurencies;
}

int Burrow::C(char c)
{
    for(int i = 0; i < original.size(); i++)
    {
        if(c == BWM[i][0])
        {
            return i;
        }
    }
}

int Burrow::C2(char c)
{
     c = tolower(c);
    std::string data = BWT;
    std::transform(data.begin(), data.end(), data.begin(),
                   [](unsigned char c){ return std::tolower(c); });
    int alphabet[26] = {0};
    for(int i = 0; i < BWT.size(); i++)
    {
        if(data[i] != '$')
        {
            alphabet[data[i] - 'a']++;
        }
    }
    int total = 0;
    for(int i = (c - 'a') - 1; i >= 0; i--)
    {
        if(alphabet[i] > 0)
        {
            total ++;
        }
    }
    return total;
}


int Burrow::totalChar(char c) {
    int occurencies = 0;
    for(int i = 0; i <= original.size(); i++)
    {
        if(c == BWT[i])
        {
            occurencies++;
        }
    }
    return occurencies;
}


//FM index implementation
bool Burrow::isSubstring(std::string input) {
    if(input == "")
    {
        return true;
    }
    else
    {
        std::list<int> positions;
        std::list<int> nextPositions;
        std::reverse(input.begin(), input.end());
        for(int i = 0; i < input.size(); i++)
        {
            char current = input[i];
            char next = input[i + 1];
            if(i == 0)
            {
                for(int j = 0; j < original.size(); j++)
                {
                    if(BWM[j][0] == current)
                    {
                        positions.push_back(j);
                    }
                }
            }
            if(!positions.empty())
            {
                for(int j : positions)
                {
                    if(BWM[j][original.size()-1] == next)
                    {
                        nextPositions.push_back(Occ(next, j) + C(next) - 1);
                    }
                }
                positions = nextPositions;
                nextPositions.clear();
            }
            if(positions.empty() && input.contains(next))
            {
                return false;
            }
        }
        return true;
    }
}
