task:main.o ByteArrayOutputStream.o ByteBuffer.o TS_2DIFF_decoder.o TS_2DIFF_encoder.o LongDeltaDecoder.o LongDeltaEncoder.o IntDeltaDecoder.o IntDeltaEncoder.o FloatDeltaDecoder.o FloatDeltaEncoder.o BitVectorDecoder.o BitVectorEncoder.o
	g++ main.o ByteArrayOutputStream.o ByteBuffer.o TS_2DIFF_decoder.o TS_2DIFF_encoder.o LongDeltaDecoder.o LongDeltaEncoder.o IntDeltaDecoder.o IntDeltaEncoder.o FloatDeltaDecoder.o FloatDeltaEncoder.o BitVectorDecoder.o BitVectorEncoder.o -o task
main.o:main.cpp ByteArrayOutputStream.h LongDeltaEncoder.h LongDeltaDecoder.h
	g++ -c main.cpp -o main.o
ByteArrayOutputStream.o: ByteArrayOutputStream.cpp ByteArrayOutputStream.h
	g++ -c ByteArrayOutputStream.cpp -o ByteArrayOutputStream.o
ByteBuffer.o: ByteBuffer.cpp ByteBuffer.h
	g++ -c ByteBuffer.cpp -o ByteBuffer.o
TS_2DIFF_decoder.o: TS_2DIFF_decoder.cpp TS_2DIFF_decoder.h ByteBuffer.h
	g++ -c TS_2DIFF_decoder.cpp -o TS_2DIFF_decoder.o
TS_2DIFF_encoder.o: TS_2DIFF_encoder.cpp TS_2DIFF_encoder.h ByteArrayOutputStream.h
	g++ -c TS_2DIFF_encoder.cpp -o TS_2DIFF_encoder.o
LongDeltaDecoder.o: LongDeltaDecoder.cpp LongDeltaDecoder.h TS_2DIFF_decoder.h ByteBuffer.h
	g++ -c LongDeltaDecoder.cpp -o LongDeltaDecoder.o
LongDeltaEncoder.o: LongDeltaEncoder.cpp LongDeltaEncoder.h TS_2DIFF_encoder.h
	g++ -c LongDeltaEncoder.cpp -o LongDeltaEncoder.o
IntDeltaDecoder.o: IntDeltaDecoder.cpp IntDeltaDecoder.h TS_2DIFF_decoder.h ByteBuffer.h
	g++ -c IntDeltaDecoder.cpp -o IntDeltaDecoder.o
IntDeltaEncoder.o: IntDeltaEncoder.cpp IntDeltaEncoder.h TS_2DIFF_encoder.h
	g++ -c IntDeltaEncoder.cpp -o IntDeltaEncoder.o
FloatDeltaDecoder.o: FloatDeltaDecoder.cpp FloatDeltaDecoder.h IntDeltaDecoder.h
	g++ -c FloatDeltaDecoder.cpp -o FloatDeltaDecoder.o
FloatDeltaEncoder.o: FloatDeltaEncoder.cpp FloatDeltaEncoder.h IntDeltaEncoder.h ByteArrayOutputStream.h
	g++ -c FloatDeltaEncoder.cpp -o FloatDeltaEncoder.o
BitVectorDecoder.o: BitVectorDecoder.cpp BitVectorDecoder.h IntDeltaDecoder.h ByteArrayOutputStream.h
	g++ -c BitVectorDecoder.cpp -o BitVectorDecoder.o
BitVectorEncoder.o: BitVectorEncoder.cpp BitVectorEncoder.h IntDeltaEncoder.h ByteArrayOutputStream.h
	g++ -c BitVectorEncoder.cpp -o BitVectorEncoder.o

clean:
	rm *.o