#######################
# Makefile
#######################
# source object target
SOURCE := *.cpp
OBJS   := *.o
TARGET := task
 
# compile and lib parameter
CC      := g++
LIBS    := libz.a
LDFLAGS := -L.
DEFINES :=
INCLUDE := -I.
CFLAGS  := 
CXXFLAGS:= 
 
# link
$(TARGET): BitVectorDecoder.o BitVectorEncoder.o ByteArrayOutputStream.o ByteBuffer.o FloatDeltaDecoder.o FloatDeltaEncoder.o FloatRleEncoder.o FloatRleDecoder.o FragmentEncoder.o IndexDecoder.o IndexEncoder.o IntDeltaDecoder.o IntDeltaEncoder.o IntPacker.o IntRleDecoder.o IntRleEncoder.o LongDeltaDecoder.o LongDeltaEncoder.o RleDecoder.o RleEncoder.o TS_2DIFF_decoder.o TS_2DIFF_encoder.o GZIP.o main.o
	$(CC) -std=c++14 -o $@ $^ $(LIBS)

# compile
BitVectorDecoder.o: BitVectorDecoder.cpp
	$(CC) -std=c++14 -c $^ -o $@
BitVectorEncoder.o: BitVectorEncoder.cpp
	$(CC) -std=c++14 -c $^ -o $@
ByteArrayOutputStream.o: ByteArrayOutputStream.cpp
	$(CC) -std=c++14 -c $^ -o $@ 
ByteBuffer.o: ByteBuffer.cpp
	$(CC) -std=c++14 -c $^ -o $@ 
FloatDeltaDecoder.o: FloatDeltaDecoder.cpp
	$(CC) -std=c++14 -c $^ -o $@ 
FloatDeltaEncoder.o: FloatDeltaEncoder.cpp
	$(CC) -std=c++14 -c $^ -o $@ 
FloatRleEncoder.o: FloatRleEncoder.cpp
	$(CC) -std=c++14 -c $^ -o $@ 
FloatRleDecoder.o: FloatRleDecoder.cpp
	$(CC) -std=c++14 -c $^ -o $@ 
FragmentEncoder.o: FragmentEncoder.cpp
	$(CC) -std=c++14 -c $^ -o $@ 
IndexDecoder.o: IndexDecoder.cpp
	$(CC) -std=c++14 -c $^ -o $@ 
IndexEncoder.o: IndexEncoder.cpp
	$(CC) -std=c++14 -c $^ -o $@ 
IntDeltaDecoder.o: IntDeltaDecoder.cpp
	$(CC) -std=c++14 -c $^ -o $@ 
IntDeltaEncoder.o: IntDeltaEncoder.cpp
	$(CC) -std=c++14 -c $^ -o $@ 
IntPacker.o: IntPacker.cpp
	$(CC) -std=c++14 -c $^ -o $@ 
IntRleDecoder.o: IntRleDecoder.cpp
	$(CC) -std=c++14 -c $^ -o $@ 
IntRleEncoder.o: IntRleEncoder.cpp
	$(CC) -std=c++14 -c $^ -o $@ 
LongDeltaDecoder.o: LongDeltaDecoder.cpp
	$(CC) -std=c++14 -c $^ -o $@ 
LongDeltaEncoder.o: LongDeltaEncoder.cpp
	$(CC) -std=c++14 -c $^ -o $@ 
RleDecoder.o: RleDecoder.cpp
	$(CC) -std=c++14 -c $^ -o $@ 
RleEncoder.o: RleEncoder.cpp
	$(CC) -std=c++14 -c $^ -o $@ 
TS_2DIFF_decoder.o: TS_2DIFF_decoder.cpp
	$(CC) -std=c++14 -c $^ -o $@ 
TS_2DIFF_encoder.o: TS_2DIFF_encoder.cpp
	$(CC) -std=c++14 -c $^ -o $@
GZIP.o: GZIP.cpp
	$(CC) -std=c++14 -c $^ -o $@
main.o: main.cpp
	$(CC) -std=c++14 -c $^ -o $@
# clean
clean:
	rm -fr *.o
	rm -fr $(TARGET)
