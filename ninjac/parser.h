#ifndef _PARSER_H
#define	_PARSER_H

#include <string>
#include <set>

class Parser {
    
public:
                            Parser      ();
    void                    parse       (std::string& source);

protected:
    std::set<std::string>   keywords;
};


#endif	/* _PARSER_H */
