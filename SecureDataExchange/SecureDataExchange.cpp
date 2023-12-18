// SecureDataExchange.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <mutex>
#include <thread>

class Data {
public:
    int data;
    std::mutex mtx;

    Data(int value) : data(value) {}
};

void swap_with_lock(Data& a, Data& b) {
    std::lock(a.mtx, b.mtx);
    std::lock_guard<std::mutex> lockA(a.mtx, std::adopt_lock);
    std::lock_guard<std::mutex> lockB(b.mtx, std::adopt_lock);

    std::swap(a.data, b.data);
}

int main() {

    std::setlocale(LC_ALL, "RU");

    Data data1(42);
    Data data2(17);

    std::thread t1([&data1, &data2]() {
        swap_with_lock(data1, data2);
        });

    std::thread t2([&data1, &data2]() {
        swap_with_lock(data1, data2);
        });

    t1.join();
    t2.join();

    std::cout << "После swap: " << data1.data << "   " << data2.data << std::endl;

    return 0;
}




// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
