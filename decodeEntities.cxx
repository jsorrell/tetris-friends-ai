#include <string>
#include <sstream>
#include <iostream>
#include <map>

using namespace std;

void stringFromCharCode(int code,string out)
{
  out[0] = (char)code;
  out[1] = '\0';
}

void stringCharAt(string str,int loc,char *out)
{
  out[0] = str[loc];
  out[1] = '\0';
}

int getCharCode(string param1)
{
  unsigned int x;   
  std::stringstream ss;
  ss << std::hex << param1.substr(3,param1.length()-4);
  ss >> x;
  return x;
}

string decodeEntities(string param1)
{
  string loc2,loc3,loc4,loc5,loc6;
  int i;
  char out[2] = {0,0};
  
   map<string,string> ascTabRev;
   map<string,string>::iterator it;
   
   ascTabRev["&gt;"] = ">";
   ascTabRev["&lt;"] = "<";
   ascTabRev["&amp;"] = "&";
   ascTabRev["&apos;"] = "\'";
   ascTabRev["&quot;"] = "\"";
  
  loc2 = "";
  while (i < param1.length())
  {
    stringCharAt(param1,i,out);
    loc3 = out;
    if (loc3 == "&")
    {
      loc4 = loc3;
      do
      {
        i++;
        stringCharAt(param1,i,out);
        loc5 = out;
        loc4 += loc5;
      } while (loc5 != ";" && i < param1.length());
      
      it = ascTabRev.find(loc4);
      if (it != ascTabRev.end())
      {
        loc6 = it->second;
        loc2 += loc6;
      
      } else {
        stringFromCharCode(getCharCode(loc4),out);
        loc2+=out;
      }
      i++;
    }
    return loc2;
  }



}