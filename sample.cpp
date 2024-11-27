#include <immintrin.h>
#include <iostream>

void add_arrays_avx(const float* A, const float* B, float* C, size_t size) {
    size_t i = 0;

    for (; i + 7 < size; i += 8) {
        __m256 a = _mm256_loadu_ps(&A[i]);
        __m256 b = _mm256_loadu_ps(&B[i]);

        __m256 c = _mm256_add_ps(a, b);
        _mm256_storeu_ps(&C[i], c);
    }

    for (; i < size; ++i) {
        C[i] = A[i] + B[i];
    }
}

void print_array(const float* arr, size_t size)
{
    size_t i = 0;
    for (; i < size; i++)
    {
        std::cout << arr[i] << " ";
    }
    std::cout << '\n';
}

int main() {
    const size_t size = 32;  
    float A[size], B[size], C[size];

    for (size_t i = 0; i < size; ++i) {
        A[i] = i * 1.0f;
        B[i] = i * 2.0f;
    }

    print_array(A, size);
    print_array(B, size);


    add_arrays_avx(A, B, C, size);


    std::cout << "Result of A + B = C:" << std::endl;
    for (size_t i = 0; i < size; ++i) {
        std::cout << C[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}
