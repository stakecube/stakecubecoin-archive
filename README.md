*** BETA SOFTWARE - USE AT YOUR OWN RISK ***

MUE 2.0
MonetaryUnit Core integration/staging repository
=====================================

MonetaryUnit is a cutting edge cryptocurrency, with many features not available in most other cryptocurrencies.
- 100% Proof of Stake 3.0 Consensus protocol, allowing very low transaction fees and energy expenditure, and staking rewards to all participants in the network
- Masternode technology used to secure the network and provide the above features, each Masternode is secured
  with collateral of 500K MUE
- Decentralized blockchain voting utilizing Masternode technology to form a DAO. The blockchain will distribute monthly treasury funds based on successful proposals submitted by the community and voted on by the DAO.

139439504 MonetaryUnit was produced for swapping.

## Coin Specs ##
<table>
<tr><td>Hash Type</td><td>SHA256</td></tr>
<tr><td>Block Time</td><td>40 Seconds</td></tr>
<tr><td>Difficulty Retargeting</td><td>Every 10 blocks</td></tr>
<tr><td>Max Coin Supply (PoS Phase)</td><td>4 billion</td></tr>
</table>

## PoS Rewards Breakdown ##

<table>
<th>Block Height</th><th>Reward</th><th>Masternodes</th><th>Stakers</th><th>Budget</th>
<tr><td>1-96514012</td><td>36 MUE</td><td>18 MUE</td><td>18 MUE</td><td>4 MUE</td></tr>
<tr><td>96514013+</td><td>0 MUE</td><td>0 MUE</td><td>0 MUE</td><td>0 MUE</td></tr>
</table>

## MUE resources ##
* Client & Source:
[Client Binaries](https://github.com/muecoin/MUE/releases)
[Source Code](https://github.com/muecoin/MUE)
* Links:
[Homepage](https://www.monetaryunit.org)
[CoinBuy](https://www.coinbuy.com)
[CryptoFeed](https://cryptofeed.io)

## Nodes & ports ##
dns1.monetaryunit.org<br>
dns2.monetaryunit.org<br>
dns3.monetaryunit.org<br>
192.99.217.102<br>
164.132.151.109<br>
p2p port :19687

## Importing wallet balances from MUE 1.0.3 wallets into MUE 2.0 wallets ##

MUE has migrated to a completely new codebase, and as such, is no longer compatible with the previous network and blockchain used by the old 1.0.3 wallets.
As part of the migration to the MUE 2.0 wallets and network, users can redeem their old wallet balances* into their new wallets.
This process is simple, but if not done correctly could risk you losing all your coins.

## NEVER UNDER ANY CIRCUMSTANCES GIVE AWAY YOUR PRIVATE KEYS TO ANYONE, THE ONE WHO HAS YOUR KEYS CONTROLS YOUR MUE ##

Please follow these simple steps
1) BACKUP your old MUE wallet, make multiple copies (most critical is your wallet.dat file!)
2) Copy that back up somewhere safe e.g USB drive, seperate computer.
3) Make a list of your wallet addresses (you may need to look in "coin control" for a full list). If coin control is not available in the send tab of your wallet, then activate this under `śettings / Options / Wallet / Enable Coin Control Features`
4) For each wallet address (that you know has a balance of MUE) in debug console run `dumpprivkey 7enteryourmuewalletaddresshere`
5) Record the private key (securely & safely) that is printed there
6) As per item 2) Backup your old MUE wallet (just to be sure).  Again, critical is your wallet.dat file
7) Uninstall your old MUE wallet IF you are installing the 2.0 wallet on the same machine (to avoid any conflicts). For the sake of safety, you may also rename your MUE folder to say MUE-1.0.3-backup so it is preserved on your machine if things go wrong.
8) Install the new MUE 2.0 wallet
9) In debug console run `importprivkey KenterYourPrivateKeyHere "comment"`

You should now see your old MUE balance re-instated into the new MUE 2.0 wallet.
For security, we *strongly recommend* you now send those coins to yourself to a newly generated receive address created in your own 2.0 wallet.

For support, please don't hesitate to join us in our chat platform at http://discord.gg/5PD3X7G

*Only transactions up to and including block 833658 will be processed
