#include<stdio.h>
#include<stdlib.h>
#include<string>
#include<math.h>
#include <iostream>


int E(std::string word1, int i, std::string word2, int j)
{
    if(word1.empty() && word2.empty())
    {
        return 0;
    }
    else if((word1.size() == 1 && word2.empty()) || (word2.size() == 1 && word1.empty()))
    {
        return 1;
    }
    else if(word1.size() == 1 && word2.size() == 1)
    {
        if(word1[0] == word2[0])
        {
            return 0;
        }
        else
        {
            return 1;
        }
    }
    else if(word1.empty())
    {
        return j;
    }
    else if(word2.empty())
    {
        return i;
    }
    else
    {
        int x= std::min(1 + E(word1.substr(0, i), i, word2.substr(0, j-1) , j-1),
                   1 + E(word1.substr(0, i-1), i-1, word2.substr(0, j) , j));
        int y = 255;
        if(word1[i-1] == word2[j-1])
        {
            y = E(word1.substr(0, i-1), i-1, word2.substr(0, j-1) , j-1);
        }
        else
        {
            y = 1 + E(word1.substr(0, i-1), i-1, word2.substr(0, j-1) , j-1);
        }
        return std::min(x, y);
    }
}

void printTable(int **table, std::string word1, std::string word2)
{
    std::string temp1 = "-";
    std::string temp2 = " -";

    temp1.append(word1);
    temp2.append(word2);


    for(int j = 0; j < temp2.size(); j++)
    {
        printf("%c ", temp2[j]);
    }
    printf("\n");
    for(int i = 0; i < word1.size() + 1; i++)
    {
        printf("%c ", temp1[i]);
        for(int j = 0; j < word2.size() + 1; j++)
        {
            printf("%d ", table[i][j]);
        }
        printf("\n");
    }
}


void backTracking(int** table, std::string word1, std::string word2)
{

}


int main()
{
    std::string word1 = "sunday";
    std::string word2 = "saturday";

    int** Edit = (int**)malloc(sizeof(int*) * (word1.size()+1));
    for(int i = 0; i < word1.size()+1; i++)
    {
        Edit[i] = (int*)malloc(sizeof(int) * (word2.size()+1));
    }

    for(int i = 0; i < word1.size() + 1; i++)
    {
        for(int j = 0; j < word2.size() + 1; j++)
        {
            Edit[i][j] = E(word1.substr(0,i), i,  word2.substr(0, j), j);
        }
    }

    printTable(Edit, word1, word2);

    backTracking(Edit, word1, word2);

}