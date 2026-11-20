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
    std::thread my_thread;
    my_args args;

    args.N = N / 2;
    args.terms = terms;
    args.x = x;
    args.y = y;

    // Create new thread
    my_thread = std::thread(my_thread_func, &args);

    // Main thread processes the second half
    sinx(N - args.N, terms, x + args.N, y + args.N);

    // Wait for the new thread to finish
    my_thread.join();
}

void sinx(int N, int terms, float* x, float* y)
{
    for (int i = 0; i < N; i++)
    {
        float value = x[i];
        float term = x[i];

        for (int j = 1; j <= terms; j++)
        {
            term *= -x[i] * x[i] /
                    ((2 * j) * (2 * j + 1));

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

    // Start time
    auto startTime =
        std::chrono::high_resolution_clock::now();

    // Run parallel function
    parallel_sinx(N, terms, x.data(), y.data());

    // End time
    auto endTime =
        std::chrono::high_resolution_clock::now();

    // Calculate execution time
    auto executionTime =
        std::chrono::duration_cast<std::chrono::microseconds>(
            endTime - startTime
        );

    std::cout << "Computed sin(x) values using parallel threads:\n\n";

    for (int i = 0; i < N; i++)
    {
        std::cout << "sin(" << x[i] << ") = "
                  << y[i] << "\n";
    }

    std::cout << "\nExecution Time = "
              << executionTime.count()
              << " microseconds\n";

    std::cout << "Execution Time = "
              << executionTime.count() / 1000.0
              << " milliseconds\n";

    return 0;
}