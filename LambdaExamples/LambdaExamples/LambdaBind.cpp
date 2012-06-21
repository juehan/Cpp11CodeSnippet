/**************************************************************************
* LambdaBind.cpp: Example to compare std::bind and Lambda
* 
* Authors: Lee Jue Han <to.johnny.lee@gmail.com>
* First created: 21. Jun. 2012
* Last modified: 21. Jun. 2012

* Description: This code is to compare use of lambda and std::bind to 
				achieve same goal. 
				Sometimes I need to iterate over containers to apply same
				logic to all of items inside. 
				There are two choice. One is use of std::bind and the other
				is C++11 Lambda.
				This example illustrates two cases.

**************************************************************************/

#include <functional> //bind
#include <iostream>
#include <vector>
#include <algorithm> //for_each
#include <string>

////////////////////////////////////////////////////////////
// Use of std::bind
////////////////////////////////////////////////////////////
//function for bind
std::string AppendHello(std::string& str)
{
	return str.append(", hello!");
}

//return function pointer which takes string reference and return string object
std::function<std::string(std::string&)> GetHello_Bind()
{
	//bind AppendHello function in place of 1st parameter
	
	//std::function<std::string(std::string&)> fBind = std::bind(AppendHello, std::placeholders::_1); //okay but boring
	auto fBind = std::bind(AppendHello, std::placeholders::_1); //much shorter thus better

	return fBind;
}

////////////////////////////////////////////////////////////
// Use of lambda 
////////////////////////////////////////////////////////////

//return function pointer which takes string reference and return string object
std::function<std::string(std::string&)> GetHello_Lambda()
{
	//std::function<std::string(std::string&)> fLambda = [](std::string& str)->std::string{ //okay but boring
	auto fLambda = [](std::string& str)->std::string{ //much shorter thus better

		return str.append(", hello!");
	};
	return fLambda;
}


//Debug utility function
void Print(std::vector<std::string>& v)
{
	std::for_each(v.begin(), v.end(), [&](std::string& str){
		std::cout<<str<<std::endl;
	});
}

//Call GetHello_Bind function to 
void TestBind()
{
	std::cout<<"\n\n## Bind Test"<<std::endl;

	//create vector with string
	std::vector<std::string> v;
	v.push_back("John");
	v.push_back("Jane");
	v.push_back("David");
	v.push_back("Tom");
	
	std::cout<<"\n--> Before operation --"<<std::endl;
	Print(v);

	//std::function<std::string(std::string&)> fb = GetHello_Bind(); //okay but boring
	auto fb = GetHello_Bind(); //much better

	//iterate over vector and apply fb function to every element in it
	std::for_each(v.begin(), v.end(), fb); 

	//check value after operation
	std::cout<<"\n--> After operation --"<<std::endl;
	Print(v);
}

void TestLambda()
{
	std::cout<<"\n\n## Lambda Test"<<std::endl;
	std::vector<std::string> v;
	v.push_back("John");
	v.push_back("Jane");
	v.push_back("David");
	v.push_back("Tom");
	
	std::cout<<"\n--> Before operation "<<std::endl;
	Print(v);

	//std::function<std::string(std::string&)> fl = GetHello_Lambda(); //okay but boring
	auto fl = GetHello_Lambda(); //much better
	
	//iterate over vector and apply fb function to every element in it
	std::for_each(v.begin(), v.end(), fl);

	//check value after operation
	std::cout<<"\n--> After operation "<<std::endl;
	Print(v);
}


int main(int argc, char* argv[])
{ 
	TestBind();
	TestLambda();

	return 0;
}

/*
Output



## Bind Test

--> Before operation --
John
Jane
David
Tom

--> After operation --
John, hello!
Jane, hello!
David, hello!
Tom, hello!


## Lambda Test

--> Before operation
John
Jane
David
Tom

--> After operation
John, hello!
Jane, hello!
David, hello!
Tom, hello!


*/