// Prompt.h
// Mara Kim
//
// Display an interactive prompt and deliver results to scanner

#ifndef PROMPT_H
#define PROMPT_H

#include <iostream>
#include <queue>

class Prompt {
public:
    Input();
    Input(std::istream *iStream); // dynamically allocated iStream
    size_t get(); // get next character
    size_t lineNr() const;
    void reRead(size_t ch); // push back 'ch' (if <= 0x100)
    void reRead(std::string const &str, size_t fmIdx); // push back str from idx 'fmIdx'
    void close(); // delete dynamically allocated
private:
    size_t next();                      // obtain the next character
    std::deque<unsigned char> d_deque;  // pending input chars
    std::istream *d_in;                 // ptr for easy streamswitching
    size_t d_lineNr;                    // line count
};

#undef PROMPT_H
