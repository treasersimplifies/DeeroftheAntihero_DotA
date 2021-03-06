#include <eosiolib/eosio.hpp>
#include <eosiolib/print.hpp>
#include <string>
#include <stack>
#include <cstdlib>
#include <map>

namespace DotA {
    using namespace eosio;
    using std::string;

    class Citygroup : public contract {
        using contract::contract;

        public:

            Citygroup(account_name self):contract(self) {}
            [[eosio::action]]
            void hi(){
                string strNum;
                strNum.push_back('3');
                int64_t currNum1 = std::stoi(strNum.c_str()); //strtof(strNum.c_str(),nullptr);
                float currNum2 = string_to_name(strNum.c_str()); //  std::stof(strNum)   atof(strNum.c_str());
                print("currNum1=",currNum1," currNum2=",currNum2);
                float currNum3 = std::stof(strNum.c_str());
                print("currNum3=",currNum3);
            }

            [[eosio::action]]
            void inftopos(string infix, string & result);//InfixToPostfix
            [[eosio::action]]
            void poxcpu(string s, int64_t & result);//posfixCompute
            [[eosio::action]]
            void expcal(string s, int64_t & result);//float expressionCalculate

            struct battle{
                uint64_t battle_id;
                uint64_t attacker;
                uint64_t defender;
                uint64_t attacked_city_id;
                uint64_t attacker_ts;
                uint64_t attacker_te;
                uint64_t defender_ts;
                uint64_t defender_te;
                uint64_t attacker_totalpoint;
                uint64_t defender_totalpoint;
                uint64_t winner;
                uint64_t primary_key() const { return battle_id; }
            };
            typedef multi_index<N(battle), battle> battleIndex;

            [[eosio::action]]
            void getbattle(uint64_t battleId);

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
            void getcitybyid(uint64_t cityId);

            [[eosio::action]]
            void citylistall();//uint64_t cityId

            [[eosio::action]]
            void updatecity(account_name account, uint64_t cityId, uint64_t newowner, uint64_t newprofit, int64_t __defense);

            [[eosio::action]]
            void declarewar(account_name attacker, uint64_t cityId, uint64_t battleId);

            [[eosio::action]]
            void attack(account_name attacker, uint64_t battleId, uint64_t attack_value, string solution, uint64_t test);
            //void buy(account_name buyer, uint64_t productId);

            // [[eosio::action]]
            // void remove(account_name account, uint64_t productId);
    };

    EOSIO_ABI(Citygroup, (hi)(cityinit)(getcitybyid)(citylistall)(updatecity)(declarewar)(attack)(getbattle)(inftopos)(poxcpu)(expcal));
}

