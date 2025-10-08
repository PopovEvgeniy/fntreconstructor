                                 FNT RECONSTRUCTOR

                     Mugen font tool by Popov Evgeniy Alekseyevich

                                 Version 0.9

The program description.

This program lets you compile and decompile fonts for the MUGEN game engine.
Give a target file name as the command-line argument to decompile a font.
Give 3 command-line arguments to compile a font: a text file name, a graphic file name, and the font file name.

Exit codes.

0: The operation was successfully completed.
1: Can't open the input file.
2: Can't create the output file.
3: Can't jump to the target offset.
4: Can't allocate memory.
5: The invalid format.

License.

This program is distributed under the GNU GENERAL PUBLIC LICENSE.

The source code.

The code was compiled under Open Watcom.
But you can compile it with any modern C compiler.
The source code can be compiled for a wide range of operating systems, but you need to create a makefile or a build script by yourself.
I provide only two things: the binary file for Windows and the makefile for Linux.

Install and uninstall under Linux.

Follow these steps:

1. Extract the content of the source code archive.
2. Open a terminal and go to the source code directory.
3.
Run as root to install: make install
Run as root to uninstall: make uninstall

Version history.

0.1: The initial version.
0.2-0.5: The small changes.
0.6: The source code has improved. Linux support has been added.
0.6.0.1: The documentation has been updated.
0.6.1-0.6.2: The small changes.
0.6.3: The command-line argument handling has improved.
0.6.3.1: The makefile has been updated.
0.6.4-0.6.5: The small changes.
0.6.6-0.6.7: A small bug has been fixed.
0.6.8-0.6.9: The small changes.
0.6.9.1-0.6.9.2: The makefile has been updated.
0.6.9.3: The documentation has been updated.
0.7-0.7.2: The small changes.
0.7.3: Visual C++ support has improved.
0.7.3.1: The documentation has been updated.
0.7.4: The small changes.
0.7.4.1-0.7.4.2: The documentation has been updated.
0.7.5: The source code was recompiled under Tiny C Compiler.
0.7.6-0.7.7: The small changes.
0.7.7.1: The documentation has been updated.
0.7.8: The small changes.
0.7.8.1: The documentation has been updated.
0.7.9: The decompilation process has improved, and the compilation process has improved.
0.8-0.8.2: The small changes.
0.8.3: The code portability has improved.
0.8.4-0.8.6: A small bug has been fixed.
0.8.7-0.9: The small changes.