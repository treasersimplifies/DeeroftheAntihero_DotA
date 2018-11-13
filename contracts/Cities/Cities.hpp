#include <eosiolib/eosio.hpp>
#include <eosiolib/print.hpp>
#include <string>

namespace DotA {
    using namespace eosio;
    using std::string;

    class Citygroup : public contract {
        using contract::contract;   //in order to use its constructor 
       
        public:
            Citygroup(account_name self):contract(self) {}

            [[eosio::action]]
            void hi(const account_name account, string& username){
                print( "Hello, it is a beautiful test, ", name{account},", ", username);
            }

            [[eosio::action]]
            void add(uint64_t deer, string city_name, string owner_username, int64_t initial_defense);

            [[eosio::action]]
            void update(account_name account, int64_t porperty);

            [[eosio::action]]
            void addcities(account_name account, string& city);

             [[eosio::action]]
            void removecities(account_name account, string& city);

            [[eosio::action]]
            void getplayer(const account_name account);

            struct city {
                uint64_t deer;
                string city_name;
                string owner_username;
                int64_t defense;
                int64_t profitrate;

                uint64_t primary_key() const { return deer; }

                EOSLIB_SERIALIZE(city, (deer)(city_name)(owner_username)(defense)(profitrate))
            };
          
            typedef multi_index<N(city), city> cityIndex;
    };

    EOSIO_ABI(Cities, (hi)(add)(update)(getplayer)(addcities)(removecities))// (additem)(addability) If you don't specifies actions here, .ABI won't specifies either. 
}
