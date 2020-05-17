icp:
	cd src && qmake -makefile icp.pro && make

run:
	cd ./src; ./icp

pack:
	make clean && zip xburka00-xklusa14.zip ./doc/img/* examples/* src/* Makefile README.txt

doxygen:
	doxygen ./src/Doxyfile
clean:
	cd src && make clean
clean-doxy:
	rm -r ./doc/html
clean-pack:
	rm xburka00-xklusa14.zip
