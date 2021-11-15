#include "HuffNode.h"

#include <iostream>
#include <fstream>

void Huffman::GenerateTree()
{
	std::priority_queue<HuffNode*, std::vector<HuffNode*>, std::less<HuffNode*>> pq;

	for (auto &item : charMap)
	{
		pq.push(&item.second);
	}

	while (!pq.empty())
	{
		if (pq.size() > 1)
		{
			auto *newNode = new HuffNode(NodeType::Child);
			auto *item1 = pq.top(); pq.pop();
			auto *item2 = pq.top(); pq.pop();
			newNode->LinkNodes(item1, item2);
			pq.push(newNode);
		}
		else
		{
			root = pq.top(); pq.pop();
		}
	}
}

void Huffman::GenerateBits(_In_ HuffNode* node, _In_ int* arrPtr, _In_count_(MAX_BITS_HUFFMAN) int arr[MAX_BITS_HUFFMAN])
{
	if (node->leftNode)
	{
		*arrPtr = 0;
		int* newPtr = (int*)((int)arrPtr + 4);
		GenerateBits(node->leftNode, newPtr, arr);
	}

	if (node->GetNodeType() == NodeType::Leaf)
	{
		auto* nodeLeaf = reinterpret_cast<HuffLeaf*>(node);
		if (nodeLeaf)
		{
			nodeLeaf->SetBits(arr);
		}
	}

	if (node->rightNode)
	{
		*arrPtr = 1;
		int* newPtr = (int*)((int)arrPtr - 4);
		GenerateBits(node->rightNode, newPtr, arr);
	}
}

const HuffNode* Huffman::GetRoot() const
{
	return root;
}

Huffman::Huffman(const _In_ std::string& text)
	: text(text)
{
	for (const auto c : text)
	{
		auto it = charMap.find(c);
		
		if (it != charMap.end())
		{		
			it->second.IncrementFrequency();
		}		
		else
		{
			HuffLeaf leaf(c);
			leaf.SetFrequency(1);
			charMap.insert(std::make_pair(c, leaf));
		}
	}

	GenerateTree();

	if (root)
	{
		int* tempArr = new int[MAX_BITS_HUFFMAN];
		for (auto i = 0; i < MAX_BITS_HUFFMAN; i++)
		{
			tempArr[i] = -1;
		}
		GenerateBits(root, &tempArr[0], tempArr);
		delete tempArr;
	}
	else
	{
		throw std::exception("Huffman tree is lacking a root, something is wrong!");
	}
}

HuffLeaf::HuffLeaf(const char symbol)
	: HuffNode(NodeType::Leaf), symbol(symbol), bits(new int[MAX_BITS_HUFFMAN])
{
	for (auto i = 0; i < MAX_BITS_HUFFMAN; i++)
	{
		bits[i] = -1;
	}
}

char HuffLeaf::GetSymbol() const
{
	return symbol;
}

void HuffLeaf::SetBits(_In_count_(MAX_BITS_HUFFMAN) int arr[MAX_BITS_HUFFMAN])
{
	for (auto i = 0; i < MAX_BITS_HUFFMAN; i++)
	{
		bits[i] = arr[i];
	}
}

std::string HuffLeaf::GetBitString() const
{
	std::string result{};
	
	for (int i= 0; i< MAX_BITS_HUFFMAN; i++)
	{
		if (bits[i] == -1)
			break;
		
		result.push_back(std::to_string(bits[i]).front());
	}
	return result;
}

void HuffLeaf::PrintBits() const
{
	std::cout << "Printing bits: " << std::endl;
	for (int i= 0; i< MAX_BITS_HUFFMAN; i++)
	{
		std::cout << bits[i] << std::endl;
	}
}

bool HuffLeaf::CmpBits(int arr[MAX_BITS_HUFFMAN])
{
	return memcmp(bits, arr, sizeof(bits[0]) * MAX_BITS_HUFFMAN) == 0;
}

void HuffLeaf::PrintSymbol() const
{
	std::cout << symbol << std::endl;
}

void HuffNode::LinkNodes(HuffNode* a, HuffNode* b)
{
	leftNode = a;
	rightNode = b;
	frequency += a->frequency + b->frequency;
	parent = a->parent = b->parent = this;
}

void HuffNode::SetFrequency(int newFrequency)
{
	frequency = newFrequency;
}

int HuffNode::GetFrequency() const
{
	return frequency;
}

void HuffNode::IncrementFrequency()
{
	frequency++;
}

NodeType HuffNode::GetNodeType() const
{
	return nodeType;
}

HuffNode::HuffNode(NodeType type)
	:nodeType(type)
{
}

const HuffLeaf* HuffNode::Find(_In_ int* &arrPtr, int arr[MAX_BITS_HUFFMAN]) const
{
	if (this->GetNodeType() == NodeType::Leaf)
	{
		return reinterpret_cast<const HuffLeaf*>(this);
	}

	if (*arrPtr == 1)
	{
		arrPtr = (int*)((int)arrPtr + 4);
		return rightNode->Find(arrPtr, arr);
	}
	else if (*arrPtr == 0)
	{
		arrPtr = (int*)((int)arrPtr + 4);
		return leftNode->Find(arrPtr, arr);
	}

	return nullptr;
}

void HuffNode::InTraverse() const
{
	if (leftNode)
	{
		leftNode->InTraverse();
	}

	if (this->GetNodeType() == NodeType::Leaf)
	{
		const auto* nodeLeaf = reinterpret_cast<const HuffLeaf*>(this);
		if (nodeLeaf)
		{		
			std::cout << nodeLeaf->GetSymbol() << std::endl;
			nodeLeaf->PrintBits();
		}
	}

	if (rightNode)
	{
		rightNode->InTraverse();
	}
}

#include <stdio.h>
#include <limits.h>

// Convert a char to a binary string representation of that char value

char* chartobin(unsigned char c)
{
	static char bin[CHAR_BIT + 1] = { 0 };
	int i;

	for (i = CHAR_BIT - 1; i >= 0; i--)
	{
		bin[i] = (c % 2) + '0';
		c /= 2;
	}

	return bin;
}

#include <bitset>
void Huffman::Compress()
{
	std::string binaryText{ };
	for (const char c : text)
	{
		auto it = charMap.find(c);

		if (it != charMap.end())
		{
			binaryText += it->second.GetBitString();
		}
	}
	
	std::ofstream os;
	
	os.open("Compress.txt", std::ios::binary);

	for (auto i = 0; i < binaryText.size(); i += 8)
	{
		std::string binString{ };
		if (i + 8 > binaryText.size())
		{
			for (auto j = i; j < binaryText.size(); j++)
				binString.push_back(binaryText[j]);
		}
		else
		{
			for (auto j = i; j < i + 8; j++)
				binString.push_back(binaryText[j]);
		}
		char** sht;
		
		char byte = std::bitset<8>(binString.c_str()).to_ulong();
		
		os.write(&byte, 1);
	}
	
	os.close();

	os.open("UnCompressed.txt", std::ios::out);
	os.write(text.c_str(), text.size());
	os.close();	
}

void Huffman::Decompress()
{
	std::string binaryFromFile{};

	std::ifstream is;
	is.open("Compress.txt", std::ios::in | std::ios::binary);

	if (is.is_open())
	{
		char a[1];
		is.read(a, 1);
		for (auto i = 0; i < 1; i++)
		{
			char* chartoBin = chartobin(a[i]);

			std::string t(chartoBin);
			binaryFromFile += t;
		}

		is.close();
	}
	else
	{
		std::cout << "Failed to open file" << std::endl;
	}
	int* temp = new int[binaryFromFile.size()];
	int* ptrStart = &temp[0];
	for (auto i= 0; i < binaryFromFile.size(); i++)
	{
		temp[i] = (int)binaryFromFile[i] - 48;
		std::cout << temp[i] << std::endl;
	}
	
	std::string resultString{  };
	int val = 0;
	while (val < binaryFromFile.size())
	{
		val++;
		const auto node = root->Find(ptrStart, temp);
		if (node)
		{
			resultString.push_back(node->GetSymbol());
		}
	}

	std::cout << resultString << std::endl;
}
