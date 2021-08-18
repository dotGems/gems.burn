#!/bin/bash

eosio-cpp burn.gems.cpp

# unlock wallet & deploy
cleos wallet unlock --password $(cat ~/eosio-wallet/.pass)
cleos set code burn.gems burn.gems.wasm
