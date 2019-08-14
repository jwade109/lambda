
#include <elementary_automata.hpp>

#include <cstdlib>
#include <iostream>
#include <bitset>

namespace lambda
{

bool decode_rule(uint8_t rule, bool left, bool center, bool right)
{
    std::bitset<8> bits(rule);
    bool rules[2][2][2];

    rules[1][1][1] = bits[7];
    rules[1][1][0] = bits[6];
    rules[1][0][1] = bits[5];
    rules[1][0][0] = bits[4];
    rules[0][1][1] = bits[3];
    rules[0][1][0] = bits[2];
    rules[0][0][1] = bits[1];
    rules[0][0][0] = bits[0];

    return rules[left][center][right];
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
    std::vector<std::vector<bool>> generations_list;
    generations_list.resize(generations);
    generations_list[0] = {1};
    size_t max_size = generations_list[0].size();
    for (size_t i = 1; i < generations; ++i)
    {
        generations_list[i] = next_generation(rule,
            generations_list[i - 1]);
        max_size += 2;
    }

    for (const auto &gen : generations_list)
    {
        std::cout << "  ";
        for (size_t i = 0; i < (max_size - gen.size())/2; ++i)
        {
            std::cout << " ";
        }
        for (bool cell : gen)
        {
            std::cout << (cell ? "▄" : " ");
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

} // namespace lambda
