#include<stdio.h>
#include<stdlib.h>
#include<string>
#include<math.h>
#include <iostream>
#include <vector>

#define GAP_COST 2
#define REPLACE_COST 10

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
    int row = word1.size();
    int col = word2.size();
    std::vector<char> finalWord1(row);
    std::vector<char> finalWord2(col);

    int totalCost = 0;


    while(!(row == 0 && col == 0))
    {
       //backtrack until at start
       int diagonalScore = (word1[row-1] == word2[col-1]) ? table[row - 1][col - 1] : table[row - 1][col - 1] + REPLACE_COST;
       int upScore = table[row - 1][col] + GAP_COST;
       int leftScore = table[row][col - 1] + GAP_COST;
       int decision = std::min(std::min(leftScore, upScore), diagonalScore);
       if(decision == upScore)
       {
           finalWord1.emplace(finalWord1.cbegin(), word1[row - 1]);
           finalWord2.emplace(finalWord2.cbegin(), '-');
           row = row - 1;
           col = col;

           totalCost += GAP_COST;
       }
       else if(decision == leftScore)
       {
           finalWord2.emplace(finalWord2.cbegin(), word2[col - 1]);
           finalWord1.emplace(finalWord1.cbegin(), '-');
           row = row;
           col = col - 1;

           totalCost += GAP_COST;
       }
       else if(decision == table[row - 1][col - 1])
       {
           finalWord1.emplace(finalWord1.cbegin(), word1[row - 1]);
           finalWord2.emplace(finalWord2.cbegin(), word2[col - 1]);
           row = row - 1;
           col = col - 1;

           totalCost += 0;
       }
       else if(decision == table[row - 1][col - 1] + REPLACE_COST)
       {
           finalWord1.emplace(finalWord1.cbegin(), '*');
           finalWord2.emplace(finalWord2.cbegin(), '*');
           row = row - 1;
           col = col - 1;

           totalCost += REPLACE_COST * 2;
       }

    }

    std::cout<<finalWord1.data()<<std::endl;
    std::cout<<finalWord2.data()<<std::endl;
    std::cout<<"Total Cost: "<<totalCost<<std::endl;
}


int main()
{
    std::string word2 = "AGGGCT";
    std::string word1 = "AGGCA";

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