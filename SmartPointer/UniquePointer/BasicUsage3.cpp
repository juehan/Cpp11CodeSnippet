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
	
	std::string GetName()
	{
		return _name;
	}

	void ChangeName(std::string name)
	{
		_name.clear();
		_name = name; 
	}

};

//pass by reference is a way better to safely pass unique pointer while retaining ownership
void process(std::unique_ptr<Person>& p)
{
	p->ChangeName("baby girl");
}

int main()
{
	std::unique_ptr<Person> p1(new Person(3, "baby"));
	process(p1);
	std::cout<<p1->GetName()<<std::endl;
		
	return 0;
}

