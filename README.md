# teeConcept
git submodule update --init --recursive
sudo apt-get install sgx-detect
sgx-detect


Option 1: Using Intel SGX Simulator
sudo apt-get update
sudo apt-get install -y build-essential ocaml automake autoconf libtool wget python ocamlbuild unzip
sudo apt-get install -y build-essential libssl-dev libcurl4-openssl-dev libprotobuf-dev cmake pkg-config python

sudo apt-get install -y ocaml ocamlbuild 
sudo apt-get install -y unzip

sudo add-apt-repository ppa:ubuntu-toolchain-r/test
sudo apt-get update

sudo apt-get install gcc-9 g++-9 binutils
sudo update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-9 90
sudo update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-9 90


git clone https://github.com/intel/linux-sgx.git

make SGX_MODE=SIM sdk_install_pkg

cd linux-sgx
make preparation
make NO_CET=1 SGX_MODE=SIM sdk_install_pkg

// make sdk_install_pkg
cd linux/installer/bin
sudo ./sgx_linux_x64_sdk_*.bin
