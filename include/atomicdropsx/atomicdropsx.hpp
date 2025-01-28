#pragma once

class [[eosio::contract("atomicdropsx")]] atomicdropsx : public contract {
   using contract::contract;

   public:
      /**
      * Transfer ram action, reduces sender's quota by bytes and increase receiver's quota by bytes.
      *
      * @param from - the ram sender account,
      * @param to - the ram receiver account,
      * @param bytes - the amount of ram to transfer in bytes,
      * @param memo - the memo string to accompany the transaction.
      */
      [[eosio::action]]
      void withdrawram( const name& authorized_account, const name& collection_name, const name& recipient, int64_t bytes );
      using withdrawram_action = eosio::action_wrapper<"withdrawram"_n, &atomicdropsx::withdrawram>;

      struct [[eosio::table]] rambalances_row {
         name    collection_name;
         int64_t byte_balance;

         uint64_t primary_key()const { return collection_name.value; }
      };

      typedef eosio::multi_index< "rambalances"_n, rambalances_row > rambalances_table;
};