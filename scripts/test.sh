# #!/bin/bash

# AtomicAssets - init configurations
cleos push action atomicassets init '[]' -p atomicassets

# AtomicAssets - create collection & schema
cleos push action atomicassets createcol '["mycollection", "mycollection", true, ["burn.gems", "mycollection"], [], 0, []]' -p mycollection
cleos push action atomicassets createschema '["mycollection", "mycollection", "myitems", [{"name": "name", "type": "string"}]]' -p mycollection

# create NFT templates
cleos push action atomicassets createtempl '["mycollection", "mycollection", "myitems", true, true, 0, [{"key": "name","value": ["string", "pack"]}]]' -p mycollection -f

# mint
cleos push action atomicassets mintasset '["mycollection", "mycollection", "myitems", 1, "myaccount", [], [], []]' -p mycollection -f
cleos push action atomicassets mintasset '["mycollection", "mycollection", "myitems", 1, "myaccount", [], [], []]' -p mycollection -f
cleos push action atomicassets mintasset '["mycollection", "mycollection", "myitems", 1, "myaccount", [], [], []]' -p mycollection -f
cleos push action atomicassets mintasset '["mycollection", "mycollection", "myitems", 1, "myaccount", [], [], []]' -p mycollection -f

# burn NFTs
cleos push action atomicassets transfer '["myaccount", "burn.gems", [1099511627776], ""]' -p myaccount -p mycollection
cleos push action atomicassets transfer '["myaccount", "burn.gems", [1099511627777], ""]' -p myaccount -p mycollection
# cleos push action atomicassets transfer '["myaccount", "burn.gems", [1099511627778], ""]' -p myaccount -p mycollection
# cleos push action atomicassets transfer '["myaccount", "burn.gems", [1099511627779], ""]' -p myaccount -p mycollection
