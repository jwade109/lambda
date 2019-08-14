#ifndef LAMBDA_ELEMENTARY_AUTOMATA_HPP
#define LAMBDA_ELEMENTARY_AUTOMATA_HPP

#include <cstdint>
#include <vector>
#include <string>

namespace lambda
{

std::vector<bool> get_generation(uint8_t rule, uint8_t generation);

std::vector<bool> next_generation(uint8_t rule,
    const std::vector<bool> &current_state);

std::string pretty(uint8_t rule, uint8_t generations,
    const std::vector<bool> &seed = {1});

} // namespace lambda

#endif // LAMBDA_ELEMENTARY_AUTOMATA_HPP
