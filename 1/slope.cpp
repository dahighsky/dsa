#include <iostream>
#include <vector>
#include <chrono>
#include <omp.h>
#include <cstdlib>   // for rand()
#include <ctime>     // for time()

using namespace std;
using namespace std::chrono;

int main() {
    int n;
    cout << "Enter number of data points: ";
    cin >> n;

    vector<double> x(n), y(n);
    srand(time(0));

    // Random data generation: y = 2*x + 5 + some noise
    cout << "Generating " << n << " random data points..." << endl;
    for (int i = 0; i < n; i++) {
        x[i] = rand() % 10000;  // Random x in [0, 9999]
        y[i] = 2 * x[i] + 5 + (rand() % 100 - 50);  // y = 2x + 5 + noise [-50, +49]
    }

    // ----- Serial Version -----
    double sum_x_serial = 0, sum_y_serial = 0, sum_xy_serial = 0, sum_xx_serial = 0;
    auto start_serial = high_resolution_clock::now();

    for (int i = 0; i < n; i++) {
        sum_x_serial += x[i];
        sum_y_serial += y[i];
        sum_xy_serial += x[i] * y[i];
        sum_xx_serial += x[i] * x[i];
    }

    double slope_serial = (n * sum_xy_serial - sum_x_serial * sum_y_serial) /
                          (n * sum_xx_serial - sum_x_serial * sum_x_serial);
    double intercept_serial = (sum_y_serial - slope_serial * sum_x_serial) / n;

    auto end_serial = high_resolution_clock::now();
    auto duration_serial = duration_cast<microseconds>(end_serial - start_serial);

    // ----- OpenMP Parallel Version -----
    double sum_x_parallel = 0, sum_y_parallel = 0, sum_xy_parallel = 0, sum_xx_parallel = 0;
    auto start_parallel = high_resolution_clock::now();

    #pragma omp parallel for reduction(+:sum_x_parallel, sum_y_parallel, sum_xy_parallel, sum_xx_parallel)
    for (int i = 0; i < n; i++) {
        sum_x_parallel += x[i];
        sum_y_parallel += y[i];
        sum_xy_parallel += x[i] * y[i];
        sum_xx_parallel += x[i] * x[i];
    }

    double slope_parallel = (n * sum_xy_parallel - sum_x_parallel * sum_y_parallel) /
                            (n * sum_xx_parallel - sum_x_parallel * sum_x_parallel);
    double intercept_parallel = (sum_y_parallel - slope_parallel * sum_x_parallel) / n;

    auto end_parallel = high_resolution_clock::now();
    auto duration_parallel = duration_cast<microseconds>(end_parallel - start_parallel);

    // ----- Results -----
    cout << "\n===== Serial Linear Regression =====" << endl;
    cout << "Slope (m): " << slope_serial << endl;
    cout << "Intercept (c): " << intercept_serial << endl;
    cout << "Execution Time: " << duration_serial.count() << " microseconds" << endl;

    cout << "\n===== Parallel Linear Regression (OpenMP) =====" << endl;
    cout << "Slope (m): " << slope_parallel << endl;
    cout << "Intercept (c): " << intercept_parallel << endl;
    cout << "Execution Time: " << duration_parallel.count() << " microseconds" << endl;

    return 0;
}
