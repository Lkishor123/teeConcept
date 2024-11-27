SGX_SDK ?= /opt/intel/sgxsdk
SGX_MODE ?= HW
SGX_ARCH ?= x64
SGX_DEBUG ?= 1

Enclave_Name := enclave.signed.so
Enclave_Config_File := Enclave.config.xml

Enclave_Cpp_Files := enclave.cpp

Enclave_Include_Paths := -I$(SGX_SDK)/include
Enclave_C_Flags := -nostdinc -fvisibility=hidden -fpie -fstack-protector -fno-strict-overflow \
                   -ffunction-sections -fdata-sections -fstack-protector-strong \
                   -Werror -Wall -Wextra -Winit-self -Wpointer-arith -Wreturn-type \
                   -Wformat-security -Wmissing-include-dirs -Wformat -Wformat-nonliteral \
                   -Wcast-align -Wcast-qual -Wwrite-strings -Wconversion -Wshadow \
                   -Wsign-conversion -Wstrict-aliasing=2 -Wstrict-overflow=2 \
                   -Wswitch-default -Wundef -fno-builtin-printf

Enclave_Cpp_Flags := $(Enclave_C_Flags) -std=c++11
Enclave_Linker_Flags := -Wl,--no-undefined -nostdlib -nodefaultlibs -nostartfiles \
                        -L$(SGX_SDK)/lib64 -Wl,--whole-archive -lsgx_tstdc -lsgx_tcrypto \
                        -Wl,--no-whole-archive -Wl,--start-group -lsgx_trts \
                        -Wl,--end-group -Wl,-Bstatic -Wl,-Bsymbolic -Wl,--no-undefined \
                        -Wl,-pie,-eenclave_entry -Wl,--export-dynamic  \
                        -Wl,--defsym,__ImageBase=0

ifeq ($(SGX_DEBUG),1)
	Enclave_Cpp_Flags += -O0 -g
else
	Enclave_Cpp_Flags += -O2
endif

.PHONY: all clean

all: $(Enclave_Name)

$(Enclave_Name): enclave.so
	@echo "Signing the enclave..."
	$(SGX_SDK)/bin/x64/sgx_sign sign -key Enclave_private.pem \
		-enclave enclave.so \
		-out $@ \
		-config $(Enclave_Config_File)

enclave.so: Enclave_t.o $(Enclave_Cpp_Files)
	@echo "Linking the enclave..."
	$(CXX) $^ -o $@ $(Enclave_Linker_Flags)

Enclave_t.c: enclave.edl
	@echo "Generating trusted bridge..."
	$(SGX_SDK)/bin/x64/sgx_edger8r --trusted $< --search-path $(SGX_SDK)/include

Enclave_t.o: Enclave_t.c
	$(CC) $(Enclave_Include_Paths) $(Enclave_C_Flags) -c $< -o $@

enclave.o: enclave.cpp
	$(CXX) $(Enclave_Include_Paths) $(Enclave_Cpp_Flags) -c $< -o $@

clean:
	rm -f *.o enclave.so Enclave_t.* $(Enclave_Name)
