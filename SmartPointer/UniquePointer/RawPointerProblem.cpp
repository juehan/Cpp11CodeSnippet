//ownership problem in raw pointer

#include <iostream>
#include <string>

class Person
{
	int _age;
	std::string _name;

public:
	Person(int age, std::string name):_age(age), _name(name){}

	int GetAge()
	{
		return _age;
	}

};

void blackholeFunc(Person* p)
{
	//3. now this freaking function just swallow it like blackhole.	
	delete p;
}

int main()
{
	//1. here i created raw pointer
	Person* p1 = new Person(3, "baby");

	//2. and pass it to one function
	blackholeFunc(p1);

	//4. Pointer owner just believe his pointer is still safe
	std::cout<<p1->GetAge()<<std::endl;

	//5. Ooops, this will crash your app
	delete p1; 
	
	return 0;
}

