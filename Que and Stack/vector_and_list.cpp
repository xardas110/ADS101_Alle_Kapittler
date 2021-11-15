#include <iostream>
#include <vector>
using namespace std;

int main(int argc, char *argv[])
{
    vector<char> v;
    cout << "vector size: " << v.size() << endl;
    cout << "vector capacity: " << v.capacity() << endl;
    cout << "vector empty: " << (v.empty() ? "true" : "false") << endl;
    // skriv noen push_back() og sjekk size på nytt
    v.push_back('a');
    v.push_back('b');
    v.push_back('c');
    cout << "vector front: " << v.front() << endl;
    cout << "vector back: " << v.back() << endl;
    v.pop_back();
    cout << "vector back: " << v.back() << endl;
    cout << "vector capacity: " << v.capacity() << endl;
    // push_back, pop_back, front og back er felles
    // for vector og list, se side 99

    cout << "traversering" << endl;
    for (unsigned int i=0; i != v.size(); i++)
        cout << v[i];
    cout << endl;

    cout << "traversering med iterator" << endl;
    for (vector<char>::iterator i=v.begin(); i!= v.end(); i++)
        cout << *i;
    cout << endl;

    cout << "la oss slippe disse iteratorene!";
    for (auto i=v.begin(); i!= v.end(); i++)
        cout << *i;

    return 0;
}
