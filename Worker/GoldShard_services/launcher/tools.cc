#include "tools.h"



namespace tools 
{
                
                list<string> application::largs;
                map<string, string > application::args;
		
                std::string & trim(std::string & str,char char_to_trim)
		{
			str.erase(str.find_last_not_of(char_to_trim)+1);
			str.erase(0,str.find_first_not_of(char_to_trim));
			return str;
		}

		std::string & rtrim(std::string & str,char char_to_trim)
		{
			str.erase(str.find_last_not_of(char_to_trim)+1);
			return str;
		}

		std::string & ltrim(std::string & str,char char_to_trim)
		{
			str.erase(0,str.find_first_not_of(char_to_trim));
			return str;
		}

		std::string & lower(std::string & Str)
		{
			std::transform(Str.begin(), Str.end(), Str.begin(), ::tolower);
			return Str;
		}

		std::string & upper(std::string & Str)
		{
			std::transform(Str.begin(), Str.end(), Str.begin(), ::toupper);
			return Str;
		}

		std::string & delete_char( std::string & str,char char_to_delete)
		{
			str.erase( std::remove( str.begin(), str.end(), char_to_delete ), str.end() );
			return str;
		}

		void explode(const std::string &s,char separator,std::vector<string> &v)
		{
			std::istringstream iss (s);//;
			std::string mot;
			while ( std::getline( iss, mot, separator ) )
			v.insert(v.end(),trim(mot));
		}

/*		void setratefields(_variant_t & amount,_variant_t & dps, _variant_t & sign, double rate_value, int size_max)
		{

			if( rate_value == 0.0)return;


			std::ostringstream oss;
			oss<< std::setprecision(size_max)<<std::fixed<< rate_value;
			std::string s=oss.str();

			if(s.find('-')!= std::string::npos )
			{
				sign.SetString("-");
				delete_char(s,'-');
			}

			if(s.find('.')!= std::string::npos )
			{
				std::istringstream iss( s );
				std::string decimal;
				std::getline( iss, decimal, '.' ) ;
				ltrim(decimal,'0');
				std::string floatant;
				std::getline( iss, floatant, '.' ) ;
				rtrim(floatant,'0');
				dps.intVal=floatant.size();
				if(size_max-decimal.size()<(unsigned)dps.intVal)
				{
					dps.intVal=size_max-decimal.size();
					s=decimal+floatant.substr(0,dps.intVal);
				}
				else
					s=decimal+floatant;

			}
			else
			{
   				dps.intVal=0;
			}
			std::istringstream iss2( s );
			iss2>> amount.dblVal;
		}
*/

}; // namespace tools
