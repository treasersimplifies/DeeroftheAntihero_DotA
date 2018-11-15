#include <eosiolib/eosio.hpp>
#include <eosiolib/print.hpp>
#include <string>

namespace DotA {
    using namespace eosio;
    using std::string;

    class Citygroup : public contract {
        using contract::contract;

        public:

            Citygroup(account_name self):contract(self) {}
            
             struct city { 
                uint64_t city_id;
                string city_name;
                uint64_t profit;
                uint64_t defense;
                uint64_t owner;
                uint64_t primary_key() const { return city_id; }
            };

            typedef multi_index<N(city), city> cityIndex;

            [[eosio::action]]
            void cityinit(account_name account);//void add(account_name account, city newProduct);

            [[eosio::action]]
            void getbyid(uint64_t cityId);

            [[eosio::action]]
            void citylistall();//uint64_t cityId

            [[eosio::action]]
            void updatecity(account_name account, uint64_t cityId, uint64_t newowner, uint64_t newprofit, int64_t __defense);

            [[eosio::action]]
            void attack(account_name attacker, uint64_t cityId, uint64_t attack_value);//void buy(account_name buyer, uint64_t productId);

            // [[eosio::action]]
            // void remove(account_name account, uint64_t productId);
    };

    EOSIO_ABI(Citygroup, (cityinit)(getbyid)(citylistall)(updatecity)(attack));
}

