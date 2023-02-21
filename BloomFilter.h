#ifndef BLOOMFILTER_H
#define BLOOMFILTER_H

#include <vector>
#include <string>
#include<omp.h>


using namespace std;

class BloomFilter
{
    private:
    double fp_probability;
    int setSize;
    int numberOfBits;
    int numberOfHash;
    vector<string> legalStrings;
    vector<int> bitVector;

    



    public:
    BloomFilter(int setSize,double fp_probability,vector<string> legalStrings);
    int getNumberOfBits(int setSize, double fp_probability);
    int getHashNumber(int numberOfBits,int setSize);
    void computeBloomFilter();
    void addElement(string item);
    void checkStream(vector<string> itemSet);
    bool checkString(string item);

    

};

#endif