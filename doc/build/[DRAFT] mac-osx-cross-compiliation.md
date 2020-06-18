(Draft) Mac OSX Cross-Compiliation of SCC Core
===============================

SCC Core can be cross-compiled on Linux to all other supported host systems. This is done by changing
the `HOST` parameter when building the dependencies and then specifying another `--prefix` directory when building SCC.

The following instructions are only tested on Debian Stretch and Ubuntu Bionic.

MacOSX Cross-compilation
------------------------
Cross-compiling to MacOSX requires a few additional packages to be installed:

```bash
$ sudo apt-get install python3-setuptools libcap-dev zlib1g-dev libbz2-dev python-pip cmake 
$ pip install setuptools
```

Additionally, the Mac OSX SDK must be downloaded and extracted manually:

```bash
$ mkdir -p depends/sdk-sources
$ mkdir -p depends/SDKs
$ curl https://bitcoincore.org/depends-sources/sdks/MacOSX10.11.sdk.tar.gz -o depends/sdk-sources/MacOSX10.11.sdk.tar.gz
$ tar -C depends/SDKs -xf depends/sdk-sources/MacOSX10.11.sdk.tar.gz
```

```bash
$ cd depends
$ make HOST=x86_64-apple-darwin11
$ cd ..
$ ./autogen.sh
$ CONFIG_SITE=$PWD/depends/x86_64-apple-darwin11/share/config.site ./configure --prefix=/
$ make
```

