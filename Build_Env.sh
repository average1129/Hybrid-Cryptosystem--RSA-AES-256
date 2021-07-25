#Building essential packages 

sudo apt-get update
sudo apt-get install build-essential gcc make cmake cmake-gui cmake-curses-gui
sudo apt-get install -y doxygen mercurial
sudo apt-get install m4
sudo apt-get install valgrind

#building gmp ibrary 
hg clone https://gmplib.org/repo/gmp-6.2/ gmp
sudo apt-get install autoconf libtool
cd gmp/
./.bootstrap
./configure --host=x86_64-linux-gnu --disable-static --enable-shared
sudo make -j8
sudo make check
sudo make install
