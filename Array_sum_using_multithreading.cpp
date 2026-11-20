#include <iostream>
#include <thread>
#include <chrono>
using namespace std;


void calculateSum(int arr[], int start, int end, long long &sum)
{
    sum = 0;

    for (int i = start; i < end; i++)
    {
        sum += arr[i];
    }
}

int main()
{
    const int N = 100000;

    int arr[N];

    for (int i = 0; i < N; i++)
    {
        arr[i] = i + 1;
    }

    long long sum1 = 0;
    long long sum2 = 0;
    long long sum3 = 0;
    long long sum4 = 0;

  
    auto startTime = chrono::high_resolution_clock::now();

    thread t1(calculateSum, arr, 0, 25000, ref(sum1));
    thread t2(calculateSum, arr, 25000, 50000, ref(sum2));
    thread t3(calculateSum, arr, 50000, 75000, ref(sum3));
    thread t4(calculateSum, arr, 75000, 100000, ref(sum4));

  
    t1.join();
    t2.join();
    t3.join();
    t4.join();

  
    long long totalSum = sum1 + sum2 + sum3 + sum4;


    auto endTime = chrono::high_resolution_clock::now();

  
    auto executionTime =
        chrono::duration_cast<chrono::microseconds>
        (endTime - startTime);

    cout << "Total Sum = " << totalSum << endl;

    cout << "Processing Time = "
         << executionTime.count()
         << " microseconds" << endl;

    cout << "Processing Time = "
         << executionTime.count() / 1000.0
         << " milliseconds" << endl;

    return 0;
}