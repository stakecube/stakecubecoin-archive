Stakecube2 (fork of PIVX) integration/staging repository
========================================================

Quick installation of the Stakecube daemon under linux. See detailed instructions there [build-unix.md](build-unix.md)

Installation of libraries (using root user):

    add-apt-repository ppa:bitcoin/bitcoin -y
    apt-get update
    apt-get install -y build-essential libtool autotools-dev automake pkg-config libssl-dev libevent-dev bsdmainutils
    apt-get install -y libboost-system-dev libboost-filesystem-dev libboost-chrono-dev libboost-program-options-dev libboost-test-dev libboost-thread-dev
    apt-get install -y libdb4.8-dev libdb4.8++-dev

Cloning the repository and compiling (use any user with the sudo group):

    cd Stakecube
    ./autogen.sh
    ./configure
    sudo make install
    cd src
    strip stakecubed
    strip stakecube-cli
    strip stakecube-tx
    cd ..

Running the daemon:

    stakecubed 

Stopping the daemon:

    stakecube-cli stop

Daemon status:

    stakecube-cli getinfo
    stakecube-cli mnsync status
