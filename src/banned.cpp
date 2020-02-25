// barrystyle 24022020
// banned inputs list
#include "main.h"

typedef std::map<uint256, int> BannedInputs;

const BannedInputs bannedFunds = 
{
    {
	{ uint256("0xb365fcb23292c4c63bb8f67bb6a5d4e9db05aed5ab5e14281e37049ec1aff2dd"), 1 },        // 500000
        { uint256("0xe9f29ab995c3ce735a74bbe8cd0235019cf45547f8b1a62f630109155857c9b9"), 0 },        // 343000
        { uint256("0x717af6ca4d6bf0e454dd87231d338683d5a6b90b6fe904aee04f1fcafa84bb14"), 1 },        // 400000
        { uint256("0xc8938cb1fbf30c70995757b81afd2decf7899219c667dd530b626af98d04e3b5"), 0 },        // 100000
        { uint256("0xcbf0edaf4a5ce2ceef2dbd76bd3033ca4a17e2a5cfa4070626372befc7496611"), 1 },        // 500000
    }
};

bool areBannedInputs(uint256 txid, int vout) {
  for (auto inputs : bannedFunds)
    if (inputs.first == txid && inputs.second == vout)
      return true;
  return false;
}
