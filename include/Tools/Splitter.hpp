//
// Created by brout_m on 14/04/17.
//

#ifndef CPP_PLAZZA_SPLITTER_HPP
#define CPP_PLAZZA_SPLITTER_HPP

#include <vector>
#include <string>
#include <map>

class Splitter
{
public:
    Splitter() = default;
    ~Splitter() = default;
    void split(std::string const& p_parse,
               std::string const &p_delimiters = " ",
               bool p_trim = true);
    std::vector<std::string> const &getTokens() const;
    void moveTokensTo(std::vector<std::string> &);
    void clear();

private:
    std::vector<std::string> m_tokens;
};


#endif //CPP_PLAZZA_COMMANDGENERATOR_HPP
