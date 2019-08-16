Building requires to build three components: patched powertop first, then libksysguard and ksysguard. ksysguard has no source changes, but ABI is not probably preserved.

## Clone repo
The repo includes a patched version of powertop, which is included as a submodule. So clone with --recursive.

## Build powertop
Go to energycore/powertop and build powertop as described in its own repo. It should output a static lib, a shared lib and a binary. Refer to powertop repo for its own deps.

    ./autogen.sh
    ./configure --prefix=$PWD/out
    make
    make install

Copy the static library to energycore and replace the version you have there. This is just a temporary solution.

    cp out/lib/libpowertop.a ../libpowertop.a

## Build libksysguard
Build branch energy_wip as usual.

## Build ksysguard
It is probably needed to rebuild ksysguard aginst the new libksysguard as ABI probably changed.
