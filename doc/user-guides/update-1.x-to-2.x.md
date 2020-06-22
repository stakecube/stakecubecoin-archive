## (Draft) Update SCC 1.x to 2.x

> IMPORTANT: Backup your wallet.dat and configuration files

### Wallet

**Upgrading the wallet format is optional but recommended**  
1. Download the latest wallet release for your operating system
2. Start the executable
3. Choose the data directory (make sure it is different from the 1.x version)  
1.x default data dir: */StakeCubeCore  
2.x default data dir: */StakeCubeCoin  
4. Cancel the seed word wizard (close with 'X')
5. Place your wallet.dat and configuration files into the new data directory
6. Rename stakecube.conf to stakecubecoin.conf
7. Start the executable again 
8. Wait for full sync (IMPORTANT!!)  
*Optinal:* use the bootstrap to speed up the process
9. Go to menu item "Tools" -> "Wallet repair" -> choose button 'Upgrade non-hd wallet to hd'. Next, use 'Create New Wallet' in the seed word wizard and follow the instructions. Make sure to write down the seed words! 
10. After finishing the process, it will restart the wallet and upgrade the wallet.dat format
