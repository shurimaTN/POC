/* ______      __    _______ __                   __
  / ____/___  / /___/ / ___// /_  ____ __________/ /
 / / __/ __ \/ / __  /\__ \/ __ \/ __ `/ ___/ __  /
/ /_/ / /_/ / / /_/ /___/ / / / / /_/ / /  / /_/ / 
\____/\____/_/\__,_//____/_/ /_/\__,_/_/   \__,_/  
Developed by GoldShard 2020                       */
#include "service.h"
#include "libfinance.h"
#include "accounting_trade_data.h"
#include "service_accounting.h"
#include "cre_function.h"
#include "cre_generator.h"

using std::string;
using std::vector;
using std::shared_ptr;
using boost::property_tree::ptree;
using boost::property_tree::ptree_error;

using namespace std;



class Service_accounting : public Service 
{
    cre_generator  gen_cre;
    string timestamp;
    string asof;
    void acct_contingent(SwapPtr sw, atdPtr atd);
    void acct_interet(SwapPtr sw,atdPtr atd){};///TODO not implemented
    void acct_fee(SwapPtr sw, atdPtr atd){};///TODO not implemented
    void acct_xnl(SwapPtr sw,atdPtr atd){};///TODO not implemented
    void acct_set(SwapPtr sw,atdPtr atd){};///TODO not implemented

    void create_cre(Trade*  td, atdPtr atd);
public:
    int  run( std::string xml_file)  override ;
    int  run( void * ptr_trade)  override ;
    void setArgs( const std::string &arg_name, const std::string & value) override ;

};

extern "C" 
{
    Service * create() {  return new Service_accounting ; }
}

//---------------------------------------------------------------------------------------



   
///enum CRE_TYPE { ENG,ECH,REVERSAL_ENG,REVERSAL_ECH};

void Service_accounting :: create_cre(Trade *  td, atdPtr atd)
{
    /// todo .... en fonction du deal demander le bon format
    gen_cre.load_format("SWAP_PARIS");

    CRE_TYPE  type;

    string cre;
    for(auto & p : atd->rev_cre)
    {

        auto it=p.second.begin();
        auto& v=*it;
        if(v[0]=="CON" && v[4].find("-")==std::string::npos)type=CRE_TYPE::REVERSAL_ENG;
        else if(v[0]=="CON" && v[4].find("-")!=std::string::npos) type=CRE_TYPE::REVERSAL_ECH;
        else 
        {
            clog<<"[ERROR]:["<<__FILE__<<":"<<__func__<<":"<<__LINE__<<"] event not managed "<<v[0]<< endl;
            throw 1;
        }

        clog << "[INFO]: create new REVERSAL CRE with "<< p.second.size() <<" posting with key :"<< p.first <<endl;
        gen_cre.generate(cre,p.second,td,type,this);
        clog <<"[INFO]CRE:"<< cre<<endl;
    }

    for(auto & p :atd->gen_cre)
    {
        auto it=p.second.begin();
        auto& v=*it;

        if(v[0]=="CON" && v[4].find("-")==std::string::npos)type=CRE_TYPE::ENG;
        else if(v[0]=="CON" && v[4].find("-")!=std::string::npos)type=CRE_TYPE::ECH;// si négatif ... reduction de ntl --> ECH
        else
        {
            clog<<"[ERROR]:["<<__FILE__<<":"<<__func__<<":"<<__LINE__<<"] event not managed "<<v[0]<< endl;
            throw 1;
        }

        clog << "[INFO]: create new CRE with "<< p.second.size() <<" posting with key :"<< p.first <<endl;
        gen_cre.generate(cre,p.second,td,type,this);
        clog <<"[INFO]CRE:"<< cre<<endl;
    }

    atd->save_hist_file=true;
}


void  Service_accounting :: setArgs( const std::string &arg_name, const std::string & value) 
{
    clog<< "[INFO]:["<<__FILE__<<":"<<__LINE__<<"] setArgs:"<<arg_name<<"="<<value << endl;  
    if(arg_name=="ASOF")asof=value;
}

int Service_accounting :: run( std::string xml_file)  
{   
    clog <<"[INFO]: -------------------------------------------------------------------------------------------"<< endl;
    clog <<"[INFO]: ---------------------------- $"<<__FILE__<<" ----------------------------------------"<< endl;
    clog <<"[INFO]: -------------------------------------------------------------------------------------------"<< endl;
    
    try
    {
        clog << "[INFO]:["<<__FILE__<<":"<<__func__<<":"<<__LINE__<<"] open XML:"<<xml_file<< endl;  
 
        Trade * t=factory_trade(xml_file) ; 
        std::unique_ptr<Trade> ut(t) ; 
        if(  t == NULL)return 1; 
        else  
            return run((void *)t);
    
    }
    catch(boost::property_tree::xml_parser::xml_parser_error &x)
    {
        clog<<"[ERROR]:["<<__FILE__<<":"<<__func__<<":"<<__LINE__<<"] catch exception in service "<<x.what()<< endl;
    }

    catch(const ptree_error &e)
    {
        clog<<"[ERROR]:["<<__FILE__<<":"<<__func__<<":"<<__LINE__<<"] catch exception in service :"<<xml_file<<":"<<e.what()<< endl;
    }

    catch(...)
    {
        clog<<"[ERROR]:["<<__FILE__<<":"<<__func__<<":"<<__LINE__<<"] catch exception in service "<<xml_file<< endl;
    }
    
    return 1;
}

int Service_accounting  :: run( void * ptr_trade) 
{
    try
    {
    clog << "[INFO]:["<<__FILE__<<":"<<__LINE__<<"] run in $asof:"<<asof<< endl; 
    timestamp=	GStools::StringTokenizer("%Y-%m-%d:%T"); 
    clog << "[INFO]:["<<__FILE__<<":"<<__LINE__<<"] execution $timestamp:"<<timestamp<< endl; 
    string s=((Trade*)ptr_trade)->getXML_filename()+ ".acct";  
    /// creation class de conteneur pour la compta d'un deal et load l'hist
    atdPtr atd(new accounting_trade_data(s));
     
    if(((Trade*)ptr_trade)->type_trade()=="swap")
    {

        SwapPtr sw((Swap *) ptr_trade);

        acct_contingent(sw,atd);
        acct_interet(sw,atd);
        acct_fee(sw,atd);
        acct_xnl(sw,atd);
        acct_set(sw,atd);
        ///TODO add other events ..... 
    }//SWAP

    ///TODO add other Tradetype
    

    atd->determine_cre_to_generate_with_historical_and_building_event_list();
    create_cre((Trade*)ptr_trade,atd);

    return 0;

    }
    catch(const ptree_error &e)
    {
        clog<<"[ERROR]:["<<__FILE__<<":"<<__func__<<":"<<__LINE__<<"] catch exception in service :"<<((Trade*)ptr_trade)->getXML_filename()<<e.what()<< endl;
    }

    catch(...)
    {
        clog<<"[ERROR]:["<<__FILE__<<":"<<__func__<<":"<<__LINE__<<"] catch exception in service:"<<((Trade*)ptr_trade)->getXML_filename()<< endl;
    }
    return 1;
}

void Service_accounting :: acct_contingent( SwapPtr sw, atdPtr atd)
{

 string tradedate= sw->getTradeDate();
 string startdate= sw->getStartDate();
 string enddate= sw->getEndDate();

 double delta;
 double r;
 int leg_number=0;
/// Step 1 & 2  create table and clean line with delta at 0 or after asof date
    
    clog << "[INFO]: create building events list for CON event"<< endl;
    
    for( auto& v : sw->xml->get_child("FpML.trade.swap")) ///iterate swap for manage Leg by Leg
    {
        if(v.first=="swapStream") /// it s a Leg !
        {
            leg_number++;
            double initialValue=GStools::getType<double>("calculationPeriodAmount.calculation.notionalSchedule.notionalStepSchedule.initialValue",0.0,v.second);
            string ccy=GStools::getType<string>("calculationPeriodAmount.calculation.notionalSchedule.notionalStepSchedule.currency","",v.second);
            
            r=initialValue;
            clog << "[DEBUG]:------------ LEG "<<leg_number<<"-------------"<<endl;
            
            atd->push_events(EV_CON,leg_number, tradedate,startdate,initialValue,ccy,"K1", timestamp);
            for( auto& step : v.second.get_child("calculationPeriodAmount.calculation.notionalSchedule.notionalStepSchedule")) 
            {
                if(step.first=="step")
                {
                     string stepdate=GStools::getType<string>("stepDate","",step.second);
                     double stepvalue=GStools::getType<double>("stepValue",0.0,step.second);
                     if (stepdate > asof) break;

                     if(r == stepvalue)delta=0.0;
                     else delta=stepvalue-r;
                     r=stepvalue;

                     if(delta != 0.0)
                        atd->push_events(EV_CON,leg_number, stepdate,stepdate ,delta,ccy,"K1", timestamp);
                }
            }
            if(enddate<=asof)
                atd->push_events(EV_CON,leg_number, enddate,enddate ,r*-1.0,ccy,"K1", timestamp);
        }// swapstream
    }
}

