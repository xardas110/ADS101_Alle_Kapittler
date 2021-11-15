#include <iostream>
#include "HuffNode.h"

int main()
{
	const std::string text = std::string("abc");

	Huffman* huff = new Huffman(text);

	//std::cout << text << std::endl;
/*
	huff->GetRoot()->InTraverse();

	int tempArr[MAX_BITS_HUFFMAN];
	memset(tempArr, -1, sizeof tempArr);
	tempArr[0] = 1;
	tempArr[1] = 1;
	
	auto found = huff->GetRoot()->Find(&tempArr[0], tempArr);

	if (found)
	{
		std::cout << "Found element;: " << std::endl;
		std::cout << found->GetSymbol() << std::endl;
	}
	*/
	huff->Compress();
	huff->Decompress();
	
	return 0;
}
