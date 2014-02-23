// KismetInput.cpp
// Mara Kim
//
// An interactive prompt for KismetScanner


KismetInput::Input():
d_in(0),
d_lineNr(1) {
}

KismetInput::Input(std::istream *iStream, size_t lineNr):
d_in(iStream),
d_lineNr(lineNr) {
}


size_t KismetInput::get() {
    // get the next input char
    switch (size_t ch = next()) {
    case '\n':
        if(std::find(history.begin(),history.end(),line) == history.end()) {
            ::Personality::set_seed(line);
            history.push_back(line);
            if(history.size() > 5)
                history.pop_front();
        }
        line.clear();
        ++d_lineNr;
        return ch;
    default:
        line.push_back((char)ch);
        return ch;
    }
}

size_t KismetInput::next() {
    size_t ch;

    if(d_deque.empty()) {
        // deque empty: next char fm d_in
        if(d_in == 0)
            return AT_EOF;
        if(Options::Instance()->get(Project::INTERACTIVE)) {
            if(::Prompt::eof()) {
                return AT_EOF;
            }
            // readline prompt
            std::string read(::Prompt::readline(prompt()));
            if(::Prompt::eof()) {
                d_deque.push_back('\n');
                d_deque.push_back('e');
                d_deque.push_back('x');
                d_deque.push_back('i');
                d_deque.push_back('t');
                d_deque.push_back('\n');
                d_deque.push_back(AT_EOF);
            }
            for(auto it = read.begin(); it != read.end(); it++)
                d_deque.push_back(*it);
            d_deque.push_back('\n');
            d_deque.push_back(AT_EOF);
        } else {
            // get char from stream
            ch = d_in->get();
            return *d_in ? ch : AT_EOF;
        }
    }

    ch = d_deque.front();
    d_deque.pop_front();

    return ch;
}

std::string KismetInput::prompt() {
    std::stringstream ss;
    ss << d_lineNr << "> ";
    return ss.str();
}

void KismetInput::reRead(size_t ch) {
    if(ch < 0x100) {
        if(ch == '\n')
            --d_lineNr;
        d_deque.push_front(ch);
    }
}

void KismetInput::reRead(std::string const &str, size_t fm) {
    for (size_t idx = str.size(); idx-- > fm; )
        reRead(str[idx]);
}

size_t KismetInput::lineNr() const {
    return d_lineNr;
}

void KismetInput::close() {
    // Force closing the stream
    delete d_in;
    // switchStreams also closes
    d_in = 0;
}
