#include <stdlib.h>
#include <string>
#include <iostream>
#include <vector>
#include <cstdint>


int E(std::string word1, int i, std::string word2, int j, int** table, int gapCost, int replaceCost)
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
        int x= std::min(gapCost + E(word1.substr(0, i), i, word2.substr(0, j-1) , j-1, table, gapCost, replaceCost),
                        gapCost + E(word1.substr(0, i-1), i-1, word2.substr(0, j) , j, table, gapCost, replaceCost));
        int y = 255;
        if(word1[i-1] == word2[j-1])
        {
            y = E(word1.substr(0, i-1), i-1, word2.substr(0, j-1) , j-1, table, gapCost, replaceCost);
        }
        else
        {
            y = replaceCost*2 + E(word1.substr(0, i-1), i-1, word2.substr(0, j-1) , j-1, table, gapCost, replaceCost);
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


void backTracking(int** table, std::string word1, std::string word2, int gapCost, int replaceCost)
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
            diagonalScore = (word1[row-1] == word2[col-1]) ? table[row - 1][col - 1] : table[row - 1][col - 1] + replaceCost*2;
        }
        else
        {
            diagonalScore = INT32_MAX;
        }
        int upScore;
        if(row - 1 >= 0)
        {
            upScore = table[row - 1][col] + gapCost;
        }
        else
        {
            upScore = INT32_MAX;
        }

        int leftScore;
        if(col - 1 >= 0)
        {
            leftScore = table[row][col - 1] + gapCost;
        }
        else
        {
            leftScore = INT32_MAX;
        }



        int decision = std::min(std::min(leftScore, upScore), diagonalScore);
        if(decision == upScore)
        {
            finalWord1.emplace(finalWord1.cbegin(), word1[row - 1]);
            finalWord2.emplace(finalWord2.cbegin(), '-');
            row = row - 1;
            col = col;

            totalCost += gapCost;
        }
        else if(decision == leftScore)
        {
            finalWord2.emplace(finalWord2.cbegin(), word2[col - 1]);
            finalWord1.emplace(finalWord1.cbegin(), '-');
            row = row;
            col = col - 1;

            totalCost += gapCost;
        }
        else if(decision == table[row - 1][col - 1])
        {
            finalWord1.emplace(finalWord1.cbegin(), word1[row - 1]);
            finalWord2.emplace(finalWord2.cbegin(), word2[col - 1]);
            row = row - 1;
            col = col - 1;

            totalCost += 0;
        }
        else if(decision == table[row - 1][col - 1] + replaceCost*2)
        {
            finalWord1.emplace(finalWord1.cbegin(), '*');
            finalWord2.emplace(finalWord2.cbegin(), '*');
            row = row - 1;
            col = col - 1;

            totalCost += replaceCost * 2;
        }

    }

    std::cout<<finalWord1.data()<<std::endl;
    std::cout<<finalWord2.data()<<std::endl;
    std::cout<<"Total Cost: "<<totalCost<<std::endl;
}

std::vector<char> randomWord(int len)
{
    std::vector<char> string;
    for(int i = 0; i < len; i++)
    {
        int random = rand() % 4;
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
            default:
                break;
        }

    }
    string.push_back('\0');
    return string;
};

int main(int argc, char* argv[])
{
    if(argc != 5)
    {
        std::cout<<"Usage: ./<exec_name> firstStringLen secondStringLen gapCost replaceCost";
        exit(0);
    }

    int len1 = atoi(argv[1]);
    int len2 = atoi(argv[2]);
    int gapCost = atoi(argv[3]);
    int replaceCost = atoi(argv[4]);


    srand(time(NULL));

    std::string word1 = randomWord(len1).data();
    std::string word2 = randomWord(len2).data();


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

    E(word1, word1.size(),  word2, word2.size(), Edit, gapCost, replaceCost);

    printTable(Edit, word1, word2);

    backTracking(Edit, word1, word2, gapCost, replaceCost);

}