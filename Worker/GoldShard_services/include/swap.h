/* ______      __    _______ __                   __
  / ____/___  / /___/ / ___// /_  ____ __________/ /
 / / __/ __ \/ / __  /\__ \/ __ \/ __ `/ ___/ __  /
/ /_/ / /_/ / / /_/ /___/ / / / / /_/ / /  / /_/ / 
\____/\____/_/\__,_//____/_/ /_/\__,_/_/   \__,_/  
Developed by GoldShard 2020                       */
#ifndef GOLDSHARD_SWAP_H
#define GOLDSHARD_SWAP_H

#include <boost/property_tree/ptree.hpp>
#include <string>
#include <memory>
#include "trade.h"
#include "tools.h"

using namespace std;
using std::string;
using std::vector;
using boost::property_tree::ptree;

class Swap : public Trade
{
    protected:
    public:
        Swap(shared_ptr<ptree>  pt,string & xml_file):Trade(pt,xml_file){};
        virtual ~Swap(){ };
        virtual const string type_trade(){return string("swap");};

        string & getStartDate() override
        {
            if(StartDate=="")StartDate=GStools::getType<string>("FpML.trade.swap.swapStream.calculationPeriodDates.effectiveDate.unadjustedDate","",*xml,true );
            return StartDate;
        }
        string & getEndDate() override
        {
            if(EndDate=="")EndDate=GStools::getType<string>("FpML.trade.swap.swapStream.calculationPeriodDates.terminationDate.unadjustedDate","",*xml,true );
            return EndDate;
        }

};
//#typedef std::shared_ptr<Swap> SwapPtr;
typedef Swap * SwapPtr;





#endif


