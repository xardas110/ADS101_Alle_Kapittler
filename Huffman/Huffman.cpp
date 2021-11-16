#include <iostream>
#include <fstream>
#include "HuffNode.h"

int main()
{
	std::string text;

	std::ifstream is;
	is.open("CompressThis.txt");
	if (is.is_open())
	{
		std::string line;
		while (std::getline(is, line))
		{
			text += line;
		}
		
		auto* huff = new Huffman(text);

		//	huff->GetRoot()->InTraverse();

		huff->Compress("Compressed.txt");
		huff->Decompress("Compressed.txt");
	}
	is.close();
	
	return 0;
}
