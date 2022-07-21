#######################
# Makefile
#######################
# source object target
SOURCE := *.cpp
OBJS   := *.o
TARGET := task
 
# compile and lib parameter
CC      := g++ -O3
LIBS    := libz.a # libstatic.a
LDFLAGS := -L.
DEFINES :=
INCLUDE := -I.
CFLAGS  := 
CXXFLAGS:= 
 
# link
$(TARGET): ByteArrayOutputStreamV2.o ByteBuffer.o FloatDeltaDecoder.o FloatDeltaEncoder.o IntDeltaDecoder.o IntDeltaEncoder.o IntPacker.o LongDeltaDecoder.o LongDeltaEncoder.o TS_2DIFF_decoder.o TS_2DIFF_encoder.o GZIP.o main_new.o
	$(CC) -o $@ $^ $(LIBS)

# compile
BitVectorDecoder.o: BitVectorDecoder.cpp
	$(CC) -c $^ -o $@
BitVectorEncoder.o: BitVectorEncoder.cpp
	$(CC) -c $^ -o $@
ByteArrayOutputStreamV2.o: ByteArrayOutputStreamV2.cpp
	$(CC) -c $^ -o $@ 
ByteBuffer.o: ByteBuffer.cpp
	$(CC) -c $^ -o $@ 
# FloatDeltaDecoder.o: FloatDeltaDecoder.cpp
# 	$(CC) -c $^ -o $@ 
# FloatDeltaEncoder.o: FloatDeltaEncoder.cpp
# 	$(CC) -c $^ -o $@ 
# FloatRleEncoder.o: FloatRleEncoder.cpp
# 	$(CC) -c $^ -o $@ 
# FloatRleDecoder.o: FloatRleDecoder.cpp
# 	$(CC) -c $^ -o $@ 
# FragmentEncoder.o: FragmentEncoder.cpp
# 	$(CC) -c $^ -o $@ 
# IndexDecoder.o: IndexDecoder.cpp
# 	$(CC) -c $^ -o $@ 
# IndexEncoder.o: IndexEncoder.cpp
# 	$(CC) -c $^ -o $@ 
IntDeltaDecoder.o: IntDeltaDecoder.cpp
	$(CC) -c $^ -o $@ 
IntDeltaEncoder.o: IntDeltaEncoder.cpp
	$(CC) -c $^ -o $@ 
# IntPacker.o: IntPacker.cpp
# 	$(CC) -c $^ -o $@ 
# IntRleDecoder.o: IntRleDecoder.cpp
# 	$(CC) -c $^ -o $@ 
# IntRleEncoder.o: IntRleEncoder.cpp
# 	$(CC) -c $^ -o $@ 
LongDeltaDecoder.o: LongDeltaDecoder.cpp
	$(CC) -c $^ -o $@ 
LongDeltaEncoder.o: LongDeltaEncoder.cpp
	$(CC) -c $^ -o $@ 
# RleDecoder.o: RleDecoder.cpp
# 	$(CC) -c $^ -o $@ 
# RleEncoder.o: RleEncoder.cpp
	$(CC) -c $^ -o $@ 
TS_2DIFF_decoder.o: TS_2DIFF_decoder.cpp
	$(CC) -c $^ -o $@ 
TS_2DIFF_encoder.o: TS_2DIFF_encoder.cpp
	$(CC) -c $^ -o $@
GZIP.o: GZIP.cpp
	$(CC) -c $^ -o $@
main_new.o: main_new.cpp
	$(CC) -c $^ -o $@
# clean
clean:
	rm -fr *.o
	rm -fr $(TARGET)
