#include "Citygroup.hpp" 

namespace DotA {
    using namespace eosio;
    using std::string;

    [[eosio::action]]
    void Cities::add(uint64_t deer, string city_name, string owner_username, int64_t initial_defense) {
        print("Inside ADD action yahoooooo!\n");
        // std::cout << "Inside add action yahoooooo!\n" ;

        cityIndex Cities(_self, _self);

        auto iterator = Cities.find(deer);
        eosio_assert(iterator == Cities.end(), "Address for CITY already exists");

        Cities.emplace(deer, [&](auto& city) {
            city.city_name = city_name;
            city.owner_username = owner_username;
            city.defense = initial_defense;
        });
        print("You have successfully ADD an new CITY in DotA!\n");

    }

    [[eosio::action]]
    void Cities::update(account_name account, int64_t porperty) {//, string& city
        print("Inside UPDATE action yahoooooo!\n");
        require_auth(account);

        playerIndex Cities(_self, _self);

        auto iterator = Cities.find(account);
        eosio_assert(iterator != Cities.end(), "Address for account not found");

        Cities.modify(iterator, account, [&](auto& player) {
            //player.cities.push_back(city);
            player.porperty +=porperty;
        });
        print("You have successfully UPDATE an account in DotA!\n");
    }

    [[eosio::action]]
    void Cities::addcities(account_name account, string& city){
        print("Inside ADDCITIES action yahoooooo!\n");
        require_auth(account);

        playerIndex Cities(_self, _self);

        auto iterator = Cities.find(account);
        eosio_assert(iterator != Cities.end(), "Address for account not found");

        Cities.modify(iterator, account, [&](auto& player) {
            player.cities.push_back(city);
            //player.porperty +=porperty;
        });
        print("You have successfully ADDCITIES for an account in DotA!\n");
    }

    [[eosio::action]]
    void Cities::removecities(account_name account, string& city){
        print("Inside ADDCITIES action yahoooooo!\n");
        require_auth(account);

        playerIndex Cities(_self, _self);

        auto iterator = Cities.find(account);
        eosio_assert(iterator != Cities.end(), "Address for account not found");

        Cities.modify(iterator, account, [&](auto& player) {
            player.cities.pop_back();
        });
        print("You have successfully ADDCITIES for an account in DotA!\n");
    }

    [[eosio::action]]
    void Cities::getplayer(const account_name account) {
        print("Inside getplayer action yahoooooo!\n");
        playerIndex Cities(_self, _self);

        auto iterator = Cities.find(account);
        eosio_assert(iterator != Cities.end(), "Address for account not found");
        auto currentPlayer = Cities.get(account);

        print("Username: ", currentPlayer.username.c_str());
        print("-Porperty : ", currentPlayer.porperty);
        print("\n");    
        if (currentPlayer.cities.size() > 0) {
            print("-Cities owned : ");
            for (uint32_t i = 0; i < currentPlayer.cities.size(); i++) {
                print(currentPlayer.cities.at(i).c_str(), " ");
            }
            print("\n");
        } else {
            print("-Cities owned : None \n");
        }
    } 

}

