#include <algorithm>
#include <iostream>

#include <boost/spirit/include/classic.hpp>

#include "DependParser.hpp"

using namespace boost::spirit;
using namespace std;

int main(int argc, char **argv)
{
  const string input("WikiName > 3.15");
    vector<double> values;
    Synthax parser;
    parse_info<string::const_iterator> pInfo = parse(input.begin(), 
						     input.end(),
                                                     parser
                                                    );

    copy(values.begin(), values.end(), ostream_iterator<double>(cout, "\n"));
        
    return 0;
}
