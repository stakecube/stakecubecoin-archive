
Debian
====================
This directory contains files used to package stakecubecoind/stakecubecoin-qt
for Debian-based Linux systems. If you compile stakecubecoind/stakecubecoin-qt yourself, there are some useful files here.

## stakecubecoin: URI support ##


stakecubecoin-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install stakecubecoin-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your stakecubecoinqt binary to `/usr/bin`
and the `../../share/pixmaps/stakecubecoin128.png` to `/usr/share/pixmaps`

stakecubecoin-qt.protocol (KDE)

