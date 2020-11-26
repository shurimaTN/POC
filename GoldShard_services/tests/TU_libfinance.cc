#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE UnitTest
#include <boost/test/included/unit_test.hpp>
#include <string>

using namespace std;
#include "libfinance.h"
 
 
BOOST_AUTO_TEST_CASE(libfinance_Swap)
{

    Trade * t;
    std::string file("/home/ludo/GoldShard_services/xml_test/swap2.xml");   
    std::unique_ptr<Trade> tu1(t=factory_trade(file)) ; 

    if(t->type_trade()=="swap")

    BOOST_CHECK( t->type_trade() == "swap" );
    BOOST_CHECK( 1 == 0 );
    BOOST_CHECK( 1 == 1 );

}
