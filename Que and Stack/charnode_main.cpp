// ADS101 Algoritmer og datastrukturer H2017-2020

#include <iostream>
#include "charnode.h"
#include <stack>
#include "Stack.h"
#include <memory>
#include <chrono>
#include<array>
#include <iomanip>
#include<algorithm>
#include <vector>
#include <cassert>

#define NStoS 0.000000001

#define Array(size) \
	new int[size], size

using DWORD64 = unsigned long long;
using ArraySort = std::vector<std::pair<std::pair<int*, int>, std::chrono::nanoseconds>>;
using VectorArraySort = std::vector<ArraySort>;

void selection_sort(int * a, const int n, std::chrono::nanoseconds &ns_elapsed) // husk r e f e r a n s e
{
    const auto start = std::chrono::high_resolution_clock::now();
    for(auto i = 0; i < n-1 ; i++)
        for(auto j = i + 1; j < n; j++)
            if(a[i] > a[j])
                std::swap(a[i], a[j]);

    const auto end = std::chrono::high_resolution_clock::now();
    ns_elapsed = end - start;
}
void selection_sort_vector(ArraySort &arr_sort)
{
    for (auto &entity : arr_sort)
        selection_sort(entity.first.first, entity.first.second, entity.second);   
}
void stl_sort(int * a, const int n, std::chrono::nanoseconds &ns_elapsed)
{
    if (n < 1) throw std::exception("Array not populated");
	
    const auto start_address = reinterpret_cast<DWORD64>(a);
    const auto end_address = start_address + (sizeof(a[0]) * n);

    auto& start_address_ptr = a;
    auto* end_address_ptr = reinterpret_cast<int*>(end_address);
	
    const auto start = std::chrono::high_resolution_clock::now();
    std::sort(start_address_ptr, end_address_ptr);
    const auto end = std::chrono::high_resolution_clock::now();
    ns_elapsed = end - start;
	
}
void stl_sort_vector(ArraySort& arr_sort)
{
    for (auto& entity : arr_sort)
    {
        stl_sort(entity.first.first, entity.first.second, entity.second);
    }
}
void randomize_array(int * a, const int n)
{
    for (auto i = 0; i < n; i++)
    {
        a[i] = rand() % 100 + 1;
    };
}
void print_array_vector(ArraySort& arr_sort)
{
    for (const auto &entity : arr_sort)
    {
        std::cout << "Array size: " << entity.first.second << std::endl;
        std::cout << "Elapsed time in nanoseconds: " << entity.second.count() << std::endl;
        std::chrono::duration<double, std::ratio<1, 1>> seconds(entity.second);
        std::cout << "Elapsed time in seconds: " << seconds.count() << std::endl;
    }
}

void randomize_array_vector(ArraySort& arr_sort)
{
    for (auto &entity : arr_sort)
        randomize_array(entity.first.first, entity.first.second);
}

void randomize_stl_sort_arrays_of_vectors(std::vector<ArraySort> &arrays)
{
    for (auto &entity : arrays)
    {
        randomize_array_vector(entity);
        stl_sort_vector(entity);
    }
}
void randomize_selection_sort_arrays_of_vectors(std::vector<ArraySort>& arrays)
{
    for (auto& entity : arrays)
    {
        randomize_array_vector(entity);
        selection_sort_vector(entity);
    }
}
void print_table(std::vector<ArraySort> &table)
{
    const auto num_arrays = table[0].size();
    const auto iterations = table.size();

    auto* average_time = new double[num_arrays];
    memset(average_time, 0, sizeof(double)*num_arrays);

    for (size_t j = 0; j < iterations; j++)
    {
        if (num_arrays != table[j].size()) 
            throw std::exception("Arrays in table do not have the same size");

        for (size_t i = 0; i < num_arrays; i++)
        {
            average_time[i] += std::chrono::duration<double, std::nano>(table[j][i].second).count();
        }
    }

    std::cout << "Number of iterations: " << iterations << std::endl;
    std::cout << "----------------------------------------------------" << std::endl;
    std::cout << "|n" << "\t|ns " << "\t\t|s" << std::endl;
    std::cout << "----------------------------------------------------" << std::endl;
    for (size_t i = 0; i < num_arrays; i++)
    {       
        const auto avg_ns = average_time[i] / static_cast<double>(iterations);
        std::cout << "|" <<table[0][i].first.second;
        std::cout << "\t|" << avg_ns;
        std::cout << "\t\t|" << avg_ns * NStoS;
        std::cout << std::endl;
    }
    std::cout << "----------------------------------------------------" << std::endl << std::endl;
    delete[] average_time;
}
void generate_arrays(std::initializer_list<int> list, ArraySort &array_sort)
{
    for (const auto n : list)
        array_sort.push_back({ {Array(n)}, {} });
}
void Del2(const std::initializer_list<int> list, const int iterations)
{
    auto r = std::setprecision(16);
	
    ArraySort array_sort;
    VectorArraySort vector_array_sort;

    generate_arrays(list, array_sort);

    for (auto i = 0; i < iterations; i++)
        vector_array_sort.push_back(array_sort);

    std::cout << "Stl sort: " << std::endl;
    randomize_stl_sort_arrays_of_vectors(vector_array_sort);
    print_table(vector_array_sort);

    std::cout << "Selection sort: " << std::endl;
    randomize_selection_sort_arrays_of_vectors(vector_array_sort);
    print_table(vector_array_sort);

    //Cleanup
    for (const auto& entity : array_sort)
        delete[] entity.first.first;

    vector_array_sort.clear();
}
int main()
{
	//Del 1
    Stack stack{ 'a', 'b' };
    //stack.Pop();
    //std::cout << stack.Top() << std::endl;

	//Del 2
    //Del2({ 10, 100, 1000, 10000, 20000, 100000}, 10);
}


