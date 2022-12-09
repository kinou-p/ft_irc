#include <vector>
#include <iostream>
#include <string>


void	print(std::string c)
{
	if (c == "")
		std::cout << "NULL" << std::endl;
	std::cout << c << std::endl;
}
int main()
{

	std::vector<std::string> vec;

	vec.insert(vec.begin(), "bonjour");
	print(vec[3]);
	return 0;
}
