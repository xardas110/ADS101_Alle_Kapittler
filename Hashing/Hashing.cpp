#include <iostream>
#include <string>
#include <unordered_set>
using namespace std;

struct Test
{
	int key;
	std::string s;
	bool operator == (const Test& t2) const { return key == t2.key;}
};

namespace  std {
	template<>
	class hash<Test>
	{
	public:
		size_t operator() (const Test& t) const
		{
			return t.key % 11;
		}
		bool operator() (const Test&t1, const Test& t2)
		{
			return t1.key == t2.key;
		}
	};
	
}


void test_hash()
{
	hash<int> h;

	size_t i = h(1113335557);
	cout << "hash  h(3453535353): " << i << std::endl;

	hash<Test> ht;
	Test t{ 1113335557, "fdgfdgfd" };
	i = ht(t);
	cout << "egen hash verdi" << i  << endl;
	
}

void test_unordered_set()
{
	hash<Test> ht;

	unordered_set<Test> us;
	unordered_set<Test>::iterator usit;
	pair<unordered_set<Test>::iterator, bool> par;

	Test t;

	cout << "Tester egen hashfunksjon" << endl;
	for(auto i = 0; i<15; i++)
	{
		t.key = i;
		cout << "Hash_ht(" << i << ")=" << ht(t) << endl;
	}

	t.key = 12; t.s = "tolv";
	us.insert(t);
	t.key = 14; t.s = "fjorten";
	us.insert(t);

	t.key = 14; t.s = "fjorten_b";
	int m = us.size();
	par = us.insert(t);

	int n = us.size();

	cout << t.s << "satt inn? " << boolalpha << (n - m == 1) << endl;
	cout << t.s << "satt inn? " << boolalpha << par.second << endl;

	t.key = 14;
	usit = us.find(t);

	t = *usit;
	cout << "post funnet: " << t.key << "_" << t.s << endl;
}

void test_unordered_multiset()
{
	unordered_multiset<Test> ums;
	unordered_multiset<Test>::iterator umsit;
	pair<unordered_multiset<Test>::iterator, bool> par;

	Test t1, t2;

	t1.key = 12; t1.s = "tolv";

	ums.insert(t1);

	t2.key = 14; t2.s = "Fjorten";

	ums.insert(t2);

	int m = ums.size();

	t2.key = 14; t2.s = "fjorten_b";
	ums.insert(t2);
	int n = ums.size();

	t2.key = 14; t2.s = "fjorten_c";
	ums.insert(t2);

	t2.key = 14; t2.s = "fjorten_d";
	ums.insert(t2);
	
	cout << t2.s << "satt inn= " << boolalpha << (n - m == 1) << endl;

	//vi skal finne igjen objektet med key 12
	// det er da ikke interessant hva objektets string verdi faktisk er siden 12 er key;

	
	t2.key = 14;
	umsit = ums.find(t2);

	t2 = *umsit;
	cout << t2.key << " " << t2.s << endl;
	
	cout << "load factor " << ums.load_factor() << endl;
	
	cout << "size " << ums.size() << endl;
	
	cout << "bucket count " << ums.bucket_count() << endl;
	
	cout << endl << "tenk litt over implemteringen i stl:  "<< endl;
	
	cout << "bucket size for key " << t1.key << " " << ums.bucket(t1) << endl;
	cout << "bucket size for key " << t2.key << " " << ums.bucket(t2) << endl;
	

	cout << "Setter inn 17 poster " << endl;

	for (int i = 13; i< 30; i++)
		ums.insert(Test{ i, "blabla" });
	
	cout << "load factor " << ums.size() << "/" << ums.bucket_count() << " " << ums.load_factor() << endl;
	
	cout << "size " << ums.size() << endl;

	cout << "bucket count: " << ums.bucket_count() << endl;
}


int main()
{
	//test_hash();
	//test_unordered_set();
	test_unordered_multiset();
}
