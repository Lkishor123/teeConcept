#include <iostream>
#include <vector>
#include <sgx_urts.h>
#include "Enclave_u.h"

#define ENCLAVE_FILE "enclave.signed.so"

int main() {
    sgx_enclave_id_t eid;
    sgx_status_t ret = SGX_ERROR_UNEXPECTED;

    // Initialize the enclave
    ret = sgx_create_enclave(ENCLAVE_FILE, SGX_DEBUG_FLAG, NULL, NULL, &eid, NULL);
    if (ret != SGX_SUCCESS) {
        std::cerr << "Failed to create enclave: " << std::hex << ret << std::endl;
        return -1;
    }

    // Sample data
    std::vector<double> x = {1, 2, 3, 4, 5};
    std::vector<double> y = {2, 4, 6, 8, 10}; // y = 2x

    double m, b;
    double learning_rate = 0.01;
    int iterations = 1000;

    // Call the enclave function
    ret = enclave_train(eid, x.data(), y.data(), x.size(), learning_rate, iterations, &m, &b);
    if (ret != SGX_SUCCESS) {
        std::cerr << "Enclave call failed: " << std::hex << ret << std::endl;
        sgx_destroy_enclave(eid);
        return -1;
    }

    std::cout << "Trained model parameters:" << std::endl;
    std::cout << "Slope (m): " << m << std::endl;
    std::cout << "Intercept (b): " << b << std::endl;

    // Destroy the enclave
    sgx_destroy_enclave(eid);

    return 0;
}
