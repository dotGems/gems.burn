#include <eosio/eosio.hpp>

using namespace eosio;

class [[eosio::contract("atomicassets")]] atomicassets : public eosio::contract {
public:
    using contract::contract;

    [[eosio::action]]
    void burnasset( const name asset_owner, const uint64_t asset_id );
    using burnasset_action = eosio::action_wrapper<"burnasset"_n, &atomicassets::burnasset>;
};

class [[eosio::contract("burn.gems")]] burn : public eosio::contract {
public:
    using contract::contract;

    /**
     * Notify contract when AtomicAssets NFT token transfer notifiers relay contract
     */
    [[eosio::on_notify("atomicassets::transfer")]]
    void on_nft_transfer( const name from, const name to, const std::vector<uint64_t> asset_ids, const std::string memo )
    {
        require_auth( from );
        atomicassets::burnasset_action burnasset( "atomicassets"_n, { get_self(), "active"_n });

        if ( is_account( "notify.gems"_n )) require_recipient( "notify.gems"_n );
        if ( to !=  get_self() ) return;

        for ( const uint64_t asset_id : asset_ids ) {
            burnasset.send( get_self(), asset_id );
        }
    }
};