
Debian
====================
This directory contains files used to package monetaryunitd/monetaryunit-qt
for Debian-based Linux systems. If you compile monetaryunitd/monetaryunit-qt yourself, there are some useful files here.

## monetaryunit: URI support ##


monetaryunit-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install monetaryunit-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your monetaryunitqt binary to `/usr/bin`
and the `../../share/pixmaps/monetaryunit128.png` to `/usr/share/pixmaps`

monetaryunit-qt.protocol (KDE)

