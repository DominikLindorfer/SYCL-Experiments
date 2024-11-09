// vector_add.cpp
#include <sycl/sycl.hpp>
#include <iostream>
#include <vector>

int main() {
    constexpr size_t N = 4096*4096;
    std::vector<float> A(N, 1.0f);
    std::vector<float> B(N, 2.0f);
    std::vector<float> C(N, 0.0f);

    try {
        sycl::queue q;

        // Create buffers
        sycl::buffer<float, 1> bufA(A.data(), sycl::range<1>(N));
        sycl::buffer<float, 1> bufB(B.data(), sycl::range<1>(N));
        sycl::buffer<float, 1> bufC(C.data(), sycl::range<1>(N));

        // Submit command group to queue
        q.submit([&](sycl::handler& h) {
            // Create accessors
            auto accA = bufA.get_access<sycl::access::mode::read>(h);
            auto accB = bufB.get_access<sycl::access::mode::read>(h);
            auto accC = bufC.get_access<sycl::access::mode::write>(h);

            // Kernel execution
            h.parallel_for<class vector_addition>(sycl::range<1>(N), [=](sycl::id<1> i) {
                accC[i] = accA[i] + accB[i];
            });
        });

        // Wait for queue to finish
        q.wait_and_throw();

    } catch (sycl::exception const& e) {
        std::cerr << "An exception is caught: " << e.what() << "\n";
        return 1;
    }

    // Verify results
    for (size_t i = 0; i < N; ++i) {
        if (C[i] != 3.0f) {
            std::cerr << "Verification failed at index " << i << ": " << C[i] << "\n";
            return 1;
        }
    }

    std::cout << "Vector addition successful!\n";
    return 0;
}
