/* ______      __    _______ __                   __
  / ____/___  / /___/ / ___// /_  ____ __________/ /
 / / __/ __ \/ / __  /\__ \/ __ \/ __ `/ ___/ __  /
/ /_/ / /_/ / / /_/ /___/ / / / / /_/ / /  / /_/ / 
\____/\____/_/\__,_//____/_/ /_/\__,_/_/   \__,_/  
Developed by GoldShard 2020                       */
#ifndef GOLDSHARD_TOOLS_H
#define GOLDSHARD_TOOLS_H

#include<string>
#include<iostream>
#include<vector>
#include <boost/property_tree/ptree.hpp>
#include <boost/foreach.hpp>
#include <boost/optional.hpp> 
#include <boost/property_tree/detail/file_parser_error.hpp>

using std::string;
using std::stringstream;

namespace GStools
{

inline string & trim(string & str,char char_to_trim=' ')
{
    str.erase(str.find_last_not_of(char_to_trim)+1);
    str.erase(0,str.find_first_not_of(char_to_trim));
    return str;
}
            
    
inline void explode(const std::string &s,char separator,std::vector<string> &v)
{
    std::istringstream iss (s);//;
    std::string mot;
    while ( std::getline( iss, mot, separator ) )
    v.insert(v.end(),trim(mot));
}

        
inline string  StringTokenizer(const string & pattern)
{
    stringstream ssp(pattern);
    string mot,result;
    while ( std::getline( ssp, mot, '\'' ) )
    {
        if(mot[0]=='%') /// DATE MODE
        {
            char tmp[1024];
	    time_t rawtime;
	    struct tm * timeinfo;
	    time ( &rawtime );
	    timeinfo = localtime ( &rawtime );
	    strftime( tmp, 1024, mot.c_str(), timeinfo);
	    result+=tmp;
        }
        else  if(mot[0]=='$') /// VAR MODE
        {
            char * var;
	    if ((var = getenv (mot.c_str()+1))!=NULL)result+=var;
        }
        /*else  if(mot[0]=='*') /// ARG MODE
        {
            map<string, string >::iterator it;
	    it=args.find(mot.c_str()+1);
	    if(it!=args.end())result+=it->second;
        }*/
        else result +=mot;
    }
    return result;
}

template <typename T> 
T getType(const char * xpath, T default_value ,boost::property_tree::ptree & pt, bool trow_mode=false)
{ 

    if(trow_mode)return pt.get<T>(xpath); 

    boost::optional<T>  value;
    T s;
    value = pt.get_optional<T>(xpath );
    s  = get_optional_value_or(value, default_value);
    return s;
}


} //namespace GStools
#endif

