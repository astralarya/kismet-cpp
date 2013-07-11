// Prompt.cpp
// Mara Kim
//
// Display an interactive prompt and deliver results to scanner

#include "Prompt.h"


KismetScannerBase::Input::Input():
d_in(0),
d_lineNr(1)
{}

KismetScannerBase::Input::Input(std::istream *iStream, size_t lineNr):
d_in(iStream),
d_lineNr(lineNr)
{}

size_t Prompt::get()
{
    switch (size_t ch = next())         // get the next input char
    {
        case '\n':
            ++d_lineNr;
        // FALLING THROUGH

        default:
        return ch;
    }
}

size_t Prompt::next()
{
    size_t ch;

    if (d_deque.empty())                    // deque empty: next char fm d_in
    {
        if (d_in == 0)
            return AT_EOF;
        ch = d_in->get();
        return *d_in ? ch : AT_EOF;
    }

    ch = d_deque.front();
    d_deque.pop_front();

    return ch;
}

void Prompt::reRead(size_t ch)
{
    if (ch < 0x100)
    {
        if (ch == '\n')
            --d_lineNr;
        d_deque.push_front(ch);
    }
}

void Prompt::reRead(std::string const &str, size_t fm)
{
    for (size_t idx = str.size(); idx-- > fm; )
        reRead(str[idx]);
}

size_t Prompt::lineNr() const {
    return d_lineNr;
}

// Force closing the stream
void Prompt::close() {
    delete d_in;
    d_in = 0;                   // switchStreams also closes
}
