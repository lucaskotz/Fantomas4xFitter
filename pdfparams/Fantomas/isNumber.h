// Header file containing the function isNumber(). Returns true
// if argument is a number. Returns false if argument is not a
// number. 

#include <sstream>

template<typename T>
bool isNumber(T x){
  std::string s;
  std::stringstream ss; 
  ss << x;
  ss >>s;
  if(s.empty() || std::isspace(s[0]) || std::isalpha(s[0])) return false ;
  char * p ;
  strtod(s.c_str(), &p) ;
  return (*p == 0) ;
}
