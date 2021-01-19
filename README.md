# psp-libpatcher
Patch official PSP SDK libs to run on firmware 1.00

Beginning with firmware 1.50 a new feature was introduced to use scratchpad RAM to give games more memory. This is done by setting a flag of an imported library to either 0x10 or 0x11.

Firmwares prior to 1.50 will fail to run or load any modules that have this flag set with error 0x80020001. This tool will patch library files to unset this flag allowing compiled games to run on prior firmwares.

Has been tested with 1.51 SDK and executables run on firmwares 1.00, 1.02, and 1.03.

Usage: libpatcher <library.a>

TODO: need to dynamically search for stubs to fix modules like pspkernel.a
