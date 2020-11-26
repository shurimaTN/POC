/* ______      __    _______ __                   __
  / ____/___  / /___/ / ___// /_  ____ __________/ /
 / / __/ __ \/ / __  /\__ \/ __ \/ __ `/ ___/ __  /
/ /_/ / /_/ / / /_/ /___/ / / / / /_/ / /  / /_/ / 
\____/\____/_/\__,_//____/_/ /_/\__,_/_/   \__,_/  
Developed by GoldShard 2020                       */
#ifndef GOLDSHARD_INTERFACE_SERVICE_H
#define GOLDSHARD_INTERFACE_SERVICE_H

#include <dlfcn.h>
#include <string>
#include <iostream>
#include <memory>


class Service 
{
public:
    virtual ~Service() {}
    virtual int run( std::string xml_file)  = 0;
    virtual int run( void * ptr_xml)  = 0;
    virtual void setArgs(const std::string &arg_name, const std::string & value){};
};


using Service_creator_t = Service *(*)();

class Service_factory 
{
public:
    ~Service_factory() {   if (handler) dlclose(handler); }
    Service_factory( const char * library_name) 
    {
        handler = dlopen(library_name, RTLD_NOW);
        if (! handler) 
        {
            std::cout << "Check if "<<library_name<<" is in LD_LIBRARY_PATH" <<std::endl;
            std::cout << "export LD_LIBRARY_PATH=.:$LD_LIBRARY_PATH"<< std::endl;
            throw std::runtime_error(dlerror());
        }
        Reset_dlerror();
        creator = reinterpret_cast<Service_creator_t>(dlsym(handler, "create"));
        Check_dlerror();
    }

    std::unique_ptr<Service> create() const { return std::unique_ptr<Service>(creator()); }


private:
    void * handler = nullptr;
    Service_creator_t creator = nullptr;

    static void Reset_dlerror() { dlerror(); }
    static void Check_dlerror() 
    {
        const char * dlsym_error = dlerror();
        if (dlsym_error) 
        {
            throw std::runtime_error(dlsym_error);
        }
    }
};

#endif
