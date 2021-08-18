#!/bin/bash

# unlock wallet
cleos wallet unlock --password $(cat ~/eosio-wallet/.pass)

# create accounts
cleos create account eosio burn.gems EOS6MRyAjQq8ud7hVNYcfnVPJqcVpscN5So8BhtHuGYqET5GDW5CV
cleos create account eosio myaccount EOS6MRyAjQq8ud7hVNYcfnVPJqcVpscN5So8BhtHuGYqET5GDW5CV
cleos create account eosio atomicassets EOS6MRyAjQq8ud7hVNYcfnVPJqcVpscN5So8BhtHuGYqET5GDW5CV
cleos create account eosio mycollection EOS6MRyAjQq8ud7hVNYcfnVPJqcVpscN5So8BhtHuGYqET5GDW5CV

# deploy
cleos set code burn.gems burn.gems.wasm
cleos set contract atomicassets include/atomicassets atomicassets.wasm atomicassets.abi

# permission
cleos set account permission burn.gems active --add-code
cleos set account permission atomicassets active --add-code

# used only for local testing
cleos set account permission mycollection active burn.gems --add-code