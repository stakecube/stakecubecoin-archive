// Copyright (c) 2014-2016 The Dash developers
// Copyright (c) 2016-2020 The PIVX developers
// Copyright (c) 2020 The StakeCubeCoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef SPORKID_H
#define SPORKID_H

/*
    Don't ever reuse these IDs for other sporks
    - This would result in old clients getting confused about which spork is for what
*/

enum SporkId : int32_t {
    SPORK_2_SWIFTTX                         = 10001,
    SPORK_3_SWIFTTX_BLOCK_FILTERING,
    SPORK_5_MAX_VALUE,
    SPORK_7_MASTERNODE_SCANNING,
    SPORK_8_MASTERNODE_PAYMENT_ENFORCEMENT,
    SPORK_9_MASTERNODE_BUDGET_ENFORCEMENT,
    SPORK_10_MASTERNODE_PAY_UPDATED_NODES,
    SPORK_11_ENABLE_SUPERBLOCKS,
    SPORK_12_NEW_PROTOCOL_ENFORCEMENT,
    SPORK_13_SEGWIT_ACTIVATION,
    SPORK_14_SEGWIT_ON_COINBASE,
    SPORK_15_CHOKE_CONTROL_MODE             = 10014,

    SPORK_INVALID                           = -1
};

// Default values
struct CSporkDef
{
    CSporkDef(): sporkId(SPORK_INVALID), defaultValue(0) {}
    CSporkDef(SporkId id, int64_t val, std::string n): sporkId(id), defaultValue(val), name(n) {}
    SporkId sporkId;
    int64_t defaultValue;
    std::string name;
};

#endif
