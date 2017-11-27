//
// Created by brout_m on 14/04/17.
//

#include <algorithm>
#include <iostream>
#include "Splitter.hpp"

const std::vector<std::string> & Splitter::getTokens() const
{
    return m_tokens;
}

void Splitter::split(std::string const &p_parse,
                     const std::string &p_delimiters,
                     bool p_trim)
{
    size_t l_pos {0};
    std::string::const_iterator l_found {p_parse.cend()};
    std::string l_word;

    while (l_pos < p_parse.length())
    {
        l_found = std::find_first_of(p_parse.cbegin() + l_pos,
                                     p_parse.cend(),
                                     p_delimiters.cbegin(),
                                     p_delimiters.cend());
        std::for_each(p_parse.cbegin() + l_pos, l_found,
                      [&l_word](char const c) {
                          l_word.push_back(c);
                      });
        l_pos += l_word.length() + 1;
        if (!l_word.empty() || !p_trim)
            m_tokens.push_back(l_word);
        l_word.clear();
    }
}

void Splitter::clear()
{
    m_tokens.clear();
}

void Splitter::moveTokensTo(std::vector<std::string> &vec)
{
    vec.clear();
    vec = m_tokens;
}

