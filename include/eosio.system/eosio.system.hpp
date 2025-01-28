#pragma once

namespace eosio {
   class [[eosio::contract("eosio.system")]] system_contract : public contract {
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
        void ramtransfer( const name& from, const name& to, int64_t bytes, const std::string& memo );
        using ramtransfer_action = eosio::action_wrapper<"ramtransfer"_n, &system_contract::ramtransfer>;

         /**
          * Buy ram action, increases receiver's ram quota based upon current price and quantity of
          * tokens provided. An inline transfer from receiver to system contract of
          * tokens will be executed.
          *
          * @param payer - the ram buyer,
          * @param receiver - the ram receiver,
          * @param quant - the quantity of tokens to buy ram with.
          */
         [[eosio::action]]
         void buyram( const name& payer, const name& receiver, const asset& quant );
         using buyram_action = eosio::action_wrapper<"buyram"_n, &system_contract::buyram>;

         /**
          * Buy a specific amount of ram bytes action. Increases receiver's ram in quantity of bytes provided.
          * An inline transfer from receiver to system contract of tokens will be executed.
          *
          * @param payer - the ram buyer,
          * @param receiver - the ram receiver,
          * @param bytes - the quantity of ram to buy specified in bytes.
          */
         [[eosio::action]]
         void buyrambytes( const name& payer, const name& receiver, uint32_t bytes );
         using buyrambytes_action = eosio::action_wrapper<"buyrambytes"_n, &system_contract::buyrambytes>;
   };
}