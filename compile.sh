rm -rf temp
rm Makefile
./bin/premake4 --os=linux --platform=x32 gmake
make
rm -rf temp
rm Makefile
