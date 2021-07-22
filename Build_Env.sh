#Building essential packages 

sudo apt-get build-essential gcc make cmake cmake-gui cmake-curses-gui
sudo apt-get install -y doxygen 
sudo apt-get install -y mercurial
sudo apt-get install m4

#building gmp ibrary 
hg clone https://gmplib.org/repo/gmp-6.2/ gmp
sudo apt-get install autoconf libtool
cd gmp/
./.bootstrap
./.configure --host=x86_64-linux-gnu --disable-static --enable-shared
make -j8
make check

