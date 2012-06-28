//ownership problem in raw pointer

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

void func(std::unique_ptr<Person> p)
{
	//3. now func have ownership of passed pointer
	std::cout<<"inside func"<<std::endl;
	std::cout<<p->GetAge()<<std::endl;
	//4. as soon as this function returns, pointer p will be destroyed even if you don't call delete
}



int main()
{
	//1. here i created unique pointer
	std::unique_ptr<Person> p1(new Person(3, "baby"));

	//2. if you want to pass it to other function, you need to move it using std::move
	func(std::move(p1));

	//5. Ooops, you forgot you already give up p1's ownership. Below line will crash your app.
	std::cout<<p1->GetAge()<<std::endl;

	
	return 0;
}

