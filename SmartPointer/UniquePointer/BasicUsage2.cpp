//How to use unique_ptr

#include <iostream>
#include <string>
#include <memory> //unique_ptr

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

std::unique_ptr<Person> getPtr()
{
	std::unique_ptr<Person> p(new Person(18, "highteen"));
	
	//no more copy happens
	return p;
}

int main()
{
	//1. here i created empty unique pointer
	std::unique_ptr<Person> p1 = getPtr();

	std::cout<<p1->GetAge()<<std::endl;

		
	return 0;
}

