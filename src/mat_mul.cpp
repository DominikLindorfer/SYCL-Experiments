// matrix_mul.cpp
#include <sycl/sycl.hpp>
#include <iostream>
#include <vector>

int main() {
    constexpr size_t N = 4096;
    std::vector<float> A(N * N, 1.0f);
    std::vector<float> B(N * N, 2.0f);
    std::vector<float> C(N * N, 0.0f);

    try {
        sycl::queue q(sycl::gpu_selector{});
        // sycl::queue q;
        
        std::cout << "Running on "
              << q.get_device().get_info<sycl::info::device::name>()
              << "\n";

        sycl::buffer<float, 2> bufA(A.data(), sycl::range<2>(N, N));
        sycl::buffer<float, 2> bufB(B.data(), sycl::range<2>(N, N));
        sycl::buffer<float, 2> bufC(C.data(), sycl::range<2>(N, N));

        q.submit([&](sycl::handler& h) {
            auto accA = bufA.get_access<sycl::access::mode::read>(h);
            auto accB = bufB.get_access<sycl::access::mode::read>(h);
            auto accC = bufC.get_access<sycl::access::mode::write>(h);

            h.parallel_for<class matrix_multiplication>(sycl::range<2>(N, N), [=](sycl::id<2> idx) {
                size_t row = idx[0];
                size_t col = idx[1];
                float sum = 0.0f;
                for (size_t k = 0; k < N; ++k) {
                    sum += accA[row][k] * accB[k][col];
                }
                accC[row][col] = sum;
            });
        });

        q.wait_and_throw();

    } catch (sycl::exception const& e) {
        std::cerr << "An exception is caught: " << e.what() << "\n";
        return 1;
    }

    // Verify results
    for (size_t i = 0; i < N * N; ++i) {
        if (C[i] != N * 2.0f) {
            std::cerr << "Verification failed at index " << i << ": " << C[i] << "\n";
            return 1;
        }
    }

    std::cout << "Matrix multiplication successful!\n";
    return 0;
}
