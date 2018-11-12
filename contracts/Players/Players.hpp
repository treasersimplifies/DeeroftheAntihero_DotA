#include <eosiolib/eosio.hpp>
#include <eosiolib/print.hpp>
#include <string>

namespace DotA {
    using namespace eosio;
    using std::string;

    class Players : public contract {
        using contract::contract;   //in order to use its constructor 
       
        public:
            Players(account_name self):contract(self) {}

            [[eosio::action]]
            void hi(const account_name account, string& username){
                print( "Hello, it is a beautiful player, ", name{account},", ", username);
                print("\n");
                print(" ==============\n ");
            }

            [[eosio::action]]//**
            void add(const account_name account, string& username);

            [[eosio::action]]
            void update(account_name account, int64_t porperty);

            [[eosio::action]]//**
            void getplayer(const account_name account);

            // [[eosio::action]]
            // void addability(const account_name account, string& ability);

            struct city { // all items purchased from the Marketplace.
                uint64_t city_id;
                string city_name;
                uint64_t profit;//power
                uint64_t defense;//health
                uint64_t owner;
                // string ability;
                // uint64_t level_up;

                uint64_t primary_key() const { return city_id; }

                EOSLIB_SERIALIZE(city, (city_id)(cityname)(profit)(defense)(owner))//(ability)(level_up)
            };

            // [[eosio::action]]//**
            // void attackcity(const account_name account, city acity);//string& cityname

            [[eosio::action]]//**
            void addcities(const account_name account, city acity);

             [[eosio::action]]//**
            void removecities(const account_name account, city acity);

            struct player {
                uint64_t account_name;
                string username;
                int64_t porperty;
                vector<city> cities;//
                // vector<item> inventory;//
                // uint64_t health_points = 1000;
                // uint64_t energy_points = 1000;
                
                uint64_t primary_key() const { return account_name; }

                EOSLIB_SERIALIZE(player, (account_name)(username)(porperty)(cities))//(level)(health_points)(energy_points)(abilities)(inventory)
            };
          
            typedef multi_index<N(player), player> playerIndex;
    };

    EOSIO_ABI(Players, (hi)(add)(update)(getplayer)(addcities)(removecities))// (additem)(addability) If you don't specifies actions here, .ABI won't specifies either. 
}
