all:
	g++ -o ncurses_1 ncurses_1.cpp -lncurses
	g++ -o ncurses_2 ncurses_2.cpp -lncurses 

clean:
	rm -rf ncurses_1 ncurses_2


#################################
# install ncurses library: 
# 	sudo apt-get install libncurses5-dev
