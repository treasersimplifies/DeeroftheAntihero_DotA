# Dear of the Anti-hero (DotA)
This is a dapp of game. The title comes from an ancient Chinese idiom——群雄逐鹿( qun xiong zhu lu ), whos superficial meaning is a lots of ambitious warlords fighting to get The Dear. "The Dear" is a representative of power. In ancient times, power comes from territory and army. <p>
This game is about players compete with each other to get as much territory which is in form of a limited number of cities as they can in order to produce incomes(EOS/EOSC) and win the game.<p>

## How to use
```bash
# 0. Start the nodeos
nodeos -e -p eosio --plugin eosio::chain_api_plugin --plugin eosio::history_api_plugin --contracts-console --verbose-http-errors


# 1. Create new wallet with the name "dota"(or whatever name you like)
cleos wallet create -n dota —-to-console


# 2. Generate two pair of keys (use the command twice)
cleos create key
cleos create key


# 3. Import the generated private keys in the wallet(you need to specify the wallet at the end)
cleos wallet import -n dota 
cleos wallet import -n dota 


# 4. Add the private key of the "eosio" into your wallet
# Note: If you're receiving an Error 3090003: Provided keys, permissions, and delays do not satisfy declared authorizations
# you probably should add the private key of the "eosio" account to your wallet. 
cleos wallet import --private-key=5KQwrPbwdL6PhXujxW37FSSQZ1JiwsST4cqQzDeyXtP79zkvFD3 -n dota


# 5. Create the account using the public keys
cleos create account eosio invoker EOS5uwWCjvFRExqAHm2QgPp5yfRmY9VPzsikf4B9bXYpoktyP3rQx EOS5PRkgchBGS7MNms4JvSJzQf7mDjg1j2szikjaP6QoeLSQLZWhD
cleos create account eosio storm EOS6mg1jYHnyWrXbMn8aqfbbg6cydjdBgTKwKB1bSSpHSQpitxMzZ EOS59w3S5worNr52DHGJ4Zu9HeDDwuRsUtm4ypHVHnkDQFduKhdhQ


# 6. Create more testing accounts
cleos create account eosio testhero EOS5vtqE4i8j1tad58DWPgXDKavUc9Tn7jRZTz6b86xFkhqgFYo2N EOS6S8Snum6Z46swRFLRX5Bd99QsLZs3ioVeAYhULMNYkUYmRGfx6
cleos create account eosio sniper EOS5TCc6ZE7eamcnyAu54aAivizXxPjoFGBTdbBVL5s3HacRBcFVt EOS6uKkjWEJq3hvCWGPDa3Vex5WZ2iNQ3StR7zZSzfZ4faxUT6LCb
# create the root account for setting contracts
cleos create account eosio god EOS5hdugsVWNbBnU3v4EGE8ktL29gDkcrUKwX1Xdr7kv2ZHsbxD9F EOS6ocAHgBf6dbQTDsCBp28Emx7rBqiGBkVs4g4s8ohTLH4zere42
cleos create account eosio dota EOS5ust6g8US4EPX21FUJENYXMYbGLXqfNdM4spED2ot9fG46Xd1C EOS8iPHfjgbAGi3tAQ8GvmRSBsbBFawtEJtp4tbcgffwYWQXTWZy6
cleos create account eosio fy EOS4v2oX9ZbF4ninG6NieWUpcXrvYKaS1tNDFQFEZ6Dy8DUXFYkPu EOS56DVgR7vMEyuqkx44h53DmDDmRjEg7wsVBBPkUYY1Lvfxn4Wes


# 7. Compile the Players/Citygroup contract
cd /DeeroftheAntiheroDIR/contracts/Players
eosio-cpp -o Players.wasm Players.cpp --abigen
cd /DeeroftheAntiheroDIR/contracts/Citygroup
eosio-cpp -o Citygroup.wasm Citygroup.cpp --abigen

# 8. Deploy the Players contract
cleos set contract dota /Users/treasersmac/programming/EOS/Dapps/DeeroftheAntihero/contracts/Players -p dota@active


# 9. Test the Players contract
# test Player::add action
cleos push action dota add '["testhero","testy"]' -p testhero@active
cleos push action dota getplayer '["testhero"]' -p testhero@active
cleos push action dota add '["testhero","testy"]' -p testhero@active # assert error test
cleos push action dota add '["sniper","snippy"]' -p sniper@active
cleos push action dota getplayer '["sniper"]' -p sniper@active

cleos push action dota add '["invoker","kaer"]' -p invoker@active
cleos push action dota getplayer '["invoker"]' -p invoker@active --json

# test Player::update action
cleos push action dota update '["testhero",100]' -p testhero@active
cleos push action dota getplayer '["testhero"]' -p testhero@active

cleos push action dota update '["testhero",-50]' -p testhero@active
cleos push action dota getplayer '["testhero"]' -p testhero@active

cleos push action dota update '["sniper",50]' -p sniper@active
cleos push action dota getplayer '["sniper"]' -p sniper@active

cleos push action dota update '["sniper",-100]' -p sniper@active
cleos push action dota getplayer '["sniper"]' -p sniper@active

# test Player::addtitle action : Succeed !
cleos push action dota addtitle '{"account":"testhero","atitle":{"title_id":1,"name":"GoldCity","num":10}}' -p testhero@active
cleos push action dota getplayer '["testhero"]' -p testhero@active
cleos push action dota addtitle '{"account":"testhero","atitle":{"title_id":2,"name":"hhh","num":9}}' -p testhero@active
cleos push action dota getplayer '["testhero"]' -p testhero@active


# 10. Deploy the Citygroup contract
cleos set contract fy /Users/treasersmac/programming/EOS/Dapps/DeeroftheAntihero/contracts/Citygroup -p fy@active


# 10. Test the Citygroup contract
# In order to test it, first list all players to make clear their account_names
# Player::playergetall action 
cleos push action dota playergetall '["testhero"]' -p testhero@active

# test Citygroup::cityinit action
cleos push action fy cityinit '["testhero"]' -p testhero@active # Transaction should have at least one required authority

# test Citygroup::getbyid action
cleos push action fy getcitybyid '[1]' -p testhero@active
cleos push action fy getcitybyid '[2]' -p testhero@active

# test Citygroup::citylistall action
cleos push action fy citylistall '[]' -p testhero@active

# test Citygroup::declarewar action
cleos push action fy declarewar '["testhero",1,1]' -p testhero@active
cleos push action fy declarewar '["testhero",1,2]' -p testhero@active

# test Citygroup::getbattle action
cleos push action fy getbattle '[1]' -p testhero@active

# test Citygroup::attack action
cleos push action fy attack '["testhero",1,10,"(3/3+2)*8",1]' -p testhero@active

```



