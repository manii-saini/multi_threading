#include <iostream>
#include <thread>
#include <vector>
#include <chrono>

typedef struct {
    int N;
    int terms;
    float* x;
    float* y;
} my_args;

void sinx(int N, int terms, float* x, float* y);

void my_thread_func(my_args* args)
{
    sinx(args->N, args->terms, args->x, args->y);
}

void parallel_sinx(int N, int terms, float* x, float* y)
{
    int N1 = N / 2;
    int N2 = N - N1;

    my_args args1;
    args1.N = N1;
    args1.terms = terms;
    args1.x = x;
    args1.y = y;

    my_args args2;
    args2.N = N2;
    args2.terms = terms;
    args2.x = x + N1;
    args2.y = y + N1;

    std::thread thread1(my_thread_func, &args1);
    std::thread thread2(my_thread_func, &args2);

    thread1.join();
    thread2.join();
}

void sinx(int N, int terms, float* x, float* y)
{
    for (int i = 0; i < N; i++)
    {
        float value = x[i];
        float term = x[i];

        for (int j = 1; j <= terms; j++)
        {
            term *= -x[i] * x[i] / ((2 * j) * (2 * j + 1));
            value += term;
        }

        y[i] = value;
    }
}

int main()
{
    int N = 4;
    int terms = 5;

    std::vector<float> x = {
        0.0f,
        0.5f,
        1.0f,
        1.5708f
    };

    std::vector<float> y(N, 0.0f);

    auto start = std::chrono::high_resolution_clock::now();

    parallel_sinx(N, terms, x.data(), y.data());

    auto end = std::chrono::high_resolution_clock::now();

    auto duration =
        std::chrono::duration_cast<std::chrono::microseconds>
        (end - start);

    std::cout << "Computed sin(x) values using two threads:\n";

    for (int i = 0; i < N; i++)
    {
        std::cout << "sin(" << x[i] << ") = "
                  << y[i] << "\n";
    }

    std::cout << "\nExecution Time: "
              << duration.count()
              << " microseconds\n";

    std::cout << "Execution Time: "
              << duration.count() / 1000.0
              << " milliseconds\n";

    return 0;
}