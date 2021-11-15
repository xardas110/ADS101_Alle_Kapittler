#pragma once
#include <string>
#include <queue>
#include <map>

#define MAX_BITS_HUFFMAN 10

enum NodeType
{
	Leaf,
	Child
};

struct HuffNode
{
	friend class Huffman;

	HuffNode(NodeType type);
	
	void LinkNodes(_In_ HuffNode* a, _In_ HuffNode* b);

	void SetFrequency(int newFrequency);
	
	int GetFrequency() const;

	void IncrementFrequency();

	NodeType GetNodeType() const;
	
	_Ret_maybenull_ const struct HuffLeaf* Find(_In_ int* &arrPtr, _In_count_(MAX_BITS_HUFFMAN) int arr[MAX_BITS_HUFFMAN]) const;
	
	void InTraverse() const;
	
	bool operator > (_In_ HuffNode* other) const { return this->frequency > other->frequency; }

private:
	int frequency{ 0 };
	NodeType nodeType;
	HuffNode* parent = nullptr, * leftNode = nullptr, * rightNode = nullptr;
};

class HuffLeaf : public HuffNode
{
	char symbol{0};
	int* bits{nullptr};
	
public:
	HuffLeaf(const char symbol);
	
	HuffLeaf(const HuffLeaf&) = default;
	HuffLeaf(HuffLeaf&&) = default;
	
	HuffLeaf& operator=(const HuffLeaf&)  = default;
	HuffLeaf& operator=(HuffLeaf&&) = default;

	char GetSymbol() const; 

	void SetBits(_In_count_(MAX_BITS_HUFFMAN) int arr[MAX_BITS_HUFFMAN]);
	
	std::string GetBitString() const;
	
	void PrintBits() const;

	bool CmpBits(_In_count_(MAX_BITS_HUFFMAN) int arr[MAX_BITS_HUFFMAN]);

	void PrintSymbol() const;
	
	~HuffLeaf() = default;
};


class Huffman
{
	HuffNode* root{ nullptr };

	std::string text;
	
	std::map<char, HuffLeaf> charMap;

	void GenerateTree();
	void GenerateBits(_In_ HuffNode* node, _In_ int* arrPtr, _In_count_(MAX_BITS_HUFFMAN) int arr[MAX_BITS_HUFFMAN]);
public:
	const HuffNode* GetRoot() const;
	Huffman(const _In_ std::string& text);
	void Compress();
	void Decompress();
};