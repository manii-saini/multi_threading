#include <iostream>
#include <chrono>
#include <vector>

using namespace std;

int main()
{
    const long long N = 10000000;


    vector<int> arr(N);


    for (long long i = 0; i < N; i++)
    {
        arr[i] = i + 1;
    }

    long long sum = 0;


    auto startTime = chrono::high_resolution_clock::now();

    for (long long i = 0; i < N; i++)
    {
        sum += arr[i];
    }

   
    auto endTime = chrono::high_resolution_clock::now();


    auto executionTime =
        chrono::duration_cast<chrono::microseconds>(
            endTime - startTime
        );

    cout << "Total Sum = " << sum << endl;

    cout << "Processing Time = "
         << executionTime.count()
         << " microseconds" << endl;

    cout << "Processing Time = "
         << executionTime.count() / 1000.0
         << " milliseconds" << endl;

    return 0;
}