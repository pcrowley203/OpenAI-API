if ! [ -d obj ]; then mkdir obj; fi
if ! [ -d bin ]; then mkdir bin; fi
cd src
make
