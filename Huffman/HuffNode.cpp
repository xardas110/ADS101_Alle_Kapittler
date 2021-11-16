#include "HuffNode.h"
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <limits.h>
#include <bitset>

std::ifstream::pos_type filesize(const char* filename)
{
	std::ifstream in(filename, std::ifstream::ate | std::ifstream::binary);
	return in.tellg();
}

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


void Huffman::GenerateTree()
{
	std::priority_queue<HuffNode*, std::vector<HuffNode*>, std::greater<HuffNode*>> pq;

	for (auto &item : leafMap)
	{
		pq.push(&item.second);
	}

	while (pq.size() != 1)
	{	
		auto *newNode = new HuffNode(NodeType::Child);
		auto *item1 = pq.top(); pq.pop();
		auto *item2 = pq.top(); pq.pop();
		newNode->LinkNodes(item1, item2);
		pq.push(newNode);
	}
	root = pq.top();
}

void Huffman::Encode(_In_ HuffNode* node, const std::string binText)
{
	if (!node)
		return;

	if (node->GetNodeType() == NodeType::Leaf)
	{
		auto* leaf = reinterpret_cast<HuffLeaf*>(node);
		leaf->SetBits(binText.empty()?"1":binText);
	}

	Encode(node->leftNode, binText + "0");
	Encode(node->rightNode, binText + "1");
}

void Huffman::Decode(const _In_ HuffNode* node, _Inout_ int& index, _In_ const std::string& binString)
{
	if (!node)
		return;

	if (node->GetNodeType() == Leaf)
	{
		const auto* leaf = reinterpret_cast<const HuffLeaf*>(node);
		std::cout << leaf->GetSymbol();
		return;
	}

	if (binString[index] == '0')
	{
		index++;
		Decode(node->leftNode, index, binString);
	}
	else if (binString[index] == '1')
	{
		index++;
		Decode(node->rightNode, index, binString);
	}
}

void Huffman::DecodeAndPrint(const _In_ HuffNode* node, _In_ const std::string& binaryString) const
{
	int index = 0;
	while (index < (int)binaryString.size()) {
		Decode(root, index, binaryString);
	}
}

const HuffNode* Huffman::GetRoot() const
{
	return root;
}

const std::string& Huffman::GetSavedText() const
{
	return text;
}

const std::map<char, HuffLeaf>& Huffman::GetLeafMap() const
{
	return leafMap;
}

Huffman::Huffman(const _In_ std::string& text)
	: text(text)
{
	for (const auto c : text)
	{
		auto it = leafMap.find(c);
		
		if (it != leafMap.end())
		{		
			it->second.IncrementFrequency();
		}		
		else
		{
			HuffLeaf leaf(c);
			leaf.SetFrequency(1);
			leafMap.insert(std::make_pair(c, leaf));
		}
	}

	GenerateTree();
	
	if (root)
	{
		const std::string temp;
		Encode(root, temp);
	}
	else
	{
		throw std::exception("Huffman tree is lacking a root, something is wrong!");
	}
	
}

HuffLeaf::HuffLeaf(const char symbol)
	: HuffNode(NodeType::Leaf), symbol(symbol), bits{}
{
}

char HuffLeaf::GetSymbol() const
{
	return symbol;
}

void HuffLeaf::SetBits(const _In_ std::string& binString)
{
	bits = binString;
}

std::string HuffLeaf::GetBitString() const
{
	return bits; 
}

void HuffLeaf::PrintBits() const
{
	std::cout << bits << std::endl;
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

void Huffman::Compress(const std::string& path)
{
	std::string binaryText{ };
	for (const char c : text)
	{
		auto it = leafMap.find(c);

		if (it != leafMap.end())
		{
			binaryText += it->second.GetBitString();
		}
	}
	
	std::ofstream os;
	
	os.open(path, std::ios::binary);

	for (size_t i = 0; i < binaryText.size(); i += 8)
	{
		std::string byteString;
		for (size_t j = i; j < i+8 && j < binaryText.size(); j++)
		{
			byteString.push_back(binaryText[j]);
		}
		char byte = std::bitset<8>(byteString.c_str()).to_ulong();
		os.write(&byte, 1);
	}
	
	os.close();

	os.open("Un"+path, std::ios::out);
	os.write(text.c_str(), text.size());
	os.close();	
}

void Huffman::Decompress(const std::string& path)
{
	std::string binaryFromFile{};

	const int s = filesize(path.c_str());
	std::cout << "Filesize : " << s << std::endl;
	
	std::ifstream is;
	is.open(path, std::ios::in | std::ios::binary);

	if (is.is_open())
	{
		char *a = new char[s];
		is.read(a, s);
		
		for (auto i = 0; i < s; i++)
		{
			const std::string decompressedBinaryString(chartobin(a[i]));
			binaryFromFile += decompressedBinaryString;
		}

		is.close();
		delete[] a;
	}
	else
	{
		std::cout << "Failed to open file" << std::endl;
	}

	std::cout << "Binary from file: "<< binaryFromFile << std::endl;

	DecodeAndPrint(root, binaryFromFile);
}
