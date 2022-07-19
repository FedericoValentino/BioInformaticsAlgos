#include <stdio.h>
#include <stdlib.h>
#include "../BurrowsWheeler/Burrow.h"
#include "../BurrowsWheeler/Burrow.cpp"

int* CalculateDepth(std::string W, Burrow* BWT)
{
    int z = 0;
    int j = 0;
    int* D = new int[W.size()];
    for(int i = 0; i < W.size(); i++)
    {
        std::string temp = W.substr(j, i);
        if(!BWT->isSubstring(temp))
        {
            z++;
            j = i + 1;
        }
        D[i] = z;
    }
    return D;
}


std::list<int> InexRecur(std::string W, int i, int z, int k, int l, int* D, Burrow* BWT)
{
    if(z < D[i])
    {
        return {};
    }
    if(i < 0)
    {
        return {k, l};
    }
    std::list<int> L = {};
    for(char C : {'G', 'O', 'L'})
    {
        k = BWT -> C2(C) + BWT -> Occ(C, k - 1) + 1;
        l = BWT -> C2(C) + BWT -> Occ(C, l);
        if(k <= l)
        {
            if(C == W[i])
            {
                L.merge(InexRecur(W, i-1, z, k, l, D, BWT));
            }
            else
            {
                L.merge(InexRecur(W, i-1, z-1, k, l, D, BWT));
            }
        }
    }
    return L;
}

//NOT WORKING ATM
int main()
{
    Burrow* GOOGOL = new Burrow("GOOGOL");
    std::string W = "GOL";
    int z = 1;
    int *D = CalculateDepth(W, GOOGOL);
    std::list<int> L = InexRecur(W, W.size()-1, z, 1, GOOGOL->original.size()-1, D, GOOGOL);

    for(int i : L)
    {
        printf("%d\n", i);
    }
}
