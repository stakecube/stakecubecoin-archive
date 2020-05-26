
from bitcoinrpc.authproxy import AuthServiceProxy, JSONRPCException
from itertools import islice
import time
import json

# Breaks up dictionary into chunks
def chunks(data, SIZE=1000):
    it = iter(data)
    for i in range(0, len(data), SIZE):
        yield {k:data[k] for k in islice(it, SIZE)}

# Number of addresses per transaction in sendmany
batch_size = 5

balances = json.load(open("balances.json","r"))

# Make dictionary of addresses and decimal balances
disbursals = {}
total_amount = 0
for entry in balances:
    # Convert from satoshis to decimal value
    disbursals[entry['address']] = entry['balance'] / 100000000
    total_amount += entry['balance'] / 100000000

print("Total amount to send: " + str(total_amount))
exit()

# replace rpcuser and rpcpassword values for your local node to match helium.conf
rpc_connection = AuthServiceProxy("http://%s:%s@%s:%s" % ('user', 'password', '127.0.0.1', '19688'))
print(rpc_connection.getbalance())

# Chunking was not necessary since there were less than 800 transactions,
# but would be for very large disbursals that may exceed maximum transaction size.
# Premine funds were sent in advance manually to an address with Premine as the label.
# If this had not been done, the default account of "" would have worked.
for chunk in chunks(disbursals, batch_size):
     print(chunk)
     sendcoins = rpc_connection.sendmany("", chunk)
     time.sleep(10)
