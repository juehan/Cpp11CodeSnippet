/**************************************************************************
* ConcurrencyRT_parallel_for_each.cpp: PPL Performace check 
* 
* Authors: Lee Jue Han <to.johnny.lee@gmail.com>
* First created: 23. Jun. 2012
* Last modified: 23. Jun. 2012

* Description: This code is to see if Microsoft's Parallel Pattern Library
	performs well. Actually PPL has no relevance with C++11 but other than 
	PPL code part, it used C++11 standard API such as random.
	This is only for my personal research.
	As PPL is Microsoft Proprietary API that this code is run on Microsoft 
	Visual Studio 2010 (VC++10.0) environment and there is no portability
	with OS-X or *nix.

**************************************************************************/

#include <ppl.h> //parallel_for_each()
#include <iostream>
#include <vector>
#include <algorithm> //for_each()
#include <time.h> //clock()
#include <random> //uniform_int_distribution, mt19937

#define _CASE1_

#ifdef _CASE1_
const int DATA_SET_SIZE = 1000;
#elif //_CASE2_
const int DATA_SET_SIZE = 100000;
#endif

//Generate random number

std::vector<int> getRandomArr()
{
	std::vector<int> v;
	std::uniform_int_distribution<int> dis(0, DATA_SET_SIZE);
	std::mt19937 engine;
	auto generator = std::bind(dis, engine);

	for(int i = 0; i < DATA_SET_SIZE; i++)
	{
		v.push_back(generator());
	}
	return v;
}

int main()
{ 
	//1. Prepare dataset
	auto v = getRandomArr(); 
	
	//2. Test performance of sequential process
	std::cout<<"Seqential process ------------ "<<std::endl;
	clock_t start = clock(); //start 
	std::for_each(v.begin(), v.end(), [&](double n) {
		for(int i = 0; i < n; i++)
		{ 
			double k = n*n;
		}
	});
	clock_t finish = clock(); //end
	double time = (double)(finish - start) / CLOCKS_PER_SEC;
	std::cout<<"Elapsed time for Sequential : "<<time<<std::endl;
	
	//3. Test performance of parallel process	
	std::cout<<"\n\nparallel process ------------ "<<std::endl;
	start = clock();//start 
	Concurrency::parallel_for_each(v.begin(), v.end(), [&](double n){
		for(int i = 0; i < n; i++)
		{ 
			double k = n*n;
		}
	});
	finish = clock();//end
	time = (double)(finish - start) / CLOCKS_PER_SEC;
	std::cout<<"Elapsed time for PPL : "<<time<<std::endl;
	
	return 0;
}


/*
Result

Case 1.
INPUT:
data size is 1000

OUTPUT 1 (In case of Intel Core i7 (8 core))
Seqential process ------------
Elapsed time for Serial : 0.001

parallel process ------------
Elapsed time for PPL : 0.003
Press any key to continue . . .

OUTPUT 2 (In case of Intel Core 2 Duo (2 core))
Seqential process ------------
Elapsed time for Sequential : 0.015

parallel process ------------
Elapsed time for PPL : 0.033





Case 2.
INPUT:
data size is 100000

OUTPUT 1 (In case of Intel Core i7 (8 core))
Seqential process ------------
Elapsed time for Serial : 10.036

parallel process ------------
Elapsed time for PPL : 1.987
Press any key to continue . . .


OUTPUT 2 (In case of Intel Core 2 Duo (2 core))
Seqential process ------------
Elapsed time for Sequential : 18.378


parallel process ------------
Elapsed time for PPL : 9.718

*/
