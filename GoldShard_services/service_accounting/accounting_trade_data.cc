/* ______      __    _______ __                   __
  / ____/___  / /___/ / ___// /_  ____ __________/ /
 / / __/ __ \/ / __  /\__ \/ __ \/ __ `/ ___/ __  /
/ /_/ / /_/ / / /_/ /___/ / / / / /_/ / /  / /_/ / 
\____/\____/_/\__,_//____/_/ /_/\__,_/_/   \__,_/  
Developed by GoldShard 2020                       */
#include <iostream>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/foreach.hpp>
#include <boost/optional.hpp> 
#include <boost/property_tree/detail/file_parser_error.hpp>
#include <boost/property_tree/ini_parser.hpp>
#include <boost/property_tree/exceptions.hpp>
#include <memory>
#include <iomanip>     
#include <vector>
#include <list>
#include <map>
#include <fstream>
#include <iterator>
//#include "service.h"
#include "libfinance.h"
#include "accounting_trade_data.h"

using namespace std;
using std::string;
using std::vector;
using std::shared_ptr;
using boost::property_tree::ptree;
using boost::property_tree::ptree_error;

    void accounting_trade_data::determine_cre_to_generate_with_historical_and_building_event_list()
    {
        ///Step 3
        // Matched: no action 
        // UnMatched: CreateNew and Reverse previous
        // OrphanNew: Create"
        // OrphanHist: Reverse
        //
        for (int i=0;i<CRE;i++)
        {
            for( auto iv= building_event[i].begin();iv != building_event[i].end();)
            {
                bool funded=false;
                auto & v=*iv;
                for( auto ih= hist_event[i].begin();ih != hist_event[i].end();ih++)
                {
                    auto & h=*ih;
                    if( v[1] == h[1] && v[2] == h[2] )/// clef de matching
                    {   
                        auto ih2=ih;
                        auto iv2=iv;
                        ih++;
                        iv++;
                        funded=true;
                        if( v[4] == h[4] && v[5] == h[5] && v[6] == h[6] )
                        {   ///matched
                            // pas de Creation ou reverse , mettre le hist dans to_save
                            to_save[i].splice(to_save[i].end(),hist_event[i],ih2,ih);
                            building_event[i].erase(iv2);
                        }
                        else ///unmatched
                        {
                            // create v et reverse h, mettre v dans to_save
                            gen_cre[v[0]+v[2]].push_back(v);
                            rev_cre[h[0]+h[2]].push_back(h);
                            to_save[i].splice(to_save[i].end(),building_event[i],iv2,iv);
                            hist_event[i].erase(ih2);
                        }
                        break;
                    }
                } //hist_event
                if (funded== false)
                {
                  /// create v and move v in to_save
                  gen_cre[v[0]+v[2]].push_back(v);
                  auto iv2=iv;
                  iv++;
                  to_save[i].splice(to_save[i].end(),building_event[i],iv2,iv);
                }
            } //building_event
            /// iterer ce qu il reste dans hist ( orphans ) et les reverser sans sauver
            for( auto& h :hist_event[i])
                            rev_cre[h[0]+h[2]].push_back(h);

        }// i<CRE

        int i=CRE;
        to_save[i].splice(to_save[i].end(), hist_event[i], hist_event[i].begin(),hist_event[i].end());
        i=OTHER;
        to_save[i].splice(to_save[i].end(), hist_event[i], hist_event[i].begin(),hist_event[i].end());
        //diff_hist_and_build_event();
        
    };


