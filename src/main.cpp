#include <vector>
#include "BloomFilter.h"
#include <chrono>
#include <cmath>
#include <iostream>
#include <fstream>
#include<omp.h>

using namespace std;

int getNumberOfBits(int setSize, double fp_probability);
int getHashNumber(int numberOfBits,int setSize);

int main()
{
  int maxThreads=12;
  int numTest=1;
 
  ofstream myfile;
  myfile.open ("BloomFilter.csv");
  std::ifstream file("bloomFilterLarge.txt");
  vector<string> legalStrings;
  vector<string> checkStrings;
  std::string str;
  while (std::getline(file, str))
  {
    legalStrings.push_back(str);
    if(rand()%4==1)
    {
    checkStrings.push_back(str);
    }
  } 

  int numberOfBits=getNumberOfBits(legalStrings.size(),0.02);
  int numHashFunctions=getHashNumber(numberOfBits,legalStrings.size());
  int* bitVector=new int[numberOfBits]{0};
  int* output= new int[checkStrings.size()];

  for(int i=0;i<checkStrings.size();i++)
  {
    output[i]=1;
  }

  for(int k=2;k<maxThreads+1;k+=2)
  {    
    omp_set_num_threads(k);
    int time=0;
    BloomFilter test(numberOfBits,numHashFunctions,legalStrings,bitVector,output);
    auto start = chrono::system_clock::now();
    test.computeBloomFilter();   
    test.checkStream(checkStrings);
    auto end = chrono::system_clock::now();
    auto elapsed = chrono::duration_cast<chrono::milliseconds>(end - start);
    time += elapsed.count();
    cout << "\t\tTime: " << time << endl;
    myfile << time<<"\n";  
  }
  myfile.close();
  return 0;
}


int getNumberOfBits(int setSize, double fp_probability)
{
    double m = -(setSize * log(fp_probability))/pow(log(2),2);
    return int(m);
}

int getHashNumber(int numberOfBits,int setSize)
{
    int k = (numberOfBits/setSize) * log(2);
    return int(k);
}