/* ______      __    _______ __                   __
  / ____/___  / /___/ / ___// /_  ____ __________/ /
 / / __/ __ \/ / __  /\__ \/ __ \/ __ `/ ___/ __  /
/ /_/ / /_/ / / /_/ /___/ / / / / /_/ / /  / /_/ / 
\____/\____/_/\__,_//____/_/ /_/\__,_/_/   \__,_/  
Developed by GoldShard 2020                       */
#ifndef GOLDSHARD_TRADE_H
#define GOLDSHARD_TRADE_H


#include <string>
#include <memory>
#include <boost/property_tree/ptree.hpp>

#include "tools.h"

using namespace std;
using std::string;
using std::vector;
using boost::property_tree::ptree;

class Trade
{
protected: 
    string XML_filename;
    string TradeDate;
    string TradeId;
    string StartDate;
    string EndDate;
 public:
    std::shared_ptr<ptree>  xml;
    Trade(std::shared_ptr<ptree>  pt,string & fn):XML_filename(fn),xml(pt){};
    virtual ~Trade(){};
    
        
     string & getXML_filename(){return XML_filename;}

     string & getTradeId()
     {
        if(TradeId=="")
        {
            TradeId=GStools::getType<string>("FpML.trade.tradeHeader.partyTradeIdentifier.versionedTradeId.tradeId","",*xml,true);
        }

        return TradeId;
     }

    string & getTradeDate()
    {
        if(TradeDate=="")TradeDate=GStools::getType<string>("FpML.trade.tradeHeader.tradeDate","",*xml,true);
        return TradeDate;
    }
    
    //method to override
    virtual const string type_trade() = 0;
    virtual string & getStartDate()   = 0;
    virtual string & getEndDate()     = 0;

};


#endif


