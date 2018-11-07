#include "Players.hpp"

namespace DotA {
    [[eosio::action]]
    void Players::add(const account_name account, string& username) {
        print("Inside ADD action yahoooooo!\n");
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
        print("You have successfully ADD an new account in DotA!\n");

    }

    [[eosio::action]]
    void Players::update(account_name account, int64_t porperty) {//, string& city
        print("Inside UPDATE action yahoooooo!\n");
        require_auth(account);

        playerIndex players(_self, _self);

        auto iterator = players.find(account);
        eosio_assert(iterator != players.end(), "Address for account not found");

        players.modify(iterator, account, [&](auto& player) {
            //player.cities.push_back(city);
            player.porperty +=porperty;
        });
        print("You have successfully UPDATE an account in DotA!\n");
    }

    [[eosio::action]]
    void Players::addcities(account_name account, string& city){
        print("Inside ADDCITIES action yahoooooo!\n");
        require_auth(account);

        playerIndex players(_self, _self);

        auto iterator = players.find(account);
        eosio_assert(iterator != players.end(), "Address for account not found");

        players.modify(iterator, account, [&](auto& player) {
            player.cities.push_back(city);
            //player.porperty +=porperty;
        });
        print("You have successfully ADDCITIES for an account in DotA!\n");
    }

    [[eosio::action]]
    void Players::removecities(account_name account, string& city){
        print("Inside ADDCITIES action yahoooooo!\n");
        require_auth(account);

        playerIndex players(_self, _self);

        auto iterator = players.find(account);
        eosio_assert(iterator != players.end(), "Address for account not found");

        players.modify(iterator, account, [&](auto& player) {
            player.cities.pop_back();
        });
        print("You have successfully ADDCITIES for an account in DotA!\n");
    }

    [[eosio::action]]
    void Players::getplayer(const account_name account) {
        print("Inside getplayer action yahoooooo!\n");
        playerIndex players(_self, _self);

        auto iterator = players.find(account);
        eosio_assert(iterator != players.end(), "Address for account not found");
        auto currentPlayer = players.get(account);

        print("Username: ", currentPlayer.username.c_str());
        print("-Porperty: ", currentPlayer.porperty);
                
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

