#include <eosiolib/asset.hpp>
#include <eosiolib/eosio.hpp>

using namespace eosio;
using namespace std;

CONTRACT ipfs : public eosio::contract {

    public:
        using contract::contract;
        
    ACTION savehash(string text_hash, string image_hash) {
        ipfs_table _ipfsdata(_self, _self.value);
        // cleos push action ipfs.app savehash '["QmPnnvFkvSCmPvMdMtSNbXrFWQX5XYc4YkcVU4cujyyH8Z",""]' -p dummy
        // cleos push action ipfs.app savehash '["","QmPnnvFkvSCmPvMdMtSNbXrFWQX5XYc4YkcVU4cujyyH8Z"]' -p dummy
        // cleos get table ipfs.app ipfs.app ipfsdata
        
        auto iter = _ipfsdata.find(0);
        if (iter != _ipfsdata.end()) {
            _ipfsdata.modify(iter, _self, [&](auto& row) {
                if(text_hash != "") {
                    row.text_hash = text_hash;
                }
                if(image_hash != "") {
                    row.image_hash = image_hash;
                }
            });
        } else {
            _ipfsdata.emplace(_self, [&] (auto& row) {
                row.id = _ipfsdata.available_primary_key();
                row.text_hash = text_hash;
                row.image_hash = image_hash;
            });
        }
    }
    
    ACTION delhash(uint64_t id) {
        // cleos push action ipfs.app delhash '[0]' -p dummy
        ipfs_table _ipfsdata(_self, _self.value);
        auto iter = _ipfsdata.find(id);
        _ipfsdata.erase(iter);
    }
    

private:
    
    TABLE ipfsdata {
        uint64_t id;
        string text_hash;
        string image_hash;
        uint64_t primary_key() const { return id; }
        EOSLIB_SERIALIZE(ipfsdata, (id)(text_hash)(image_hash));
    };

    typedef eosio::multi_index< "ipfsdata"_n, ipfsdata > ipfs_table;
};

EOSIO_DISPATCH( ipfs, (savehash)(delhash) );
