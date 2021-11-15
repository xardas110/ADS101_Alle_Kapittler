// ADS101 Algoritmer og datastrukturer 180903
// Implementering av kø med enkel lenket liste
#include <iostream>
#include "queue.h"
#include <queue>

int main()
{
    std::cout << "std::queue har push(), pop(), front(), size()\n";
    std::cout << "\nTester egen queue\n";

    ADS101::queue<char> queue;
    queue.push('a');
    queue.push('b');
    queue.push('c');
    auto ch = queue.front();
    std::cout << "queue front = " << ch << std::endl;
    queue.pop();
    queue.pop();
    queue.push('a');
    std::cout << "queue size = " << queue.size() << std::endl;

    std::cout << "\nTester std::queue\n";

    std::queue<char> q;
    q.push('a');
    q.push('b');
    q.push('c');
    ch = q.front();
    std::cout << "queue front = " << ch << std::endl;
    q.pop();
    q.pop();
    q.push('a');
    std::cout << "queue size = " << q.size() << std::endl;

    std::cin >> ch;
    return 0;
}


