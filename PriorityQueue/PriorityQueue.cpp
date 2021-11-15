#include <iostream>
#include <queue>
#include <list>


struct Test
{
	char a;
	int weight = 2;
	Test(char a, int weight) :a(a), weight(weight){};
};


void print(_In_ Test* test)
{
	std::cout << test->a << std::endl;
}

int main()
{
	std::vector<Test> abc{ {'A', 1}, {'C', 2}, {'D', 4}, {'F',3} };
	int c = 3;
	auto cmp = [](Test &a, Test &b) {return a.weight > b.weight; };
	std::priority_queue < Test, std::vector<Test>, decltype(cmp)> pq(cmp, abc);

	
	while (!pq.empty())
	{
		std::cout << pq.top().a << std::endl;
		pq.pop();
	}
	
	//print(nullptr);
}
