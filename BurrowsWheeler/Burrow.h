#include<stdio.h>
#include<stdlib.h>
#include<string>
#ifndef BIOINFORMATICS_BURROW_H
#define BIOINFORMATICS_BURROW_H


class Burrow {
public:
    std::string original;
    std::string* BWM;
    std::string BWT;
    explicit Burrow(std::string input);
    bool isSubstring(std::string input);
    int Occ(char c, int pos);
    int C(char c);
    int C2(char C);
private:
    void buildBWM();
    void buildBWT();
    int totalChar(char c);
};


#endif //BIOINFORMATICS_BURROW_H
