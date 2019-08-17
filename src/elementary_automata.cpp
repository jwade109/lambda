
#include <elementary_automata.hpp>

#include <cstdlib>
#include <iostream>
#include <bitset>
#include <sstream>

namespace lambda
{

bool decode_rule(uint8_t rule, bool left, bool center, bool right)
{
    std::bitset<8> bits(rule);
    uint8_t index = (left << 2) + (center << 1) + right;
    return bits[index];
}

std::vector<bool> get_generation(uint8_t rule, uint8_t generation)
{
    return std::vector<bool>();
}

std::vector<bool> next_generation(uint8_t rule,
    const std::vector<bool> &current_state)
{
    if (current_state.size() == 0) return std::vector<bool>();

    size_t size = current_state.size();
    std::vector<bool> star_trek(size + 2); // TNG

    for (size_t i = 0; i < star_trek.size(); ++i)
    {
        bool left = false, center = false, right = false;
        if (i > 1 && i < size + 2) left = current_state.at(i - 2);
        if (i > 0 && i < size + 1) center = current_state.at(i - 1);
        if (i < size) right = current_state.at(i);

        bool result = decode_rule(rule, left, center, right);
        star_trek.at(i) = result;
    }

    return star_trek;
}

std::string pretty(uint8_t rule, uint8_t generations,
    const std::vector<bool> &seed)
{
    std::stringstream ss;
    std::vector<std::vector<bool>> generations_list;
    generations_list.resize(generations);
    generations_list[0] = {1};
    for (size_t i = 1; i < generations; ++i)
    {
        generations_list[i] = next_generation(rule, generations_list[i - 1]);
    }
    size_t max_size = generations_list[generations - 1].size();

    for (const auto &gen : generations_list)
    {
        ss << "  ";
        for (size_t i = 0; i < (max_size - gen.size())/2; ++i)
        {
            ss << " ";
        }
        for (bool cell : gen)
        {
            ss << (cell ? "▄" : " ");
        }
        ss << "\n";
    }
    ss << "\n";

    return ss.str();
}

} // namespace lambda
