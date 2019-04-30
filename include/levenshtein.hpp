#ifndef LAMBDA_LEVENSHTEIN
#define LAMBDA_LEVENSHTEIN

#include <algorithm>
#include <array>

namespace lambda
{

template <class A, class B>
size_t levenshtein(const std::vector<A> &left, const std::vector<B> &right)
{
    const size_t M = left.size();
    const size_t N = right.size();

    if (M == 0 || N == 0) return 0;

    std::vector<std::vector<size_t>> dist;

    for (size_t i = 0; i <= M; ++i)
    {
        dist.push_back(std::vector<size_t>(N));
        for (size_t j = 0; j <= N; ++j) dist[i].push_back(0);
    }

    for (size_t i = 1; i <= M; ++i) dist[i][0] = i;
    for (size_t i = 1; i <= N; ++i) dist[0][i] = i;

    for (size_t j = 1; j <= N; j++)
    {
        for (size_t i = 1; i <= M; i++)
        {
            dist[i][j] = std::min(std::min(
                dist[i-1][j] + 1, dist[i][j-1] + 1),
                dist[i-1][j-1] + (left[i-1] == right[j-1] ? 0 : 1));
        }
    }
    return dist[M][N];
}

size_t levenshtein(const std::string &left, const std::string &right);

template <class A, size_t N, class B, size_t M>
size_t levenshtein(const std::array<A, N> &left,
                   const std::array<B, M> &right)
{
    std::vector<A> lvec(begin(left), end(left));
    std::vector<B> rvec(begin(right), end(right));
    return levenshtein(lvec, rvec);
}

} // namespace lambda

#endif // LAMBDA_LEVENSHTEIN
