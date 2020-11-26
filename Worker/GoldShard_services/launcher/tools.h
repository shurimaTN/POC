/* ______      __    _______ __                   __
  / ____/___  / /___/ / ___// /_  ____ __________/ /
 / / __/ __ \/ / __  /\__ \/ __ \/ __ `/ ___/ __  /
/ /_/ / /_/ / / /_/ /___/ / / / / /_/ / /  / /_/ / 
\____/\____/_/\__,_//____/_/ /_/\__,_/_/   \__,_/  
Developed by GoldShard 2020                       */

#ifndef GOLDSHARD_LOCAL_TOOLS_H
#define GOLDSHARD_LOCAL_TOOLS_H

#include <iostream>
#include<string>
#include<map>
#include<vector>
#include<list>
#include<sstream>
#include<algorithm>
#include <fstream>
#include <iomanip>

//#include <cctype>
//#include <time.h>


using std::string;
using std::map;
using std::vector;
using std::list;
using std::stringstream;





namespace tools
{
void explode(const string &s,char separator,vector<string> &v);
template<class Type> std::string implode(std::string sep , std::list<Type>& l)
{
    std::ostringstream oss;
    int i=0;
    for( auto it=l.begin();it!=l.end();++it,++i)
    {
     if(i !=0) oss<<sep;
     oss<<*it;
    }

    return oss.str();
};

template<class Type> std::string implode(std::string sep , std::vector<Type>& v)
{
    std::ostringstream oss;
    int i=0;
    for( auto it=v.begin();it!=v.end();++it,++i)
    {
     if(i !=0) oss<<sep;
     oss<<*it;
    }

    return oss.str();
};

	string & trim(string & str,char char_to_trim=' ');
	string & rtrim(string & str,char char_to_trim=' ');
	string & ltrim(string & str,char char_to_trim=' ');
	string & lower(string & Str);
	string & upper(string & Str);
	string & delete_char( string & str,char char_to_delete);

	class application
	{
	public:

		static map<string, string > args;
                static list<string> largs;

		static int init(int argc,char ** argv)
		{
			list<string>l;
			string arg;
			for(int i=1;i<argc;++i)
			{
				arg=string(argv[i]);
				if(*argv[i]=='-')upper(arg);
				l.push_back(arg);
			}

			string key,value;

			for(list<string>::iterator it=l.begin();it!=l.end();)
			{
				if((*it)[0]!='-')
				{
                                    value=(*it);
                                    largs.push_back(value);
                                    ++it;
				}
                                else 
                                {    
				    key=(*it);
				    key.erase(0,1);
				    if(key.size()==0)
				    {
					std::clog << "arg error"<< std::endl;
					exit(1);
				    }
				    ++it;
                                    if(it==l.end())args[key]="";
				    else
				    {
					value=(*it);
					if(value[0]=='-')args[key]="";
					else
					{
						args[key]=value;
						++it;
					}
				    }
                                }
			}
			return 0;
		};

		static string  StringTokenizer(const string & pattern)
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
					//time_t intps=time(NULL);
					//struct tm * pdh = localtime(&intps);
					strftime( tmp, 1024, mot.c_str(), timeinfo);
					//strftime( tmp, 1024, "", timeinfo);
					result+=tmp;
				}
				else  if(mot[0]=='$') /// VAR MODE
				{
					char * var;
					if ((var = getenv (mot.c_str()+1))!=NULL)result+=var;
				}
				else  if(mot[0]=='*') /// ARG MODE
				{
					map<string, string >::iterator it;
					it=args.find(mot.c_str()+1);
					if(it!=args.end())result+=it->second;
				}
				else result +=mot;
			}
			return result;
		};
	};// class application



	}; // namespace tools

namespace CSV
{
typedef void (*_Function_vs)(vector<string>&);

template < typename _Function_vs>
long int foreachrow(const char * filename , _Function_vs _f, bool skip_header=false, char separator=';')
{

    std::ifstream In(filename);
	string line;


    if(skip_header==true) std::getline(In,line);// skip header

    int i=0;
	while ( std::getline( In, line) )
	{
	    vector<string> v;
        tools::explode(line,separator,v);
        _f(v);
        i++;
	}

return i;
}

}; //namespace CSV

#endif
