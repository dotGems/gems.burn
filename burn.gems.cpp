#include <eosio/eosio.hpp>

const eosio::name COLLECTION_NAME = "pomelo"_n;
const eosio::name REFUND_BYTES_FROM = "burn.gems"_n;
const int64_t REFUND_BYTES = 1024; // 1KB
const int64_t TEMPLATE_ID = 0;

#include "./burn.gems.hpp"
