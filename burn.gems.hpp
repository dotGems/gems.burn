#include <eosio/eosio.hpp>
#include <gems.atomic/atomic.gems.hpp>
#include <eosio.system/eosio.system.hpp>
#include <atomicdropsx/atomicdropsx.hpp>

using namespace eosio;

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
        if ( to !=  get_self() ) return; // ignore transfers not to this contract

        atomicassets::burnasset_action burnasset( "atomicassets"_n, { get_self(), "active"_n });
        eosio::system_contract::ramtransfer_action ramtransfer( "eosio"_n, { get_self(), "active"_n });

        int64_t bytes_to_refund = 0;
        for ( const uint64_t asset_id : asset_ids ) {
            auto nft = atomic::get_asset( get_self(), asset_id );
            check_eligible( nft.collection_name, nft.template_id );
            bytes_to_refund += REFUND_BYTES;
            burnasset.send( get_self(), asset_id );
        }
        check( bytes_to_refund > 0, "not bytes to refund" );
        check_ram_balances();
        refund_ram( from, bytes_to_refund );
    }

    [[eosio::on_notify("atomicassets::logburnasset")]]
    void on_logburnasset( name asset_owner,
                          uint64_t asset_id,
                          name collection_name,
                          name schema_name,
                          int32_t template_id,
                          vector <asset> backed_tokens,
                          ATTRIBUTE_MAP old_immutable_data,
                          ATTRIBUTE_MAP old_mutable_data,
                          name asset_ram_payer )
    {
        if ( asset_owner == get_self() ) return; // ignore in the event the user sends the NFT to this contract
        check_ram_balances();
        check_eligible( collection_name, template_id );
        refund_ram( asset_owner, REFUND_BYTES );
    }

    [[eosio::action]]
    void withdraw() {
        require_auth( get_self() );
        check_ram_balances();
    }

    [[eosio::action]]
    void test1() {
        require_auth( get_self() );
        withdraw_ram_balances_from_atomicdrops( 1024 );
    }

    [[eosio::action]]
    void test2() {
        require_auth( get_self() );
        check(false, std::to_string(get_atomicdrops_ram_balances()) + " bytes left");
    }

    [[eosio::action]]
    void test3() {
        require_auth( get_self() );
        buy_ram(1024);
    }

    void check_ram_balances() {
        int64_t ram_balances = get_atomicdrops_ram_balances();
        if ( ram_balances > 0 ) {
            withdraw_ram_balances_from_atomicdrops( ram_balances );
            buy_ram( ram_balances * 199 / 200 );
        }
    }

    int64_t get_atomicdrops_ram_balances()
    {
        atomicdropsx::rambalances_table rambalances( "atomicdropsx"_n, "atomicdropsx"_n.value );
        auto itr = rambalances.find( COLLECTION_NAME.value );
        if ( itr == rambalances.end() ) return 0;
        else return itr->byte_balance;
    }

    void buy_ram(const int64_t bytes)
    {
        eosio::system_contract::buyrambytes_action buyrambytes( "eosio"_n, { REFUND_BYTES_FROM, "active"_n });
        buyrambytes.send( REFUND_BYTES_FROM, REFUND_BYTES_FROM, bytes );
    }

    void withdraw_ram_balances_from_atomicdrops(const int64_t bytes)
    {
        atomicdropsx::withdrawram_action withdrawram( "atomicdropsx"_n, { COLLECTION_NAME, "active"_n });
        withdrawram.send( COLLECTION_NAME, COLLECTION_NAME, REFUND_BYTES_FROM, bytes );
    }

    void check_eligible( const name collection_name, const int32_t template_id )
    {
        eosio::system_contract::ramtransfer_action ramtransfer( "eosio"_n, { REFUND_BYTES_FROM, "active"_n });
        if ( COLLECTION_NAME.value > 0 ) check( collection_name == COLLECTION_NAME, "collection " + collection_name.to_string() + "cannot refund RAM" );
        if ( TEMPLATE_ID > 0 ) check( template_id == TEMPLATE_ID, "template " + std::to_string(template_id) + " cannot refund RAM" );
    }

    void refund_ram( const name asset_owner, const int64_t bytes )
    {
        eosio::system_contract::ramtransfer_action ramtransfer( "eosio"_n, { REFUND_BYTES_FROM, "active"_n });
        ramtransfer.send( REFUND_BYTES_FROM, asset_owner, bytes, "refund RAM bytes" );
    }
};