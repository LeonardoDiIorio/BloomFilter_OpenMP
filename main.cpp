#include <vector>
#include "BloomFilter.h"
#include <chrono>
#include <iostream>
#include <fstream>
#include<omp.h>

using namespace std;

int main()
{
  int maxThreads=12;
  int numTest=1;
 
  ofstream myfile;
  myfile.open ("BloomFilter.csv");
  std::ifstream file("bloomFilter.txt");
  vector<string> legalStrings;
  vector<string> checkStrings;
  std::string str;
  while (std::getline(file, str))
  {
    legalStrings.push_back(str);
    if(rand()%3==2)
    {
        checkStrings.push_back(str);
    }
  }  
  
  for(int k=2;k<maxThreads+1;k+=2)
  {
    omp_set_num_threads(k);
    int time=0;
    BloomFilter test(64131,0.02,legalStrings);
    auto start = chrono::system_clock::now();
    test.computeBloomFilter();   
    test.checkStream(legalStrings);
    auto end = chrono::system_clock::now();
    auto elapsed = chrono::duration_cast<chrono::milliseconds>(end - start);
    time += elapsed.count();
    cout << "\t\tTime: " << time << endl;
    myfile << time<<"\n";  
  }
  myfile.close();
  return 0;
}