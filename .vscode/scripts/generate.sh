echo "Current working directory(fileDirname) -" $1
cd $1
echo "fileBasenameNoExtension -" $2
# eosiocpp -g $2.abi $2.cpp
# eosio-cpp -o $2.wasm $2.cpp –abigen???
cd /Users/treasersmac/programming/EOS/Dapps/DearoftheAntihero/contracts/Players
eosio-cpp -o Players.wasm Players.cpp --abigen
# cd /Users/treasersmac/programming/EOS/Dapps/DearoftheAntihero/contracts/Marketplace
# eosio-cpp -o Marketplace.wasm Marketplace.cpp --abigen
echo "Successfully generated abi files :) "