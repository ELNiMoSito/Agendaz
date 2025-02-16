#include <iostream>
#include <random>
#include "menus.hpp"
std::string getUID(int& len)
{
	std::vector<char> x = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a',
	'b', 'c', 'd', 'e', 'f'};
	std::string uid(len, '\0');
	static std::mt19937 gen(std::random_device{}());
	std::uniform_int_distribution < > dis(0, x.size()-1);
	for (char& c: uid)
	{
		c = x[dis(gen)];
	}
	return uid;
}
void ClearScreen()
{
	for (int i=0; i<100;i++)
	{
		std::cout<<std::endl;
	}
}

int main()
{
	ClearScreen();
	menu1();
}