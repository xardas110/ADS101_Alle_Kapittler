#pragma once
#include <string>
#include <queue>
#include <map>

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
	
	void InTraverse() const;
	
	bool operator > (_In_ HuffNode* other) const { return this->frequency > other->frequency; }
	bool operator < (_In_ HuffNode* other) const { return this->frequency < other->frequency; }

private:
	int frequency{ 0 };
	NodeType nodeType;
	HuffNode* parent = nullptr, * leftNode = nullptr, * rightNode = nullptr;
};

class HuffLeaf : public HuffNode
{
	char symbol{};
	std::string bits;
	
public:
	HuffLeaf(const char symbol);
	
	char GetSymbol() const; 

	void SetBits(const _In_ std::string& binString);
	
	std::string GetBitString() const;
	
	void PrintBits() const;

	void PrintSymbol() const;
};

class Huffman
{
	using LeafMap = std::map<char, HuffLeaf>;
	
	HuffNode* root{ nullptr };

	std::string text;
	
	LeafMap leafMap;

	void GenerateTree();
	
public:
	Huffman(const _In_ std::string& text);

	static void Encode(_In_ HuffNode* node, const std::string binText);
	
	static void Decode(const _In_ HuffNode* node, _Inout_ int& index, _In_ const std::string& binString);

	void DecodeAndPrint(const _In_ HuffNode* node, _In_ const std::string& binaryString) const;
	
	const HuffNode* GetRoot() const;

	const std::string& GetSavedText() const;

	const LeafMap& GetLeafMap() const;
	
	void Compress(const std::string& path);
	void Decompress(const std::string& path);
};