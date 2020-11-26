#include "service.h"


int main(int argc, char** argv)
{
    {
    Service_factory acct_factory("service_accounting.so");
    std::unique_ptr<Service> accounting = acct_factory.create();

    accounting->setArgs("ASOF","2021-05-10");
    accounting->run("/home/ludo/GoldShard_services/xml_test/swap1.xml");
    accounting->run("/home/ludo/GoldShard_services/xml_test/test1.xml");
    accounting->run("/home/ludo/GoldShard_services/xml_test/unknown_file.xml");
    accounting->run("/home/ludo/GoldShard_services/xml_test/swap2.xml");
    }
    return 0;
}
