#include <boost/spirit/include/classic.hpp>
#include <boost/spirit/include/qi.hpp>

// see http://www.boost.org/doc/libs/1_54_0/libs/spirit/doc/html/spirit/qi/tutorials/employee___parsing_into_structs.html

using namespace boost::spirit;

struct depend
{
    int age;
    std::string surname;
    std::string forename;
    double salary;
};


template <typename Iterator>
struct depend_parser : qi::grammar<Iterator, depend(), ascii::space_type>
{
    depend_parser() : depend_parser::base_type(start)
    {
        using qi::int_;
        using qi::lit;
        using qi::double_;
        using qi::lexeme;
        using ascii::char_;

        quoted_string %= lexeme['"' >> +(char_ - '"') >> '"'];

        start %=
            lit("employee")
            >> '{'
            >>  int_ >> ','
            >>  quoted_string >> ','
            >>  quoted_string >> ','
            >>  double_
            >>  '}'
            ;
    }

    qi::rule<Iterator, std::string(), ascii::space_type> quoted_string;
    qi::rule<Iterator, depend(), ascii::space_type> start;
};
