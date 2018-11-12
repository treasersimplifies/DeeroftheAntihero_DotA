#include "Players.hpp"

namespace DotA {
    // using namespace eosio;
    // using std::string;

    [[eosio::action]]
    void Players::add(const account_name account, string& username) {
        print("Inside ADD action of Players!");
        // std::cout << "Inside add action yahoooooo!\n" ;
        require_auth(account);

        playerIndex players(_self, _self);

        auto iterator = players.find(account);
        eosio_assert(iterator == players.end(), "Address for account already exists");

        players.emplace(account, [&](auto& player) {
            player.account_name = account;
            player.username = username;
            player.porperty = 0;
            // player.cities.push_back("NULL");
        });
        print(" You have successfully ADD an new PLAYER in DotA! ");

    }

    [[eosio::action]]
    void Players::update(account_name account, int64_t porperty) {//, string& city
        // print("Inside UPDATE action of Players!\n");
        require_auth(account);

        playerIndex players(_self, _self);

        auto iterator = players.find(account);
        eosio_assert(iterator != players.end(), "Address for account not found");

        players.modify(iterator, account, [&](auto& player) {
            //player.cities.push_back(city);
            player.porperty +=porperty;
        });
        print("You have successfully UPDATE an PLAYER in DotA!\n");
    }

    // [[eosio::action]]//**
    // void Players::attackcity(const account_name account,city acity) {//string& cityname
    //     // print("Inside ADDCITIES action of player!");
    //     require_auth(account);
    //     playerIndex players(_self, _self);
    //     auto iterator = players.find(account);
    //     eosio_assert(iterator != players.end(), "Address for account not found");
         

    // }

    [[eosio::action]]
    void Players::addcities(account_name account,city acity){
        // print("Inside ADDCITIES action yahoooooo!");
        require_auth(account);
        playerIndex players(_self, _self);
        auto iterator = players.find(account);
        eosio_assert(iterator != players.end(), "Address for account not found");

        players.modify(iterator, account, [&](auto& player) {
            player.cities.push_back(city{
                acity.city_id,
                acity.cityname,
                acity.profit,
                acity.defense
            });
            //player.porperty +=porperty;
        });
        print("You have successfully ADDCITIES for an PLAYER in DotA!\n");
    }

    [[eosio::action]]
    void Players::removecities(account_name account,city acity){
        print("Inside ADDCITIES action yahoooooo!\n");
        require_auth(account);

        playerIndex players(_self, _self);

        auto iterator = players.find(account);
        eosio_assert(iterator != players.end(), "Address for account not found");

        players.modify(iterator, account, [&](auto& player) {
            player.cities.pop_back();
        });
        print("You have successfully ADDCITIES for an PLAYERs in DotA!\n");
    }

    [[eosio::action]]
    void Players::getplayer(const account_name account) {
        print("Inside GETPLAYER action!");
        playerIndex players(_self, _self);

        auto iterator = players.find(account);
        eosio_assert(iterator != players.end(), "Address for account not found");
        auto currentPlayer = players.get(account);

        print(" Username: ", currentPlayer.username.c_str());
        print(" Porperty : ", currentPlayer.porperty);
        print(" ");    
        if (currentPlayer.cities.size() > 0) {
            print(" Cities owned : ");
            for (uint32_t i = 0; i < currentPlayer.cities.size(); i++) {
                print(currentPlayer.cities.at(i).city_name.c_str(), " ");
            }
            print("  ");
        } else {
            print(" Cities owned : None ");
        }
    } 

}

