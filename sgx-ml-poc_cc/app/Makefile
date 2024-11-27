SGX_SDK ?= /opt/intel/sgxsdk
SGX_MODE ?= HW
SGX_ARCH ?= x64
SGX_DEBUG ?= 1

App_Name := app
App_Cpp_Files := app.cpp

App_Include_Paths := -I$(SGX_SDK)/include

App_Cpp_Flags := -std=c++11 -fstack-protector -fPIC -Wformat -Wformat-security \
                 -Werror -Wall -Wextra -Winit-self -Wpointer-arith -Wreturn-type \
                 -Wformat-nonliteral -Wcast-align -Wcast-qual -Wwrite-strings \
                 -Wconversion -Wshadow -Wsign-conversion -Wstrict-overflow=2 \
                 -Wswitch-default -Wundef -fno-builtin-printf

App_Link_Flags := -L$(SGX_SDK)/lib64 -lsgx_urts

ifeq ($(SGX_DEBUG),1)
	App_Cpp_Flags += -O0 -g
else
	App_Cpp_Flags += -O2
endif

.PHONY: all clean

all: $(App_Name)

$(App_Name): Enclave_u.o $(App_Cpp_Files)
	@echo "Compiling the application..."
	$(CXX) $^ -o $@ $(App_Cpp_Flags) $(App_Include_Paths) $(App_Link_Flags)

Enclave_u.c: ../enclave/enclave.edl
	@echo "Generating untrusted bridge..."
	$(SGX_SDK)/bin/x64/sgx_edger8r --untrusted $< --search-path $(SGX_SDK)/include

Enclave_u.o: Enclave_u.c
	$(CC) $(App_Cpp_Flags) $(App_Include_Paths) -c $< -o $@

clean:
	rm -f *.o Enclave_u.* $(App_Name)
