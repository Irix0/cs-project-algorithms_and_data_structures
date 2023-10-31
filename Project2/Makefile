OFILES_testlist = testcputime.o PointDctList.o Point.o List.o
OFILES_testbst = testcputime.o PointDctBST.o Point.o List.o BST.o
OFILES_testbst2d = testcputime.o PointDctBST2d.o Point.o List.o BST2d.o
OFILES_taxi = testtaxi.o PointDctList.o Point.o List.o
OFILES_taxibst = testtaxi.o PointDctBST.o Point.o List.o BST.o
OFILES_taxibst2d = testtaxi.o PointDctBST2d.o Point.o List.o BST2d.o

TARGET_testlist = testlist
TARGET_testbst = testbst
TARGET_testbst2d = testbst2d
TARGET_taxi = testtaxi
TARGET_taxibst = testtaxibst
TARGET_taxibst2d = testtaxibst2d

CC = gcc
CFLAGS = -Wall -Wextra -Wmissing-prototypes --pedantic -std=c99

.PHONY: all clean run

LDFLAGS = -lm

all: $(TARGET_testlist) $(TARGET_testbst) $(TARGET_testbst2d)
clean:
	rm -f $(OFILES_testlist) $(OFILES_testbst) $(OFILES_testbst2d) $(OFILES_taxi) $(OFILES_taxibst) $(OFILES_taxibst2d) $(TARGET_testlist) $(TARGET_testbst) $(TARGET_testbst2d) $(TARGET_taxi) $(TARGET_taxibst) $(TARGET_taxibst2d)
run: $(TARGET_testlist) $(TARGET_testbst) $(TARGET_testbst2d)
	./$(TARGET_testlist) 1000000 10000 0.01
	./$(TARGET_testbst) 1000000 10000 0.01
	./$(TARGET_testbst2d) 1000000 10000 0.01

$(TARGET_testlist): $(OFILES_testlist)
	$(CC) -o $(TARGET_testlist) $(OFILES_testlist) $(LDFLAGS)
$(TARGET_testbst): $(OFILES_testbst)
	$(CC) -o $(TARGET_testbst) $(OFILES_testbst) $(LDFLAGS)
$(TARGET_testbst2d): $(OFILES_testbst2d)
	$(CC) -o $(TARGET_testbst2d) $(OFILES_testbst2d) $(LDFLAGS)
$(TARGET_taxi): $(OFILES_taxi)
	$(CC) -o $(TARGET_taxi) $(OFILES_taxi) $(LDFLAGS)
$(TARGET_taxibst): $(OFILES_taxibst)
	$(CC) -o $(TARGET_taxibst) $(OFILES_taxibst) $(LDFLAGS)
$(TARGET_taxibst2d): $(OFILES_taxibst2d)
	$(CC) -o $(TARGET_taxibst2d) $(OFILES_taxibst2d) $(LDFLAGS)

BST.o: BST.c BST.h List.h
BST2d.o: BST2d.c BST2d.h Point.h List.h
List.o: List.c List.h
Point.o: Point.c Point.h
PointDctBST.o: PointDctBST.c PointDct.h List.h Point.h BST.h
PointDctBST2d.o: PointDctBST2d.c PointDct.h List.h Point.h BST2d.h
PointDctList.o: PointDctList.c PointDct.h List.h Point.h
testcputime.o: testcputime.c PointDct.h List.h Point.h
testtaxi.o: testtaxi.c PointDct.h List.h Point.h
