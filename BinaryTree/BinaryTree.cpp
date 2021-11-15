#include <iostream>
#include "BinaryNode.h"

int main()
{
	auto* bt = new BinaryNode<int>({5,3,7,6,9,5,5,2,4,3});

	std::list<int> itemsForDeletion;
	
	for (int i = 0; i< 3000; i++)
	{
		auto randVal = rand() % 6000 +10;
		itemsForDeletion.push_back(randVal);
		bt->Insert(randVal);
	}

	for (auto item: itemsForDeletion)
	{
		auto node = bt->Find(item);
		if (node)
			bt->Slett(node);
	}
	
	std::vector<int> container;

	bt->InOrder();
	bt->InOrder(container);
	std::cout << "size of tree; " << container.size();
}

