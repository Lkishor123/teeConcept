#include "Enclave_t.h"
#include <vector>

void enclave_train(double* x, double* y, size_t num_elements, double learning_rate, int iterations, double* m, double* b) {
    // Convert raw pointers to vectors
    std::vector<double> x_vec(x, x + num_elements);
    std::vector<double> y_vec(y, y + num_elements);

    // Initialize parameters
    *m = 0.0;
    *b = 0.0;

    for (int iter = 0; iter < iterations; ++iter) {
        double dm = 0.0;
        double db = 0.0;
        for (size_t i = 0; i < num_elements; ++i) {
            double prediction = (*m) * x_vec[i] + (*b);
            double error = prediction - y_vec[i];
            dm += error * x_vec[i];
            db += error;
        }
        dm /= num_elements;
        db /= num_elements;
        *m -= learning_rate * dm;
        *b -= learning_rate * db;
    }
}
