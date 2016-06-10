/* 
 * server - The RainbruRPG's services binary.
 *
 * Copyright (C) 2014-2016 Jérôme Pasquier
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

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
  void operator()(std::string a) const {
    std::cout << "WikiWord is '" << a << "'" << std::endl; 
    }
};

int main() {
  std::string s;
  std::getline(std::cin, s);
  Iterator beg = s.begin(), end = s.end();
 std:string ret;
  phrase_parse(beg, end, WikiWordParser(), ascii::space, ret);
  if (beg != end)
    puts("Parse failed.");
  else
    std::cout << "WikiWord is '" << ret << "'" << std::endl; 
}
