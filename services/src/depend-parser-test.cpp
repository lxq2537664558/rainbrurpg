#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <iostream>
#include <string>
#include <algorithm>

#include "DependParser.hpp"

using namespace boost::spirit;
using namespace std;
using namespace boost::spirit::classic;
int main(int argc, char **argv)
{
  const string input("WikiName > 3.15");
    /**
    parse_info<string::const_iterator> pInfo = parse(input.begin(), 
						     input.end(),
                                                     depend_parser
                                                    );
    **/
    parse_info<string::const_iterator> pInfo = p
      qi::phrase_parse(input.begin(), input.end(), depend_parser);

        
    return 0;
}
