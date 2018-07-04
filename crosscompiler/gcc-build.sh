export CC=/usr/local/bin/gcc-7
export LD=/usr/local/bin/gcc-7
export PREFIX="/Users/limuyang/Desktop/OS-Kernel/crosscompiler/gcc"
export TARGET=i386-elf
export PATH="$PREFIX/bin:$PATH"

cd '/Users/limuyang/Desktop/OS-Kernel/crosscompiler/src'
curl -O http://ftp.gnu.org/gnu/binutils/binutils-2.30.tar.gz # If the link 404's, look for a more recent version
tar xf binutils-2.30.tar.gz
mkdir binutils-build
cd binutils-build
../binutils-2.30/configure --target=$TARGET --enable-interwork --enable-multilib --disable-nls --disable-werror --prefix=$PREFIX 2>&1 | tee configure.log
make all install 2>&1 | tee make.log

cd '/Users/limuyang/Desktop/OS-Kernel/crosscompiler/src'
curl -O https://ftp.gnu.org/gnu/gcc/gcc-7.3.0/gcc-7.3.0.tar.gz
tar xf gcc-7.3.0.tar.gz
mkdir gcc-build
cd gcc-build
../gcc-7.3.0/configure --target=$TARGET --prefix="$PREFIX" --disable-nls --disable-libssp --enable-languages=c --without-headers
make all-gcc 
make all-target-libgcc 
make install-gcc 
make install-target-libgcc 
