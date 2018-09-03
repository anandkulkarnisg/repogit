################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../BinaryTree.cpp \
../bubblesort.cpp \
../heapsort.cpp \
../insertionsort.cpp \
../main.cpp \
../mergesort.cpp \
../quicksort.cpp \
../selectionsort.cpp \
../shellsort.cpp \
../singleLinkedList.cpp \
../sortutils.cpp 

OBJS += \
./BinaryTree.o \
./bubblesort.o \
./heapsort.o \
./insertionsort.o \
./main.o \
./mergesort.o \
./quicksort.o \
./selectionsort.o \
./shellsort.o \
./singleLinkedList.o \
./sortutils.o 

CPP_DEPS += \
./BinaryTree.d \
./bubblesort.d \
./heapsort.d \
./insertionsort.d \
./main.d \
./mergesort.d \
./quicksort.d \
./selectionsort.d \
./shellsort.d \
./singleLinkedList.d \
./sortutils.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/anand/git/repogit/cpp/datastructures" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


