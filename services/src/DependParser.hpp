#include <string>
#include <boost/spirit/include/qi.hpp>
#include <boost/fusion/include/adapt_struct.hpp>

struct Date {
    int year, month, day;
};
struct Time {
    int hour, minute, second;
};

BOOST_FUSION_ADAPT_STRUCT(
    Date,
    (int, year)
    (int, month)
    (int, day)
)

BOOST_FUSION_ADAPT_STRUCT(
    Time,
    (int, hour)
    (int, minute)
    (int, second)
)

namespace qi = boost::spirit::qi;
namespace ascii = boost::spirit::ascii;
typedef std::string::const_iterator Iterator;

class DateParser:
    public qi::grammar < Iterator, Date() > {
        qi::rule < Iterator, Date() > main;
    public:
        DateParser(): base_type(main) {
            main %= qi::int_ >> '-' >> // Year
                    qi::int_ >> '-' >> // Month
                    qi::int_;          // Day
        }
};

class TimeParser:
    public qi::grammar < Iterator, Time() > {
        qi::rule < Iterator, Time() > main;
    public:
        TimeParser(): base_type(main) {
            main %= qi::int_ >> ':' >> // Hour
                    qi::int_ >> ':' >> // Minute
                    qi::int_;          // Second
        }
};

class DateTimeParser:
    public qi::grammar < Iterator, boost::variant<Date, Time>() > {
        qi::rule < Iterator, boost::variant<Date, Time>()> main;
    public:
        DateTimeParser(): base_type(main) {
            main %= date_parser | time_parser;
        }
        DateParser date_parser;
        TimeParser time_parser;
};
