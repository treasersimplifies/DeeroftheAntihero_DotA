#include <eosiolib/eosio.hpp>
#include <eosiolib/print.hpp>
#include <string>
#include <../Players/Players.hpp>

namespace DotA {
    using namespace eosio;
    using std::string;
    typedef Players::city city;

    class Citygroup : public contract {
        using contract::contract;

        public:

            Citygroup(account_name self):contract(self) {}

            typedef multi_index<N(city), city> cityIndex;

            [[eosio::action]]
            void city_init(account_name account);//void add(account_name account, city newProduct);

            [[eosio::action]]
            void attack_city(account_name attacker, uint64_t cityId, uint64_t attack_value);//void buy(account_name buyer, uint64_t productId);

            [[eosio::action]]
            void city_get_by_id(uint64_t cityId);

            [[eosio::action]]
            void city_list_all();//uint64_t cityId

            [[eosio::action]]
            void city_update(account_name account, uint64_t cityId, uint64_t newowner, uint64_t newprofit, int64_t __defense);

            // [[eosio::action]]
            // void remove(account_name account, uint64_t productId);
    };

    EOSIO_ABI(Citygroup, (attack_city)(city_get_by_id)(city_list_all)(city_init)(city_update));
}

