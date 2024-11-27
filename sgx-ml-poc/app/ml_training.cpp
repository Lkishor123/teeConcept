#include <iostream>
#include <vector>

// Simple linear regression using gradient descent
void linear_regression(const std::vector<double>& x, const std::vector<double>& y, double& m, double& b, double learning_rate, int iterations) {
    size_t n = x.size();
    m = 0.0; // slope
    b = 0.0; // intercept

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
}

int main() {
    // Sample data
    std::vector<double> x = {1, 2, 3, 4, 5};
    std::vector<double> y = {2, 4, 6, 8, 10}; // y = 2x

    double m, b;
    double learning_rate = 0.01;
    int iterations = 1000;

    linear_regression(x, y, m, b, learning_rate, iterations);

    std::cout << "Trained model parameters:" << std::endl;
    std::cout << "Slope (m): " << m << std::endl;
    std::cout << "Intercept (b): " << b << std::endl;

    return 0;
}
