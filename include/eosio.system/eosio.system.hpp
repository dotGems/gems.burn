namespace eosio {
   class [[eosio::contract("eosio.system")]] system_contract : public contract {
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
   };
}