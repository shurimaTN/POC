#include "service.h"
#include "tools.h"

using namespace std;
#include "libfinance.h"

int main(int argc, char** argv)
{
    tools::application::init(argc,argv);


    string xmlfile=tools::application::StringTokenizer("*I");
    string asof=tools::application::StringTokenizer("*ASOF");

    if(asof=="") asof=tools::application::StringTokenizer("%Y-%m-%d");


    cout << "Try to launch :"<<xmlfile<<" in asof :"<< asof << endl;    
    for (auto & s : tools::application::largs)
    {
        cout << "on service :"<<s << endl;
    }
    
    Trade * t;
    try
    {
        t=factory_trade(xmlfile) ; 
    }
    catch(...)
    {
            cout << "Erreur factory_trade  :"<<xmlfile<< endl;
            exit(1);
    }

    std::unique_ptr<Trade> tu1(t) ; 
    for (auto & s : tools::application::largs)
    {
        cout << "Run service :"<<s << endl;
        try
        {
            Service_factory serv_factory(s.c_str());
            std::unique_ptr<Service> service  = serv_factory.create();

            service->setArgs("ASOF",asof);
            service->run((void * )t);
        }
        catch(...)
        {
            cout << "Erreur sur service :"<<s<< endl;
        }
    }

    /*
    Service_factory acct_factory("service_accounting.so");
    std::unique_ptr<Service> accounting = acct_factory.create();

    accounting->setArgs("ASOF","2021-05-10");
    accounting->run("/home/ludo/GoldShard_services/xml_test/swap1.xml");
    accounting->run("/home/ludo/GoldShard_services/xml_test/test1.xml");
    accounting->run("/home/ludo/GoldShard_services/xml_test/unknown_file.xml");
    accounting->run("/home/ludo/GoldShard_services/xml_test/swap2.xml");
    */
    return 0;
}
