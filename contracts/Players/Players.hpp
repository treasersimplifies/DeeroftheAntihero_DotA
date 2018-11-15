#include <eosiolib/eosio.hpp>
#include <eosiolib/print.hpp>
#include <string>

namespace DotA {
    using namespace eosio;
    using std::string;

    class Players : public contract {//[[eosio::contract]]s
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

            struct title{
                uint64_t title_id;
                string name;
                int64_t num;
                uint64_t primary_key() const { return title_id; }
            };

            [[eosio::action]]//test
            void addtitle(const account_name account, title atitle);

            struct city { 
                uint64_t city_id;
                string city_name;
                uint64_t profit;//power
                uint64_t defense;//health
                uint64_t owner;
                uint64_t primary_key() const { return city_id; }
                // “city_id”:1,"city_name":"GoldCity","profit":10,"defense":10,"owner":888}
                // EOSLIB_SERIALIZE(city, (city_id)(city_name)(profit)(defense)(owner))//(ability)(level_up)
            };

            [[eosio::action]]//**
            void addcity(const account_name account, city acity);

             [[eosio::action]]//**
            void removecity(const account_name account, city acity);

            struct player { //[[eosio::table]]
                uint64_t account_name;
                string username;
                int64_t porperty;
                vector<city> cities_owned;
                // vector<simplecity> simplecities_owned;
                vector<title> titles_owned;
                //future : owned_city_number
                uint64_t primary_key() const { return account_name; }
                // EOSLIB_SERIALIZE(player, (account_name)(username)(porperty)(cities_owned)(titles_owned))
            };
          
            typedef multi_index<N(player), player> playerIndex;
    };

    EOSIO_ABI(Players, (hi)(add)(update)(getplayer)(addcity)(removecity)(addtitle))// (additem)(addability) If you don't specifies actions here, .ABI won't specifies either. 
}

//waiting to improve :
// player_list_all
//