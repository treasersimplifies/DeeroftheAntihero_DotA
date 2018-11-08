# Dear of the Anti-hero (DotA)
This is a dapp of game. The title comes from an ancient Chinese idiom——群雄逐鹿( qun xiong zhu lu ), whos superficial meaning is a lots of ambitious warlords fighting to get The Dear. "The Dear" is a representative of power. In ancient times, power comes from territory and army. <p>
This game is about players compete with each other to get as much territory which is in form of a limited number of cities as they can in order to produce incomes(EOS/EOSC) and win the game.<p>

## How to use
```bash
# 0. Start the nodeos
nodeos -e -p eosio --plugin eosio::chain_api_plugin --plugin eosio::history_api_plugin
# 1. Create new wallet with the name "dota"
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
# 6. Create more accounts
cleos create account eosio storm EOS6mg1jYHnyWrXbMn8aqfbbg6cydjdBgTKwKB1bSSpHSQpitxMzZ EOS59w3S5worNr52DHGJ4Zu9HeDDwuRsUtm4ypHVHnkDQFduKhdhQ
# 7. Compile the contract
cd /DeeroftheAntiheroDIR/contracts/Players
eosio-cpp -o Players.wasm Players.cpp --abigen
# 8. Set contract
```


