#include "BloomFilter.h"
#include "MurmurHash.h"

#include <iostream>
#include <cmath>
#include <vector>
#include <bitset> 
#include <string>
#include <omp.h>
#include<random>

using namespace std;

BloomFilter::BloomFilter(int numberOfBits,int numberOfHash,vector<string> legalStrings,int* bitVector,int*output)
{
    this->numberOfBits=numberOfBits;
    this->numberOfHash=numberOfHash;
    this->legalStrings=legalStrings;
    this->bitVector=bitVector;
    this->output=output;
}



void BloomFilter::computeBloomFilter()
{
#pragma omp parallel for 
    for(int i=0;i<legalStrings.size();i++)
    {
        for(int j=0;j<numberOfHash;j++)
        {
        uint32_t h=MurmurHash(&*legalStrings[i].begin(),sizeof(legalStrings[i]),j)%numberOfBits;
        this->bitVector[h]=1;
        }
    } 

}


void BloomFilter::checkStream(vector<string> check)
{
#pragma omp parallel for
  for(int i=0;i<check.size();i++)
  {
     for(int j=0;j<numberOfHash;j++)
    {   
        uint32_t h=MurmurHash(&*check[i].begin(),sizeof(check[i]),j)%numberOfBits;
        if(bitVector[h]==0)
        {
          this->output[i]=0;
        }
    } 
  }
 
}


