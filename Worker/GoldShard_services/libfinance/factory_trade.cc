/* ______      __    _______ __                   __
  / ____/___  / /___/ / ___// /_  ____ __________/ /
 / / __/ __ \/ / __  /\__ \/ __ \/ __ `/ ___/ __  /
/ /_/ / /_/ / / /_/ /___/ / / / / /_/ / /  / /_/ / 
\____/\____/_/\__,_//____/_/ /_/\__,_/_/   \__,_/  
Developed by GoldShard 2020                       */
#include <boost/property_tree/xml_parser.hpp>

#include "swap.h"
#include "tools.h"

using std::string;
using std::vector;
using std::shared_ptr;
using boost::property_tree::ptree;
using boost::property_tree::ptree_error;

Trade * factory_trade( std::string & xml_filename)
{
    shared_ptr<ptree>  xml ( new  ptree) ;
    Trade * r=NULL;
   
    boost::property_tree::read_xml( xml_filename, *xml  );

    string s=GStools::getType<string>("FpML.trade.tradeHeader.tradeCondition.exchangedProduct1.productType","",*xml,true); 
    string si=GStools::getType<string>("FpML.trade.tradeHeader.partyTradeIdentifier.versionedTradeId.tradeId.<xmlattr>.tradeIdScheme","",*xml,false); 

    if(s=="swap") r= new Swap(xml,xml_filename);
     
    if(r != NULL) clog << "[INFO]:["<<__FILE__<<":"<<__func__<<":"<<__LINE__<<"] creation "<<s<<" Tradeid:" <<si<<":"<<r->getTradeId()<<endl;  
    
    return r;
}
