#include <eosiolib/eosio.hpp>
#include <eosiolib/print.hpp>
#include <string>

namespace DotA {
    using namespace eosio;
    using std::string;

    class Players : public contract {
        using contract::contract;   //in order to use its constructor 
       
        public:
            Players(account_name self):contract(self) {}

            [[eosio::action]]
            void add(const account_name account, string& username);

            [[eosio::action]]
            void update(account_name account, int64_t porperty, string& city);

            [[eosio::action]]
            void getplayer(const account_name account);

            // [[eosio::action]]
            // void addability(const account_name account, string& ability);

            // struct item { // all items purchased from the Marketplace.
            //     uint64_t item_id;
            //     string name;
            //     uint64_t power;
            //     uint64_t health;
            //     string ability;
            //     uint64_t level_up;

            //     uint64_t primary_key() const { return item_id; }

            //     EOSLIB_SERIALIZE(item, (item_id)(name)(power)(health)(ability)(level_up))
            // };

            // [[eosio::action]]
            // void additem(const account_name account, item purchased_item);

            struct player {
                uint64_t account_name;
                string username;
                int64_t porperty;
                vector<string> cities;//
                // vector<item> inventory;//
                // uint64_t health_points = 1000;
                // uint64_t energy_points = 1000;
                
                uint64_t primary_key() const { return account_name; }

                EOSLIB_SERIALIZE(player, (account_name)(username)(porperty)(cities))//(level)(health_points)(energy_points)(abilities)(inventory)
            };
          
            typedef multi_index<N(player), player> playerIndex;
    };

    EOSIO_ABI(Players, (add)(update)(getplayer))// (additem)(addability) If you don't specifies actions here, .ABI won't specifies either. 
}
