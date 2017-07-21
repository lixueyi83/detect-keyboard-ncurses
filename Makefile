all:
	g++ -o ncurses ncurses.cpp -lncurses

clean:
	rm -rf ncurses


#################################
# install ncurses library: 
# 	sudo apt-get install libncurses5-dev
