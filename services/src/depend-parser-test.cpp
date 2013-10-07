#include<iostream>
#include<cstdio>

#include "DependParser.hpp"

struct Printer : public boost::static_visitor<> {
    void operator()(Date a) const {
        printf("Year: %d, Month: %d, Day: %d\n", a.year, a.month, a.day);
    }
    void operator()(Time a) const {
        printf("Hour: %d, Minute: %d, Second: %d\n", a.hour, a.minute, a.second);
    }
    void operator()(WikiWord a) const {
        printf("Wikiword: %c\n", a.content);
    }
};

int main() {
    std::string s;
    std::getline(std::cin, s);
    Iterator beg = s.begin(), end = s.end();
    WikiWord ret;
    phrase_parse(beg, end, WikiWordParser(), ascii::space, ret);
    if (beg != end)
        puts("Parse failed.");
    else
      puts("Parse succeed!");
 
%   boost::apply_visitor(Printer(), ret);
}
