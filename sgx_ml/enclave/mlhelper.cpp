#include <vector>
#include <iostream> // Note: Using standard I/O in enclave requires defining OCALLs for printing.
#include "mlhelper.h"
#include "Enclave_t.h" // Generated header for trusted bridge

void ML_helper() {
    // Sample data
    std::vector<double> x = {1, 2, 3, 4, 5};
    std::vector<double> y = {2, 4, 6, 8, 10}; // y = 2x

    double m = 0.0; // Slope
    double b = 0.0; // Intercept
    double learning_rate = 0.01;
    int iterations = 1000;

    size_t n = x.size();

    // Gradient Descent Algorithm
    for (int iter = 0; iter < iterations; ++iter) {
        double dm = 0.0;
        double db = 0.0;

        for (size_t i = 0; i < n; ++i) {
            double prediction = m * x[i] + b;
            double error = prediction - y[i];
            dm += error * x[i];
            db += error;
        }

        dm /= n;
        db /= n;

        m -= learning_rate * dm;
        b -= learning_rate * db;
    }

    // Output the result - Since we cannot use standard I/O, we need to use an OCALL
    ocall_print("Trained model parameters:");
    ocall_print_double("Slope (m): ", m);
    ocall_print_double("Intercept (b): ", b);
}
