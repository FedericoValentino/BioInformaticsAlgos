#include<stdio.h>
#include<stdlib.h>
#include<string>
#include<math.h>
#include <iostream>
#include <vector>

#define GAP_COST 2
#define REPLACE_COST 10

int E(std::string word1, int i, std::string word2, int j, int** table)
{
    if(word1.empty() && word2.empty())
    {
        table[i][j] = 0;
        return 0;
    }
    else if((word1.size() == 1 && word2.empty()) || (word2.size() == 1 && word1.empty()))
    {
        table[i][j] = 1;
        return 1;
    }
    else if(word1.size() == 1 && word2.size() == 1)
    {
        if(word1[0] == word2[0])
        {
            table[i][j] = 0;
            return 0;
        }
        else
        {
            table[i][j] = 1;
            return 1;
        }
    }
    else if(word1.empty())
    {
        table[i][j] = j;
        return j;
    }
    else if(word2.empty())
    {
        table[i][j] = i;
        return i;
    }
    else
    {
        int x= std::min(1 + E(word1.substr(0, i), i, word2.substr(0, j-1) , j-1, table),
                   1 + E(word1.substr(0, i-1), i-1, word2.substr(0, j) , j, table));
        int y = 255;
        if(word1[i-1] == word2[j-1])
        {
            y = E(word1.substr(0, i-1), i-1, word2.substr(0, j-1) , j-1, table);
        }
        else
        {
            y = 1 + E(word1.substr(0, i-1), i-1, word2.substr(0, j-1) , j-1, table);
        }
        table[i][j] = std::min(x, y);
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
       int diagonalScore;
       if(row - 1 >= 0 && col - 1 >= 0)
       {
           diagonalScore = (word1[row-1] == word2[col-1]) ? table[row - 1][col - 1] : table[row - 1][col - 1] + REPLACE_COST;
       }
       else
       {
           diagonalScore = INT32_MAX;
       }
       int upScore;
       if(row - 1 >= 0)
       {
           upScore = table[row - 1][col] + GAP_COST;
       }
       else
       {
           upScore = INT32_MAX;
       }

       int leftScore;
       if(col - 1 >= 0)
       {
           leftScore = table[row][col - 1] + GAP_COST;
       }
       else
       {
           leftScore = INT32_MAX;
       }



       int decision = std::min(std::min(leftScore, upScore), diagonalScore);
       if(decision == upScore)
       {
           std::cout<<"going up"<<std::endl;
           finalWord1.emplace(finalWord1.cbegin(), word1[row - 1]);
           finalWord2.emplace(finalWord2.cbegin(), '-');
           row = row - 1;
           col = col;

           totalCost += GAP_COST;
       }
       else if(decision == leftScore)
       {
           std::cout<<"going left"<<std::endl;
           finalWord2.emplace(finalWord2.cbegin(), word2[col - 1]);
           finalWord1.emplace(finalWord1.cbegin(), '-');
           row = row;
           col = col - 1;

           totalCost += GAP_COST;
       }
       else if(decision == table[row - 1][col - 1])
       {
           std::cout<<"going diag"<<std::endl;
           finalWord1.emplace(finalWord1.cbegin(), word1[row - 1]);
           finalWord2.emplace(finalWord2.cbegin(), word2[col - 1]);
           row = row - 1;
           col = col - 1;

           totalCost += 0;
       }
       else if(decision == table[row - 1][col - 1] + REPLACE_COST)
       {
           std::cout<<"going diag"<<std::endl;
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

std::vector<char> randomWord()
{
    std::vector<char> string;
    bool generating = true;
    while(generating)
    {
        int random = rand() % 5;
        switch(random)
        {
            case 0:
                string.push_back('A');
                break;
            case 1:
                string.push_back('C');
                break;
            case 2:
                string.push_back('T');
                break;
            case 3:
                string.push_back('G');
                break;
            case 4:
                if(!string.empty())
                    generating = false;
                break;
            default:
                generating = false;
                break;
        }

    }
    string.push_back('\0');
    return string;
};

int main()
{
    srand(time(NULL));
    std::string word2 = randomWord().data();
    std::string word1 = randomWord().data();

    int** Edit = (int**)malloc(sizeof(int*) * (word1.size()+1));
    for(int i = 0; i < word1.size()+1; i++)
    {
        Edit[i] = (int*)malloc(sizeof(int) * (word2.size()+1));
    }


    //table base case initialization
    for(int i = 0; i < word1.size()+1; i++)
    {
        Edit[0][i] = i;
        Edit[i][0] = i;
    }

    E(word1, word1.size(),  word2, word2.size(), Edit);

    printTable(Edit, word1, word2);

    backTracking(Edit, word1, word2);

}