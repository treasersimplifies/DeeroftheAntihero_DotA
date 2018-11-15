#include "Citygroup.hpp"
#include <eosiolib/asset.hpp>
// new city name can be xiangyang city/ winterfell / pingan / longlake
namespace DotA {

    [[eosio::action]]
    void Citygroup::cityinit(account_name account) {
        require_auth(account);
        // if(account != "dota") return;
        //productIndex products(_self, _self);
        cityIndex cities(_self, _self);

        auto iterator = cities.find(1);//newProduct.product_sid
        eosio_assert(iterator == cities.end(), "City for this ID already exists");
        cities.emplace(account, [&](auto& city) {
            city.city_id = 1;//
            city.city_name = "GoldCity";
            city.profit = 5*20/45;//5/person * 20 players / 45mins
            city.defense = 10;
            city.owner = 0;//??? god's account_name;
        });

        iterator = cities.find(2);//newProduct.product_id
        eosio_assert(iterator == cities.end(), "City for this ID already exists");
        cities.emplace(account, [&](auto& city) {
            city.city_id = 2;//
            city.city_name = "WoodCity";
            city.profit = 5*20/45;//5/person * 20 players / 45mins
            city.defense = 5;
            city.owner = 0;//??? god's account_name;
        });
    }
    
    [[eosio::action]]
    void Citygroup::getbyid(uint64_t cityId) {
        cityIndex cities(_self, _self);
        auto iterator = cities.find(cityId);
        eosio_assert(iterator != cities.end(), "City not found.");

        auto thecity = cities.get(cityId);
        print("|-| Id: ", thecity.city_id);
        print(" | CityName: ", thecity.city_name.c_str());
        print(" | Profit: ", thecity.profit);
        print(" | Defense: ", thecity.defense);
        print(" | Owner: ", thecity.owner);
    }

    [[eosio::action]]
    void Citygroup::citylistall(){
        cityIndex cities(_self, _self);
        auto iterator = cities.find(1);
        eosio_assert(iterator != cities.end(), "City not found.");
        auto thecity = cities.get(1);
        
        uint64_t cityId;
        for(cityId=1; cityId < thecity.city_name.size(); cityId++){
            auto iterator = cities.find(cityId);
            // eosio_assert(iterator != cities.end(), "City not found");
            if(!(iterator != cities.end()))break;
            auto thecity = cities.get(cityId);
            print("[Id: ", thecity.city_id);
            print(" | Name: ", thecity.city_name.c_str());
            print(" | Profit: ", thecity.profit);
            print(" | Defense: ", thecity.defense);
            print(" | Owner: ", thecity.owner);
            print("]O.O");
        }
    }

    [[eosio::action]]
    void Citygroup::updatecity(account_name account, uint64_t cityId, uint64_t newowner, uint64_t newprofit, int64_t __defense) {
        require_auth(account);
        // if(account != "dota") return;
        cityIndex cities(_self, _self);
        auto iterator = cities.find(cityId);
        eosio_assert(iterator != cities.end(), "City not found");

        cities.modify(iterator, account, [&](auto& city) {
            city.owner = newowner;
            city.profit = newprofit;
            city.defense += __defense;
        });
    }
    
    [[eosio::action]]//still have some problems
    void Citygroup::attack(account_name attacker, uint64_t cityId, uint64_t attack_value){
        require_auth(attacker);
        cityIndex cities(_self, _self);
        auto iterator = cities.find(cityId);
        eosio_assert(iterator != cities.end(), "The city not found");

        auto thecity = cities.get(cityId);
        eosio_assert(thecity.owner != attacker, "You can't attack a city you own.");

        //Create asset
        //asset({amount}, string_to_symbol({precision}, {symbol}));
        asset attackPrice = asset(attack_value, string_to_symbol(4, "EOSC"));//thecity.defense
        
        // Do inline trasfer
        // action({permission_level}, {contract_deployer}, {contract_action}, {data_to_pass}).send();
        action(vector<permission_level>(), N(dota), N(transfer), make_tuple(attacker, _self, attackPrice, string(""))).send();

        uint64_t attackerPoints=attack_value;
        uint64_t defenderPoints=thecity.defense;
        // Execute action from another contract
        // action({permission_level}, {contract_deployer}, {contract_action}, {data_to_pass}).send();
        if( attackerPoints >= defenderPoints ){
            action(vector<permission_level>(), N(dota), N(addcity), make_tuple(attacker, 
                thecity.city_id,
                thecity.city_name,
                thecity.profit,
                thecity.defense,
                thecity.owner
            )).send();
        }
    }
}
