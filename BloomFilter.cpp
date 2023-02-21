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

BloomFilter::BloomFilter(int setSize,double fp_probability,vector<string> legalStrings)
{
    this->setSize=setSize;
    this->fp_probability=fp_probability;
    this->legalStrings=legalStrings;
}


int BloomFilter::getNumberOfBits(int setSize, double fp_probability)
{
    double m = -(setSize * log(fp_probability))/pow(log(2),2);
    return int(m);
}

int BloomFilter::getHashNumber(int numberOfBits,int setSize)
{
    int k = (numberOfBits/setSize) * log(2);
    return int(k);
}

void BloomFilter::computeBloomFilter()
{
    this->numberOfBits=getNumberOfBits(setSize,fp_probability);
    this->numberOfHash=getHashNumber(numberOfBits,setSize);
    for(int n=0;n<numberOfBits;n++)
    {
        this->bitVector.emplace_back(0);
    }
   #pragma omp parallel for collapse(2)
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
   if(checkString(check[i])==true)
   {
    // cout<<"la stringa"<<" "<<check[i]<<" "<<"è ammessa \n";
   }
   else 
   {
    // cout<<"la stringa"<<" "<<check[i]<<" "<<"non è ammessa \n";
   }
  }
 
}


bool BloomFilter::checkString(string check)
{
    const char* key=&*check.begin();
    for(int j=0;j<numberOfHash;j++)
    {   
        uint32_t h=MurmurHash(key,sizeof(check),j)%numberOfBits;
        if(bitVector[h]==0)
        {
        return false;
        }
    }
    return true;
}



