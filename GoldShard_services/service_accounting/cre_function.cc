#include "cre_function.h"

string TypeCRE_SwapParis( list<vector<string> >& list_event ,Trade * td, CRE_TYPE type , Service_accounting *sa )
{
       if(type==CRE_TYPE::ENG)          return string("15ENG");
       if(type==CRE_TYPE::ECH)          return string("15ECH");
       if(type==CRE_TYPE::REVERSAL_ENG) return string("15ENG");
       if(type==CRE_TYPE::REVERSAL_ECH) return string("15ECH");

       clog<<"[ERROR]:["<<__FILE__<<":"<<__func__<<":"<<__LINE__<<"] event not managed "<<type<< endl;
       throw 1;

}



string isReversal( list<vector<string> >& list_event ,Trade * td, CRE_TYPE type , Service_accounting *sa )
{
       if(type==CRE_TYPE::ENG)          return string(" ");
       if(type==CRE_TYPE::ECH)          return string(" ");
       if(type==CRE_TYPE::REVERSAL_ENG) return string("2");
       if(type==CRE_TYPE::REVERSAL_ECH) return string("2");

       clog<<"[ERROR]:["<<__FILE__<<":"<<__func__<<":"<<__LINE__<<"] event not managed "<<type<< endl;
       throw 1;
}


string TODO( list<vector<string> >& list_event ,Trade * td, CRE_TYPE type , Service_accounting *sa )
{
    return string("");
}

string CodeInstrument_RDJ( list<vector<string> >& list_event ,Trade * td, CRE_TYPE type , Service_accounting *sa )
{
    return string("");
}

string dateAsof( list<vector<string> >& list_event ,Trade * td, CRE_TYPE type , Service_accounting *sa )
{
    return string("20200824");
}

string getBackId( list<vector<string> >& list_event ,Trade * td, CRE_TYPE type , Service_accounting *sa )
{
    return string("");
}

string CustRICOS( list<vector<string> >& list_event ,Trade * td, CRE_TYPE type , Service_accounting *sa )
{
    return string("");
}

string getMatDate( list<vector<string> >& list_event ,Trade * td, CRE_TYPE type , Service_accounting *sa )
{
    return string("");
}

string getValueDate( list<vector<string> >& list_event ,Trade * td, CRE_TYPE type , Service_accounting *sa )
{
    return string("");
}

string getSIAM( list<vector<string> >& list_event ,Trade * td, CRE_TYPE type , Service_accounting *sa )
{
    return string("");
}

string getCDR( list<vector<string> >& list_event ,Trade * td, CRE_TYPE type , Service_accounting *sa )
{
    return string("");
}

string getFrontId( list<vector<string> >& list_event ,Trade * td, CRE_TYPE type , Service_accounting *sa )
{
    return string("");
}

string empty_field( list<vector<string> >& list_event ,Trade * td, CRE_TYPE type , Service_accounting *sa )
{
    return string("");
}
/// TODO to delete
string LUDO_TEST( list<vector<string> >& list_event ,Trade * td, CRE_TYPE type , Service_accounting *sa )
{

    static int i;

    if (i== 0){ i++;return string("Hello");}
    else if(i == 1){i++;return string("word");}
    i=0;
    return string("AbC");
        
}




