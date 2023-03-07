OFILES_AdaptiveMergeSort = main.o Array.o AdaptiveMergeSort.o
OFILES_HeapSort = main.o Array.o HeapSort.o
OFILES_QuickSort = main.o Array.o QuickSort.o
OFILES_InsertionSort = main.o Array.o InsertionSort.o
OFILES_MergeSort = main.o Array.o MergeSort.o

TARGET_AdaptiveMergeSort = adaptivemergesort
TARGET_HeapSort = heapsort
TARGET_QuickSort = quicksort
TARGET_InsertionSort = insertionsort
TARGET_MergeSort = mergesort

CC = gcc
CFLAGS = -Wall -Wextra -Wmissing-prototypes --pedantic -std=c99

.PHONY: all clean run

LDFLAGS = -lm

all: $(TARGET_QuickSort)
#all: $(TARGET_AdaptiveMergeSort) $(TARGET_InsertionSort) $(TARGET_MergeSort) $(TARGET_QuickSort) $(TARGET_HeapSort) 
clean:
	rm -f $(OFILES_AdaptiveMergeSort) $(OFILES_HeapSort) $(OFILES_MergeSort) $(OFILES_QuickSort) $(OFILES_InsertionSort) $(TARGET_AdaptiveMergeSort) $(TARGET_HeapSort) $(TARGET_MergeSort) $(TARGET_QuickSort) $(TARGET_InsertionSort) 
run: $(TARGET_AdaptiveMergeSort) $(TARGET_HeapSort) $(TARGET_MergeSort) $(TARGET_QuickSort) $(TARGET_InsertionSort) 
	./$(TARGET_InsertionSort) 10000 1
	./$(TARGET_HeapSort) 10000 1
	./$(TARGET_QuickSort) 10000 1
	./$(TARGET_MergeSort) 10000 1
	./$(TARGET_AdaptiveMergeSort) 10000 1

$(TARGET_AdaptiveMergeSort): $(OFILES_AdaptiveMergeSort)
	$(CC) -o $(TARGET_AdaptiveMergeSort) $(OFILES_AdaptiveMergeSort) $(LDFLAGS)
$(TARGET_QuickSort): $(OFILES_QuickSort)
	$(CC) -o $(TARGET_QuickSort) $(OFILES_QuickSort) $(LDFLAGS)
$(TARGET_HeapSort): $(OFILES_HeapSort)
	$(CC) -o $(TARGET_HeapSort) $(OFILES_HeapSort) $(LDFLAGS)
$(TARGET_MergeSort): $(OFILES_MergeSort)
	$(CC) -o $(TARGET_MergeSort) $(OFILES_MergeSort) $(LDFLAGS)
$(TARGET_InsertionSort): $(OFILES_InsertionSort)
	$(CC) -o $(TARGET_InsertionSort) $(OFILES_InsertionSort) $(LDFLAGS)

Array.o: Array.c Array.h
AdaptiveMergeSort.o: AdaptiveMergeSort.c Sort.h Array.h
QuickSort.o: QuickSort.c Sort.h Array.h
HeapSort.o: Heapsort.c Sort.h Array.h
InsertionSort.o: InsertionSort.c Sort.h Array.h
main.o: main.c Array.h Sort.h Array.h
