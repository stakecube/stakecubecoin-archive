// barrystyle 24022020
// banned inputs list
#include "main.h"

typedef std::map<uint256, int> BannedInputs;

const BannedInputs bannedFunds = 
{
    {	      
        { uint256("0x717af6ca4d6bf0e454dd87231d338683d5a6b90b6fe904aee04f1fcafa84bb14"), 1 },        // 400000
        { uint256("0xc8938cb1fbf30c70995757b81afd2decf7899219c667dd530b626af98d04e3b5"), 0 },        // 100000
        { uint256("0xcbf0edaf4a5ce2ceef2dbd76bd3033ca4a17e2a5cfa4070626372befc7496611"), 1 },        // 500000
        { uint256("0x80ceb841070a61624c45030e1d84a7029dcdde0e1028be099f4ce830a8143c56"), 0 },        
        { uint256("0x80ceb841070a61624c45030e1d84a7029dcdde0e1028be099f4ce830a8143c56"), 1 },        
        { uint256("0x60dff9a6ce4c05265c01e2a3b0dc646ef763147e1011a0c9ad1650efc4e9ccd3"), 0 },        
        { uint256("0x60dff9a6ce4c05265c01e2a3b0dc646ef763147e1011a0c9ad1650efc4e9ccd3"), 1 },        
        { uint256("0x8b35a101b1859862d2628302a3d4604c181c723842ade795f4a92abfcb9ea936"), 0 },        
        { uint256("0x8b35a101b1859862d2628302a3d4604c181c723842ade795f4a92abfcb9ea936"), 1 },    
    }
};

bool areBannedInputs(uint256 txid, int vout) {
  for (auto inputs : bannedFunds)
    if (inputs.first == txid && inputs.second == vout)
      return true;
  return false;
}
