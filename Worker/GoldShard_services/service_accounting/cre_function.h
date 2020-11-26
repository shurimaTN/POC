/* ______      __    _______ __                   __
  / ____/___  / /___/ / ___// /_  ____ __________/ /
 / / __/ __ \/ / __  /\__ \/ __ \/ __ `/ ___/ __  /
/ /_/ / /_/ / / /_/ /___/ / / / / /_/ / /  / /_/ / 
\____/\____/_/\__,_//____/_/ /_/\__,_/_/   \__,_/  
Developed by GoldShard 2020                       */
#ifndef GOLDSHARD_CRE_FUNC_ACCT_H
#define GOLDSHARD_CRE_FUNC_ACCT_H
#include "service_accounting.h"
#include "libfinance.h"

using std::string;
using std::vector;
using std::list;
using std::shared_ptr;

enum CRE_TYPE { ENG,ECH,REVERSAL_ENG,REVERSAL_ECH};
typedef int (*_Function_Field_Int)(vector<string>&);
typedef string (*_Function_Field_String)( list<vector<string> >& list_event ,Trade * td, CRE_TYPE type, Service_accounting *sa );

string TypeCRE_SwapParis( list<vector<string> >& list_event ,Trade * td, CRE_TYPE type , Service_accounting *sa );
string isReversal( list<vector<string> >& list_event ,Trade * td, CRE_TYPE type , Service_accounting *sa );
string TODO( list<vector<string> >& list_event ,Trade * td, CRE_TYPE type , Service_accounting *sa );
string CodeInstrument_RDJ( list<vector<string> >& list_event ,Trade * td, CRE_TYPE type , Service_accounting *sa );
string dateAsof( list<vector<string> >& list_event ,Trade * td, CRE_TYPE type , Service_accounting *sa );
string getBackId( list<vector<string> >& list_event ,Trade * td, CRE_TYPE type , Service_accounting *sa );
string CustRICOS( list<vector<string> >& list_event ,Trade * td, CRE_TYPE type , Service_accounting *sa );
string getMatDate( list<vector<string> >& list_event ,Trade * td, CRE_TYPE type , Service_accounting *sa );
string getValueDate( list<vector<string> >& list_event ,Trade * td, CRE_TYPE type , Service_accounting *sa );
string getSIAM( list<vector<string> >& list_event ,Trade * td, CRE_TYPE type , Service_accounting *sa );
string getCDR( list<vector<string> >& list_event ,Trade * td, CRE_TYPE type , Service_accounting *sa );
string getFrontId( list<vector<string> >& list_event ,Trade * td, CRE_TYPE type , Service_accounting *sa );
string empty_field( list<vector<string> >& list_event ,Trade * td, CRE_TYPE type , Service_accounting *sa );

    /// TODO to delete
string LUDO_TEST( list<vector<string> >& list_event ,Trade * td, CRE_TYPE type , Service_accounting *sa );


#endif
