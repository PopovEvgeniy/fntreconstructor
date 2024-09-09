                                 FNT RECONSTRUCTOR

                     Mugen font tool by Popov Evgeniy Alekseyevich

                                 Version 0.7.3.1

System requirement

64 kilobytes of free space on storage media.

Description and usage

This program lets you compile and decompile fonts for MUGEN game engine.
Give a target file name as a command-line argument to decompile a font.
Give 3 command-line arguments to compile a font: text file name, graphic file name, font file name.

Exit codes

0 - Operation successfully completed.
1 - Can't open input file.
2 - Can't create output file.
3 - Can't jump to target offset.
4 - Can't allocate memory.
5 - Invalid format.

License

This program is distributed under GNU GENERAL PUBLIC LICENSE.

Source code

The  code was compiled under Open Watcom.
But you can compile it under any modern C compiler.
Source code can be compiled for a wide range of operating systems, but you need to create a makefile or build script by yourself.
I provide only two things: the binary file for Windows and makefile for Linux.

Install and uninstall under Linux

Follow these steps:

1. Extract the content of the source code archive.
2. Open a terminal and go to the source code directory.
3.
Run as root to install: make install
Run as root to uninstall: make uninstall

Contact

You can send me a letter at tuzik87@inbox.ru.

Version history

0.1 — Initial version.
0.2 — 0.5 — Small changes.
0.6 — Source code improved. Linux support added.
0.6.0.1 – Documentation updated.
0.6.1 — 0.6.2 — Small changes.
0.6.3 — Command line argument handling improved.
0.6.3.1 — Makefile updated.
0.6.4 — 0.6.5 — Small changes.
0.6.6 — 0.6.7 — Small bug fixed.
0.6.8 — 0.6.9 — Small changes.
0.6.9.1 — 0.6.9.2 — Makefile updated.
0.6.9.3 — Documentation updated.
0.7 — 0.7.2 — Small changes.
0.7.3 — Visual C++ support improved.
0.7.3.1 — Documentation updated.