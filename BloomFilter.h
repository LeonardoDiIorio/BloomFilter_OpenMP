#ifndef BLOOMFILTER_H
#define BLOOMFILTER_H

#include <vector>
#include <string>
#include<omp.h>


using namespace std;

class BloomFilter
{
    private:
    int numberOfBits;
    int numberOfHash;
    vector<string> legalStrings;
    int* bitVector;
    int* output;


    



    public:
    BloomFilter(int numberOfBits,int numberOfHash,vector<string> legalStrings,int* bitVector,int* output);
    void computeBloomFilter();
    //void addElement(string item);
    void checkStream(vector<string> itemSet);
    //bool checkString(string item, int i);

    

};

#endif