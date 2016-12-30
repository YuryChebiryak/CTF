//
//  main.cpp
//  CtfParser
//
//  Created by Yury Chebiryak on 01/09/16.
//  Copyright © 2016 Yury Chebiryak. All rights reserved.
//

#include <iostream>
#include <boost/spirit/include/qi.hpp>
#include <boost/fusion/adapted.hpp>
#include <map>
//#include <utility>


namespace qi = boost::spirit::qi;

template <typename Iterator>
struct keys_and_values
: qi::grammar<Iterator, std::map<std::string, std::string>()>
{
    keys_and_values()
    : keys_and_values::base_type(query)
    {
        query =  pair >> *((qi::lit(';') | '&') >> pair);
        pair  =  key >> -('=' >> value);
        key   =  qi::char_("a-zA-Z_") >> *qi::char_("a-zA-Z_0-9");
        value = +qi::char_("a-zA-Z_0-9");
    }
    qi::rule<Iterator, std::map<std::string, std::string>()> query;
    qi::rule<Iterator, std::pair<std::string, std::string>()> pair;
    qi::rule<Iterator, std::string()> key, value;
};




int main(int argc, const char * argv[]) {

    std::string input("key1=value1;key2;key3=value3");  // input to parse
    std::string::iterator begin = input.begin();
    std::string::iterator end = input.end();
    
    keys_and_values<std::string::iterator> p;    // create instance of parser
    std::map<std::string, std::string> m;        // map to receive results
    bool result = qi::parse(begin, end, p, m);   // returns true if successful
    
    // insert code here...
    std::cout << result;
    return 0;
}
