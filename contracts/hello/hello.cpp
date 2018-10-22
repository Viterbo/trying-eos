#include <eosiolib/eosio.hpp>
#include <eosiolib/asset.hpp>

using namespace eosio;

CONTRACT hello : public eosio::contract {
     public:
        using contract::contract;
        ACTION hi( name user ) {
            require_auth( user );
            print( "Hello, ", name{user} );
            
        }

        asset get_balance( name token_contract_account, name owner, symbol_code sym_code ) {
            accounts my_accounts( "_self"_n, "_self"_n.value );
            const auto& ac = my_accounts.get( sym_code.raw() );
            return ac.balance;
        }

        struct [[eosio::table]] account {
            asset balance;
            uint64_t primary_key() const { return balance.symbol.code().raw(); }
        };

        typedef eosio::multi_index< "accounts"_n, account > accounts;
};

EOSIO_DISPATCH( hello, (hi) )
