#ifndef LAMBDA_CRC_HPP
#define LAMBDA_CRC_HPP

#include <bitset>
#include <sstream>
#include <vector>

namespace lambda
{

std::vector<bool> crc(const std::vector<uint8_t> &data,
                      const std::vector<bool> &poly);

template <size_t N, size_t M>
std::bitset<N-1> crc(const std::bitset<M> &data,
                     const std::bitset<N> &poly)
{
    static_assert(M > N, "Data must be longer than polynomial");
    static_assert(N > 0, "Polynomial must be at least one bit long");

    std::cout << "Data: " << data << std::endl;
    std::cout << "Poly: " << poly << std::endl;

    std::bitset<M+N-1> divisor, result;
    for (size_t i = 0; i < M + N - 1; ++i)
    {
        if (i < N) divisor[i] = poly[i];
        else divisor[i] = false;
        if (i < N - 1) result[i] = false;
        else result[i] = data[i- (N - 1)];
    }

    auto kernel = divisor << (M - 1);

    for (int i = 0; i < M - N + 2; ++i)
    {
        size_t ptr = M + N - i - 2;
        if (!result[ptr])
        {
            kernel >>= 1;
            continue;
        }

        std::cout << "---------------------------" << std::endl;
        std::cout << "Divisor: " << kernel << std::endl;
        result ^= kernel;
        std::cout << "Result:  " << result << std::endl;
        kernel >>= 1;
    }

    std::bitset<N-1> output;
    for (size_t i = 0; i < N; ++i)
        output[i] = result[i];

    std::cout << "Final:   " << output << std::endl;

    std::stringstream ss;
    ss << std::hex << output;
    std::cout << "         0x" << ss.str() << std::endl;

    return output;
}

} // namespace lambda

#endif // LAMBDA_CRC_HPP
