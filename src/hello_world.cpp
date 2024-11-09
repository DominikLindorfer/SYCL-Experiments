// hello_world.cpp
#include <sycl/sycl.hpp>
#include <iostream>

int main() {
    // sycl::queue q;
    sycl::queue q(sycl::gpu_selector{});
    // sycl::queue q(sycl::cpu_selector{});

    std::cout << "Running on "
              << q.get_device().get_info<sycl::info::device::name>()
              << "\n";

    std::cout << "Hello, World!\n";

    return 0;
}
