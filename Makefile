all: 
	g++ -Wall -std=c++11 RedBlackTree.cpp RedBlackTreeTestsFirstStep.cpp -o firsttests
	g++ -Wall -std=c++11 RedBlackTree.cpp RedBlacktreeTests.cpp -o moretests
run: 
	./firsttests
	./moretests

try: all run