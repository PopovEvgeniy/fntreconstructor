                                 FNT RECONSTRUCTOR

                     Mugen font tool by Popov Evgeniy Alekseyevich

                                 Version 0.6

System requirement

48 kilobytes free space on storage media.

Description and usage

This program let you compile and decompile a fonts for MUGEN game engine.
Give a target file name as command line argument for decompile a font.
Give 3 command line arguments for compile a font:text file name, graphic file name, font file name.

Exit codes

0 - Operation successfully complete.
1 - Can't allocate memory.
2 - File operation error.
3 - Invalid format.

License

This program distributed under GNU GENERAL PUBLIC LICENSE.

Source code

The program source code was compiled under Open Watcom.
But you can do it under any modern C compiler.
Source code can be compiled for wide range operation systems, but you need create makefile or build script by yourself.
I provide only two things: compiled binary file for Windows and makefile for Linux.

Installation and uninstallation under Linux

Follow this steps:

1.Extract content of source code archive.
2.Open terminal and go to source code directory.
3.
Run for installation: make install
Run for uninstallation: make uninstall

Contact

You can send me a letter to tuzik87@inbox.ru.

Version history

0.1 — Initial version.
0.2 - 0.5 — Small changes.
0.6 - Source code was improved. Linux support has been added.
