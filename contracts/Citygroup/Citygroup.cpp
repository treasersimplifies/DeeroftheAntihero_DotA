#include "Citygroup.hpp"
#include <eosiolib/asset.hpp>

namespace DotA {
   [[eosio::action]]
    void Citygroup::city_init(account_name account) {
        require_auth(account);

        //productIndex products(_self, _self);
        cityIndex cities(_self, _self);

        auto iterator = cities.find(1);//newProduct.product_id
        eosio_assert(iterator == cities.end(), "Cities for this ID already exists");
        cities.emplace(account, [&](auto& city) {
            city.product_id = 1;//
            city.cityname = "GoldCity";
            city.profit = 5*20/45;//5/person * 20 players / 45mins
            city.defense = 10;
            city.owner = 0;//??? god's account_name;
        });

        auto iterator = cities.find(2);//newProduct.product_id
        eosio_assert(iterator == cities.end(), "Cities for this ID already exists");
        cities.emplace(account, [&](auto& city) {
            city.product_id = 2;//
            city.cityname = "WoodCity";
            city.profit = 5*20/45;//5/person * 20 players / 45mins
            city.defense = 9;
            city.owner = 0;//??? god's account_name;
        });
    }

    [[eosio::action]]//still have some problems
    void Citygroup::attack_city(account_name attacker, uint64_t cityId, uint64_t attack_value){
        cityIndex cities(_self, _self);

        auto iterator = cities.find(cityId);
        eosio_assert(iterator != cities.end(), "The city not found");
    
        auto thecity = cities.get(cityId);
        eosio_assert(thecity.owner != attacker, "You can't attack a city you own.");

        //Create asset
        //asset({amount}, string_to_symbol({precision}, {symbol}));
        asset productPrice = asset(product.price, string_to_symbol(4, "EOSC"));
        
        // Do inline trasfer
        // action({permission_level}, {contract_deployer}, {contract_action}, {data_to_pass}).send();
        action(vector<permission_level>(), N(anorak), N(transfer), make_tuple(attacker, _self, productPrice, string(""))).send();

        // Execute action from another contract
        // action({permission_level}, {contract_deployer}, {contract_action}, {data_to_pass}).send();
        action(vector<permission_level>(), N(market), N(additem), make_tuple(buyer, 
            product.product_id,
            product.name,
            product.power,
            product.health,
            product.ability,
            product.level_up
        )).send();

        update(buyer, product.product_id, -1);
    }
    
    [[eosio::action]]
    void Citygroup::city_get_by_id(uint64_t cityId) {
        cityIndex cities(_self, _self);

        auto iterator = cities.find(cityId);
        eosio_assert(iterator != cities.end(), "City not found");

        auto thecity = cities.get(cityId);
        print("Id: ", thecity.city_id);
        print(" | Name: ", thecity.city_name.c_str());
        print(" | Profit: ", thecity.profit);
        print(" | Defense: ", thecity.defense);
        print(" | Owner: ", thecity.owner);
    }

    [[eosio::action]]
    void Citygroup::city_list_all(){
        cityIndex cities(_self, _self);
        uint64_t cityId;
        for(cityId=1;cityId++;cityId<6){
            auto iterator = cities.find(cityId);
            eosio_assert(iterator != cities.end(), "City not found");

            auto thecity = cities.get(cityId);
            print("Id: ", thecity.city_id);
            print(" | Name: ", thecity.city_name.c_str());
            print(" | Profit: ", thecity.profit);
            print(" | Defense: ", thecity.defense);
            print(" | Owner: ", thecity.owner);
        }
    }

    [[eosio::action]]
    void Citygroup::city_update(account_name account, uint64_t cityId, uint64_t newowner, uint64_t newprofit, int64_t __defense) {
        require_auth(account);

        cityIndex cities(_self, _self);

        auto iterator = cities.find(cityId);
        eosio_assert(iterator != cities.end(), "City not found");

        cities.modify(iterator, account, [&](auto& city) {
            city.owner = newowner;
            city.profit = newprofit;
            city.defense += __defense;
        });
    }

}
