cd /Users/limuyang/Desktop/OS-Kernel/crosscomplier/src
# curl -O http://ftp.rediris.es/mirror/GNU/gdb/gdb-7.8.tar.gz
tar xf gdb-7.8.tar.gz
mkdir gdb-build
cd gdb-build
export PREFIX="/Users/limuyang/Desktop/OS-Kernel/crosscompiler/gdb"
export TARGET=i386-elf
../gdb-7.8/configure --target="$TARGET" --prefix="$PREFIX" --program-prefix=i386-elf-
make
make install
