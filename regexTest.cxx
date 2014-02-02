#include <string>
#include <iostream>
#include <boost/regex.hpp>

using namespace std;
using namespace boost;

int main()
{
  regex reg("(?<=seed' t='n'>)(\\d+)(?=<)");
  
  string testString = "<var n='seed' t='n'>52176</var>";
  smatch results;
  
  regex_search(testString,results,reg);
  
  cout << results[0] << endl;
  
  return 0;
  
}
