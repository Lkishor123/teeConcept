#include <iostream>
#include <sgx_urts.h>
#include "Enclave_u.h" // Generated header for untrusted bridge

#define ENCLAVE_FILE "enclave.signed.so"

void ocall_print(const char* str) {
    std::cout << str << std::endl;
}

void ocall_print_double(const char* label, double val) {
    std::cout << label << val << std::endl;
}

int main() {
    sgx_enclave_id_t eid;
    sgx_status_t ret = SGX_ERROR_UNEXPECTED;

    // Create the enclave
    ret = sgx_create_enclave(ENCLAVE_FILE, SGX_DEBUG_FLAG, NULL, NULL, &eid, NULL);
    if (ret != SGX_SUCCESS) {
        std::cerr << "Failed to create enclave: error code " << std::hex << ret << std::endl;
        return -1;
    }

    // Call the enclave entry point
    ret = enclave_entry_point(eid);
    if (ret != SGX_SUCCESS) {
        std::cerr << "Enclave call failed: error code " << std::hex << ret << std::endl;
        sgx_destroy_enclave(eid);
        return -1;
    }

    // Destroy the enclave
    sgx_destroy_enclave(eid);

    return 0;
}
