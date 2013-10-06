#include <boost/spirit/include/classic.hpp>
#include <boost/spirit/include/qi_grammar.hpp>

struct Syntax :
  public boost::spirit::qi::grammar<Syntax>
{
public:
    Syntax( CParser &parser );
    virtual ~Syntax();
    template <typename ScannerT>
    struct definition
    {
    public:
        definition( Syntax const &self )
        {
	  integer = lexeme[ +digit ];
        }
        boost::spirit::symbols<int> vars;
        boost::spirit::rule<ScannerT> integer, factor, term,
            expression, assignment, var_decl, declaration,
            baseExpression;
        const boost::spirit::rule<ScannerT> &start() const { return baseExpression; }
    };
    friend struct definition;
private:
    Private::FinishedProcessing *m_finishedProcessing;
};
