/* ______      __    _______ __                   __
  / ____/___  / /___/ / ___// /_  ____ __________/ /
 / / __/ __ \/ / __  /\__ \/ __ \/ __ `/ ___/ __  /
/ /_/ / /_/ / / /_/ /___/ / / / / /_/ / /  / /_/ / 
\____/\____/_/\__,_//____/_/ /_/\__,_/_/   \__,_/  
Developed by GoldShard 2020                       */
#ifndef GOLDSHARD_ATD_H
#define GOLDSHARD_ATD_H

#include<string>
#include<vector>
#include<list>
#include <memory>
#include <iomanip>     
#include <vector>
#include <list>
#include <map>
#include <fstream>
#include <iterator>

#include "libfinance.h"
using std::string;
using std::vector;
using std::list;
using std::map;
using std::ifstream;
using std::stringstream;

enum  events {EV_CON,EV_INT,EV_FEE,CRE,OTHER,EV_MAX};
inline int index(string& s)
{
    if(s=="CON")return EV_CON;
    if(s=="INT")return EV_INT;
    if(s=="FEE")return EV_FEE;
    if(s=="CRE")return CRE;
    return OTHER;
}

inline const char * rindex(events ev)
{
    if(ev==EV_CON)return "CON";
    if(ev==EV_INT)return "INT";
    if(ev==EV_FEE)return "FEE";
    if(ev==CRE)return "CRE";
    return "OTH";
}

class accounting_trade_data
{
    public:

    bool save_hist_file;
    string hist_file;
    vector<list<vector<string> > > to_save;
    vector<list<vector<string> > > building_event;
    vector<list<vector<string> > > hist_event;
    
    map<string, list<vector<string> > > gen_cre;
    map<string, list<vector<string> > > rev_cre;
    
    void determine_cre_to_generate_with_historical_and_building_event_list();

    accounting_trade_data(string &  hist_filename):save_hist_file(false),hist_file(hist_filename),to_save(EV_MAX),building_event(EV_MAX),hist_event(EV_MAX)
    {
        ifstream In(hist_filename);
        string line;
         while ( std::getline( In, line) )
        {
            vector<string> v;
            GStools::explode(line,';',v);
            hist_event[ index(v[0]) ].push_back(v);
        }
    };


    virtual ~accounting_trade_data( )
    { 
        if (!save_hist_file)
            clog << "[ERROR]: cannot save Histfile:"<< hist_file<<endl;
        else 
        {
        clog << "[SUCCESS]: save Histfile:"<< hist_file<<" and destroy Accounting Structure of trade "<<endl;
        ofstream ofs (hist_file, std::ofstream::out);
    
        for (int i=0;i<EV_MAX;i++)
            for (auto& v : to_save[i])
            {
                std::copy (v.begin(), v.end(), std::ostream_iterator<string>(ofs, ";"));
                ofs << endl;
            }			
        ofs.close();
        }
    };


     void push_events(events ev, int leg_number, string trigger_date,string valuedate,double amount,string ccy,string regen_key,string timestamp)
     {
        vector<string> v;
        stringstream ss;
        ss.setf(ios::fixed);
        ss.precision(2);
        
        ss << rindex(ev)<<";"<<leg_number<<";"<<trigger_date<<";"<<valuedate<<";"<<amount<<";"<<ccy<<";"<< regen_key<<";"<<timestamp;
        GStools::explode(ss.str(),';',v);
        building_event[ev].push_back(v);
        clog <<"[DEBUG]:"<< ss.str()<<endl;
     }
};

typedef shared_ptr<accounting_trade_data> atdPtr;




#endif
