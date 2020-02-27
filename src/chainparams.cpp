// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Bitcoin developers
// Copyright (c) 2014-2015 The Dash developers
// Copyright (c) 2015-2017 The PIVX developers
// Copyright (c) 2018-2020 StakeCubeCore developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "chainparams.h"

#include "random.h"
#include "util.h"
#include "utilstrencodings.h"

#include <assert.h>

#include <boost/assign/list_of.hpp>

using namespace std;
using namespace boost::assign;

struct SeedSpec6 {
    uint8_t addr[16];
    uint16_t port;
};

#include "chainparamsseeds.h"

/**
 * Main network
 */

//! Convert the pnSeeds6 array into usable address objects.
static void convertSeed6(std::vector<CAddress>& vSeedsOut, const SeedSpec6* data, unsigned int count)
{
    // It'll only connect to one or two seed nodes because once it connects,
    // it'll get a pile of addresses with newer timestamps.
    // Seed nodes are given a random 'last seen time' of between one and two
    // weeks ago.
    const int64_t nOneWeek = 7 * 24 * 60 * 60;
    for (unsigned int i = 0; i < count; i++) {
        struct in6_addr ip;
        memcpy(&ip, data[i].addr, sizeof(ip));
        CAddress addr(CService(ip, data[i].port));
        addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
        vSeedsOut.push_back(addr);
    }
}

//   What makes a good checkpoint block?
// + Is surrounded by blocks with reasonable timestamps
//   (no blocks before with a timestamp after, none after with
//    timestamp before)
// + Contains no strange transactions
static Checkpoints::MapCheckpoints mapCheckpoints =
    boost::assign::map_list_of
    (0,      uint256("0x000005bc17744254b063fe3ee2fd568f89bd9d88c2f16fcba1c74c05625ae442"))
    (25000,  uint256("0xcb04ab37cd5ae6f7aa352dfd8e4bcba46dc2af3ef9f0615ec39ab6177ed9b429"))
    (75000,  uint256("0x1cb3eb6d01fa3ee611c284f16e1f7a922e5c2c151da3e89b9d703606bf00500e"))
    (150000, uint256("0xe4009f6d69e6f18ee295fd41f2e285d6af52b245f75927e9444f242e0e603467"))
    (200000, uint256("0x63e4ced0469981f3537184abe52c9ebafcab9e70e1d6f586fe4ee814010a753c"))
    (250000, uint256("0xe4bdb74e76eb0da2870cc5420a9bc9605e54244727528a7afbfb30ff087edd5e"))
    (300000, uint256("0xcce450e481798ffaa2505c2ae03a87cf4b720a7f9cab5d549d974e443bfb3c22"))
    (310000, uint256("0xe294f3bb879a01df241503df7d0ed7ecbf2d69b46687e9ebac0e07242bc61be4"))
    (320000, uint256("0x6547c1fc6752c0efcaa2e08dc9214bf5453ba9c4741298cf6174e04cd7eca943"))
    (325000, uint256("0xff9db74a03e6df4785f4b6d43b5489cd22ab72fb02251dfe52622f763479bfb0"))
    (326000, uint256("0x7a4b03c4cb7b3fc1c4760c94984215c614e7f9c313dbc9a6c4c1784b29b9c69c"))
    (327000, uint256("0xe7c4e47216fbd465a0b6ce4f5cae6f679e679e8d4cfe27bf338802b5b706acd6"))
    (328000, uint256("0x6f1085019f5ee9b927d6e983692fd6c5df7d23b20d908b0f6d5c0edf34af094d"))
    (329000, uint256("0x81df3190210377d47fa39202238ad0d75206a1259b6df3096843de5424439c9c"))
    (330000, uint256("0x96ac1323d22619493c1e4ec70dc75efda73f0e906cb4a3cb100d3074ef4e81a2"))
    (335278, uint256("0xcd523768dd5a59e479d8cf0c5292b8ff21002045d5e3b672ebb9a91dfe3f4cb0"))
    (335279, uint256("0x028d917673a6f7969d1a93c299440d9e2243e21829f49c33293979158fe0e91e"))
    (335280, uint256("0x8535d3c8af8075b8872111be1d7bff122816614d14b6a81c7059f713bb39b303"))
    (335281, uint256("0x81c2ecd0e7ece2094dbc0edc966e04cde8ddc5d5b0b96db823d4aba2fe604394"))
    (335282, uint256("0x499a502dd24198630a1d795acb0b9cd3b99c309f64d0e854f02ed0f2b05f9e4b"));

static const Checkpoints::CCheckpointData data = {
    &mapCheckpoints,
    1582840209,
    808186,
    1
};

static Checkpoints::MapCheckpoints mapCheckpointsTestnet =
    boost::assign::map_list_of(0, uint256("0x001"));
static const Checkpoints::CCheckpointData dataTestnet = {
    &mapCheckpointsTestnet,
    1524873600,
    0,
    250};

static Checkpoints::MapCheckpoints mapCheckpointsRegtest =
    boost::assign::map_list_of(0, uint256("0x001"));
static const Checkpoints::CCheckpointData dataRegtest = {
    &mapCheckpointsRegtest,
    1524873600,
    0,
    100};

// CBlock(hash=000005bc17744254b063fe3ee2fd568f89bd9d88c2f16fcba1c74c05625ae442, ver=1, hashPrevBlock=0000000000000000000000000000000000000000000000000000000000000000, hashMerkleRoot=81791231fefc74d7924ae1c1ff9e384f77285885f4a7a7c32570942834efd5d2, nTime=1538198000, nBits=1e0ffff0, nNonce=721427, vtx=1)
//  CTransaction(hash=81791231fe, ver=1, vin.size=1, vout.size=1, nLockTime=0)
//    CTxIn(COutPoint(0000000000000000000000000000000000000000000000000000000000000000, 4294967295), coinbase 04ffff001d0104147374616b65637562654d4e203239303932303138)
//    CTxOut(nValue=0.00000000, scriptPubKey=0457c56ed69a1f42398804504fcab8)

class CMainParams : public CChainParams
{
public:
    CMainParams()
    {
        networkID = CBaseChainParams::MAIN;
        strNetworkID = "main";
        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 4-byte int at any alignment.
         */
        pchMessageStart[0] = 0x05;
        pchMessageStart[1] = 0x74;
        pchMessageStart[2] = 0x43;
        pchMessageStart[3] = 0x50;
        vAlertPubKey = ParseHex("");
        nDefaultPort = 40000;
        bnProofOfWorkLimit = ~uint256(0) >> 20;
        nSubsidyHalvingInterval = 210000;
        nMaxReorganizationDepth = 100;
        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;
        nMinerThreads = 0;
        nTargetTimespan = 20 * 60;
        nTargetSpacing = 2 * 60;
        nLastPOWBlock = 200;
        nMaturity = 25;
        nMasternodeCountDrift = 20;
        nMasternodeCollateralLimit = 1000;
        nModifierUpdateBlock = 500;
        nMaxMoneyOut = 20000000 * COIN;

        const char* pszTimestamp = "stakecubeMN 29092018";
        CMutableTransaction txNew;
        txNew.vin.resize(1);
        txNew.vout.resize(1);
        txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        txNew.vout[0].nValue = 0 * COIN;
        txNew.vout[0].scriptPubKey = CScript() << ParseHex("0457c56ed69a1f42398804504fcab82f430cc864c8fc8cd25b76e141d12c13012ee9d500e11f84d5f75f5c669e88ca196142ddb7406d3635d840fa5e9d2a6bb100") << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime = 1538198000;
        genesis.nBits = 0x1e0ffff0;
        genesis.nNonce = 721427;

        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("000005bc17744254b063fe3ee2fd568f89bd9d88c2f16fcba1c74c05625ae442"));
        assert(genesis.hashMerkleRoot == uint256("81791231fefc74d7924ae1c1ff9e384f77285885f4a7a7c32570942834efd5d2"));

	vSeeds.push_back(CDNSSeedData("0", "95.179.165.19"));
	vSeeds.push_back(CDNSSeedData("1", "2001:19f0:6c01:22ee:5400:02ff:fe0a:f0bb"));
	vSeeds.push_back(CDNSSeedData("2", "209.250.224.166"));
	vSeeds.push_back(CDNSSeedData("3", "2001:19f0:7400:8249:5400:02ff:fe0a:f089"));
	vSeeds.push_back(CDNSSeedData("4", "108.61.212.198"));
	vSeeds.push_back(CDNSSeedData("5", "2001:19f0:5801:10b6:5400:02ff:fe0a:f090"));
	vSeeds.push_back(CDNSSeedData("6", "78.141.211.79"));
	vSeeds.push_back(CDNSSeedData("7", "2001:19f0:5001:3ad0:5400:02ff:fe0a:f09b"));
	vSeeds.push_back(CDNSSeedData("8", "95.179.209.111"));
	vSeeds.push_back(CDNSSeedData("9", "2001:19f0:6801:171a:5400:02ff:fe0a:f0a9"));
    vSeeds.push_back(CDNSSeedData("10", "144.202.60.226"));
	vSeeds.push_back(CDNSSeedData("11", "2001:19f0:5c01:b60:5400:02ff:fe8e:495f"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 125);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 117);
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 253);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x02)(0x2D)(0x25)(0x33).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x02)(0x21)(0x31)(0x2B).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x00)(0x77).convert_to_container<std::vector<unsigned char> >();

	convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));

        fRequireRPCPassword = true;
        fMiningRequiresPeers = true;
        fAllowMinDifficultyBlocks = false;
        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;
        fSkipProofOfWorkCheck = true;
        fTestnetToBeDeprecatedFieldRPC = false;
        fHeadersFirstSyncingActive = false;

        nPoolMaxTransactions = 3;
        strSporkKey = "02e52ae838842b7a34468639ca17a2e3883f10f30095ee31e19984e5590149fbcc";
        strObfuscationPoolDummyAddress = "Lo3fnibtjwvqYE1T7Lce5uYbdt3pf6PKUu";
		
        nStartMasternodePayments = genesis.nTime + 5400;
    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return data;
    }
};
static CMainParams mainParams;

/**
 * Testnet (v3)
 */
class CTestNetParams : public CMainParams
{
public:
    CTestNetParams()
    {
        networkID = CBaseChainParams::TESTNET;
        strNetworkID = "test";
        pchMessageStart[0] = 0x41;
        pchMessageStart[1] = 0x4d;
        pchMessageStart[2] = 0x5e;
        pchMessageStart[3] = 0x78;
        vAlertPubKey = ParseHex("");
        nDefaultPort = 39795;
        nEnforceBlockUpgradeMajority = 51;
        nRejectBlockOutdatedMajority = 75;
        nToCheckBlockUpgradeMajority = 100;
        nMinerThreads = 0;
        nTargetTimespan = 1 * 60; // StakeCubeCore: 1 day
        nTargetSpacing = 1 * 60;  // StakeCubeCore: 1 minute
        nLastPOWBlock = 50;
        nMaturity = 5;
        nMasternodeCountDrift = 4;
        nMasternodeCollateralLimit = 1000;
        nModifierUpdateBlock = 51197; //approx Mon, 17 Apr 2017 04:00:00 GMT
        nMaxMoneyOut = 43199500 * COIN;

        //! Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nTime = 1524873600;
        genesis.nNonce = 2394236;

        hashGenesisBlock = genesis.GetHash();

        vFixedSeeds.clear();
        vSeeds.clear();

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 139); // Testnet stakecube addresses start with 'x' or 'y'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 19);  // Testnet stakecube script addresses start with '8' or '9'
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 239);     // Testnet private keys start with '9' or 'c' (Bitcoin defaults)
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x3a)(0x80)(0x61)(0xa0).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x3a)(0x80)(0x58)(0x37).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x00)(0x01).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_test, ARRAYLEN(pnSeed6_test));

        fRequireRPCPassword = true;
        fMiningRequiresPeers = false;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = false;
        fRequireStandard = false;
        fMineBlocksOnDemand = false;
        fSkipProofOfWorkCheck = true;
        fTestnetToBeDeprecatedFieldRPC = true;

        nPoolMaxTransactions = 2;
        strSporkKey = "02e52ae838842b7a34468639ca17a2e3883f10f30095ee31e19984e5590149fbcc";
        strObfuscationPoolDummyAddress = "xxVKdbxVogrXrPLMo2qEEyCm1GRv2KZCLy";
        nStartMasternodePayments = 1524873600; //Fri, 09 Jan 2015 21:05:58 GMT
    }
    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataTestnet;
    }
};
static CTestNetParams testNetParams;

/**
 * Regression test
 */
class CRegTestParams : public CTestNetParams
{
public:
    CRegTestParams()
    {
        networkID = CBaseChainParams::REGTEST;
        strNetworkID = "regtest";
        strNetworkID = "regtest";
        pchMessageStart[0] = 0x2d;
        pchMessageStart[1] = 0x53;
        pchMessageStart[2] = 0x6f;
        pchMessageStart[3] = 0x40;
        nSubsidyHalvingInterval = 150;
        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;
        nMinerThreads = 1;
        nTargetTimespan = 24 * 60 * 60; // StakeCubeCore: 1 day
        nTargetSpacing = 1 * 60;        // StakeCubeCore: 1 minutes
        bnProofOfWorkLimit = ~uint256(0) >> 1;
        genesis.nTime = 1524873600;
        genesis.nBits = 0x207fffff;
        genesis.nNonce = 906460;

        hashGenesisBlock = genesis.GetHash();
        nDefaultPort = 39793;

        vFixedSeeds.clear(); //! Testnet mode doesn't have any fixed seeds.
        vSeeds.clear();      //! Testnet mode doesn't have any DNS seeds.

        fRequireRPCPassword = false;
        fMiningRequiresPeers = false;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = true;
        fRequireStandard = false;
        fMineBlocksOnDemand = true;
        fTestnetToBeDeprecatedFieldRPC = false;
    }
    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataRegtest;
    }
};
static CRegTestParams regTestParams;

/**
 * Unit test
 */
class CUnitTestParams : public CMainParams, public CModifiableParams
{
public:
    CUnitTestParams()
    {
        networkID = CBaseChainParams::UNITTEST;
        strNetworkID = "unittest";
        nDefaultPort = 39791;
        vFixedSeeds.clear(); //! Unit test mode doesn't have any fixed seeds.
        vSeeds.clear();      //! Unit test mode doesn't have any DNS seeds.

        fRequireRPCPassword = false;
        fMiningRequiresPeers = false;
        fDefaultConsistencyChecks = true;
        fAllowMinDifficultyBlocks = false;
        fMineBlocksOnDemand = true;
    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        // UnitTest share the same checkpoints as MAIN
        return data;
    }

    //! Published setters to allow changing values in unit test cases
    virtual void setSubsidyHalvingInterval(int anSubsidyHalvingInterval) { nSubsidyHalvingInterval = anSubsidyHalvingInterval; }
    virtual void setEnforceBlockUpgradeMajority(int anEnforceBlockUpgradeMajority) { nEnforceBlockUpgradeMajority = anEnforceBlockUpgradeMajority; }
    virtual void setRejectBlockOutdatedMajority(int anRejectBlockOutdatedMajority) { nRejectBlockOutdatedMajority = anRejectBlockOutdatedMajority; }
    virtual void setToCheckBlockUpgradeMajority(int anToCheckBlockUpgradeMajority) { nToCheckBlockUpgradeMajority = anToCheckBlockUpgradeMajority; }
    virtual void setDefaultConsistencyChecks(bool afDefaultConsistencyChecks) { fDefaultConsistencyChecks = afDefaultConsistencyChecks; }
    virtual void setAllowMinDifficultyBlocks(bool afAllowMinDifficultyBlocks) { fAllowMinDifficultyBlocks = afAllowMinDifficultyBlocks; }
    virtual void setSkipProofOfWorkCheck(bool afSkipProofOfWorkCheck) { fSkipProofOfWorkCheck = afSkipProofOfWorkCheck; }
};
static CUnitTestParams unitTestParams;


static CChainParams* pCurrentParams = 0;

CModifiableParams* ModifiableParams()
{
    assert(pCurrentParams);
    assert(pCurrentParams == &unitTestParams);
    return (CModifiableParams*)&unitTestParams;
}

const CChainParams& Params()
{
    assert(pCurrentParams);
    return *pCurrentParams;
}

CChainParams& Params(CBaseChainParams::Network network)
{
    switch (network) {
    case CBaseChainParams::MAIN:
        return mainParams;
    case CBaseChainParams::TESTNET:
        return testNetParams;
    case CBaseChainParams::REGTEST:
        return regTestParams;
    case CBaseChainParams::UNITTEST:
        return unitTestParams;
    default:
        assert(false && "Unimplemented network");
        return mainParams;
    }
}

void SelectParams(CBaseChainParams::Network network)
{
    SelectBaseParams(network);
    pCurrentParams = &Params(network);
}

bool SelectParamsFromCommandLine()
{
    CBaseChainParams::Network network = NetworkIdFromCommandLine();
    if (network == CBaseChainParams::MAX_NETWORK_TYPES)
        return false;

    SelectParams(network);
    return true;
}
