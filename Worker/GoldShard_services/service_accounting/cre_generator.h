/* ______      __    _______ __                   __
  / ____/___  / /___/ / ___// /_  ____ __________/ /
 / / __/ __ \/ / __  /\__ \/ __ \/ __ `/ ___/ __  /
/ /_/ / /_/ / / /_/ /___/ / / / / /_/ / /  / /_/ / 
\____/\____/_/\__,_//____/_/ /_/\__,_/_/   \__,_/  
Developed by GoldShard 2020                       */
#ifndef GOLDSHARD_CRE_GENERATOR_H
#define GOLDSHARD_CRE_GENERATOR_H
#include "service_accounting.h"
#include "libfinance.h"

using std::string;
using std::vector;
using std::list;
using std::shared_ptr;


enum ALIGN { LEFT,RIGHT };
enum TYPE_FIELD { STRING,INT,DOUBLE};

class field
{
    public: 
    
    const char * field_name;    
    long unsigned int width;
    char fill;
    ALIGN align;
    int precision;
    TYPE_FIELD type;
    void * ptr_func;
 
    field(const char * fn,TYPE_FIELD tp,ALIGN al,char f,long unsigned int w,int p,void *pf):field_name(fn),width(w),fill(f),align(al),precision(p),type(tp),ptr_func(pf){};
};

class cre_generator
{
    string fname;
    list<field> list_format;
    string separator;

    public:

    inline void add_field(const char * fn,TYPE_FIELD tp,ALIGN al,char f,long unsigned int w,int p,void *pf)
    {
        list_format.push_back(field (fn,tp,al,f,w,p,pf));
    }

    void load_format(const string & formatname);

    void generate(string & result, list<vector<string> >& list_event ,Trade * td,  CRE_TYPE type, Service_accounting *sa )
    {
        string s;
        stringstream ss;
        
        for(auto &f:list_format)
        {
            if(f.type==STRING)
            {
                _Function_Field_String func= (_Function_Field_String) (f.ptr_func);
                s = func(list_event,td,type,sa);
                if(s.size()>f.width)
                {
                    clog<<"[ERROR]:["<<__FILE__<<":"<<__func__<<":"<<__LINE__<<"] format error, size of field greater than"<<f.width <<":"<<f.field_name<<":"<<s<< endl;
                    throw 1;
                }

                if(f.align==RIGHT)
                    ss <<right <<setfill(f.fill)<< setw(f.width)<<s; 
                else
                    ss <<right <<setfill(f.fill)<< setw(f.width)<<s; 
            }
        }
        result= ss.str();
    };


};///cre_generator

#endif
