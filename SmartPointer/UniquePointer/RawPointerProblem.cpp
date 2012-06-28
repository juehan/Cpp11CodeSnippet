#include <iostream>
#include <memory>
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

void blackhallFunc(Person* p)
{
	//who owns the pointer p now?	
	delete p;
}

int main()
{
	//ownership problem in raw pointer
	Person* p1 = new Person(3, "baby");
	blackhallFunc(p1);
	std::cout<<p1->GetAge()<<std::endl;
	delete p1; //oops, this will crash your app
	
	return 0;
}

