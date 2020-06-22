## (Draft) How to update

> IMPORTANT: Backup your wallet.dat and stakecube.conf/masternode.conf
> files!

### Wallet

1. Download the latest wallet release for your operating system
2. Update the executable 
**Windows** 
Run the installer or replace the *.exe
**Mac**
Copy over /Applications/stakecubecoin-qt  
**Linux**
Replace stakecubed and or stakecubecoin-qt

3. Start the wallet and wait until fully synced

### Masternode(s)

1.  log into your VPS
2.  rm sccmultitool.sh #delete old version
3.  wget  [https://github.com/stakecube/SCC-multitool/raw/master/sccmultitool.sh](https://github.com/stakecube/SCC-multitool/raw/master/sccmultitool.sh)
4.  chmod +x sccmultitool.sh
5.  ./sccmultitool.sh
6.  Select appropriate 'Wallet update' option, either 3 or 31.

*Optional*: Restart the masternode(s) from your controller wallet (if needed - follow the specific instructions for the release)
