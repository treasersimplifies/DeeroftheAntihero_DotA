#include "Players.hpp"

namespace DotA {

    [[eosio::action]]
    void Players::add(const account_name account, string& username) {
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
        print(" *** You have successfully ADD an new PLAYER in DotA! *** ");

    }

    [[eosio::action]]
    void Players::update(account_name account, int64_t porperty) {//, string& city
        require_auth(account);
        playerIndex players(_self, _self);
        auto iterator = players.find(account);
        eosio_assert(iterator != players.end(), "Address for account not found");

        players.modify(iterator, account, [&](auto& player) {
            player.porperty += porperty;
        });
        print("You have successfully UPDATE an PLAYER in DotA!\n");
    }

    [[eosio::action]]//**
    void Players::addtitle(const account_name account, title atitle){
        print("Inside addtitle...");
        require_auth(account);
        playerIndex players(_self, _self);
        auto iterator = players.find(account);
        eosio_assert(iterator != players.end(), "Address for account not found");

        players.modify(iterator, account, [&](auto& player) {
            player.titles_owned.push_back(title{
                atitle.title_id,
                atitle.name,
                atitle.num,
            });
        });
        print("You have successfully ADDTITLE for an PLAYER in DotA!");
    }

    [[eosio::action]]
    void Players::addcity(account_name account,city acity){
        require_auth(account);
        playerIndex players(_self, _self);
        auto iterator = players.find(account);
        eosio_assert(iterator != players.end(), "Address for account not found");

        players.modify(iterator, account, [&](auto& player) {
            player.cities_owned.push_back(city{
                acity.city_id,
                acity.city_name,
                acity.profit,
                acity.defense,
                acity.owner
            });
        });
        print("You have successfully ADDCITIY for an PLAYER in DotA!\n");
    }

    [[eosio::action]]
    void Players::removecity(account_name account,city acity){
        require_auth(account);
        playerIndex players(_self, _self);
        auto iterator = players.find(account);
        eosio_assert(iterator != players.end(), "Address for account not found");
        // How to implement remove city from a player ?
        auto currentPlayer = players.get(account);
        players.modify(iterator, account, [&](auto& player) {
            // auto targert = currentPlayer.cities_owned.find(acity);
            player.cities_owned.pop_back();
        });

        print("You have successfully REMOVECITIY for an PLAYER in DotA!\n");
    }

    [[eosio::action]]
    void Players::getplayer(const account_name account) {
        playerIndex players(_self, _self);
        auto iterator = players.find(account);//
        eosio_assert(iterator != players.end(), "Address for account not found");
        auto currentPlayer = players.get(account);
        
        print(" |Account_name(ID): ", currentPlayer.account_name);
        print(" |Username: ", currentPlayer.username.c_str());
        print(" |Porperty : ", currentPlayer.porperty);  
        if (currentPlayer.cities_owned.size() > 0) {
            print(" |Cities owned : ");
            for (uint32_t i = 0; i < currentPlayer.cities_owned.size(); i++) {
                print(currentPlayer.cities_owned.at(i).city_name.c_str(), " ");
            }
        } else {
            print(" |Cities owned : None ");
        }

        if (currentPlayer.titles_owned.size() > 0) {
            print(" |Titles owned : ");
            for (uint32_t i = 0; i < currentPlayer.titles_owned.size(); i++) {
                print(currentPlayer.titles_owned.at(i).name.c_str(), " ");
            }
        } else {
            print(" |Titles owned : None ");
        }
    } 

}



    // [[eosio::action]]
    // void Players::addsimcity(const account_name account, simplecity asimplecity){
    //     require_auth(account);
    //     playerIndex players(_self, _self);
    //     auto iterator = players.find(account);
    //     eosio_assert(iterator != players.end(), "Address for account not found");

    //     players.modify(iterator, account, [&](auto& player) {
    //         player.simplecities_owned.push_back(simplecity{
    //             asimplecity.city_id,
    //             asimplecity.city_name,
    //             asimplecity.profit,
    //             // asimplecity.defense
    //         });
    //     });
    //     print("You have successfully ADDSIMPLECITIY for an PLAYER in DotA!\n");
    // }