#include "pch.h"
#include "CppUnitTest.h"
#include "../../CSSC_compression_code/CSSC_compression_code/ByteArrayOutputStream.h"
#include "../../CSSC_compression_code/CSSC_compression_code/ByteBuffer.h"
#include "../../CSSC_compression_code/CSSC_compression_code/IntRleEncoder.h"
#include "../../CSSC_compression_code/CSSC_compression_code/IntRleDecoder.h"
#include "../../CSSC_compression_code/CSSC_compression_code/ByteArrayOutputStream.cpp"
#include "../../CSSC_compression_code/CSSC_compression_code/ByteBuffer.cpp"
#include "../../CSSC_compression_code/CSSC_compression_code/IntRleEncoder.cpp"
#include "../../CSSC_compression_code/CSSC_compression_code/IntRleDecoder.cpp"

#include "../../CSSC_compression_code/CSSC_compression_code/RleEncoder.h"
#include "../../CSSC_compression_code/CSSC_compression_code/RleEncoder.cpp"

#include "../../CSSC_compression_code/CSSC_compression_code/RleDecoder.h"
#include "../../CSSC_compression_code/CSSC_compression_code/RleDecoder.cpp"

#include "../../CSSC_compression_code/CSSC_compression_code/IntPacker.h"
#include "../../CSSC_compression_code/CSSC_compression_code/IntPacker.cpp"


#include "../../CSSC_compression_code/CSSC_compression_code/lz4.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(RLETEST)
	{
	public:
		
		TEST_METHOD(IntSingleValue)
		{
			int data[] = { 0, 1, 22, 333, 4444, 5555, 6666, 1213122, 2187800 };
			//ll data[] = { 1 };
			for (auto d : data) {
				ByteArrayOutputStream out;
				IntRleEncoder encoder;
				IntRleDecoder decoder;
				encoder.encode(d, out);
				encoder.flush(out);
				ByteBuffer in(out.getBytes());
				int r = decoder.readInt(in);
				Assert::AreEqual(d, r);
			}
		}

		TEST_METHOD(IntRepeatValue)
		{
			for (int i = 0; i < 100; i++) {
				ByteArrayOutputStream out;
				IntRleEncoder encoder;
				IntRleDecoder decoder;
				for (int j = 0; j < 2000; j++) {
					encoder.encode(i, out);
				}
				encoder.flush(out);
				ByteBuffer in(out.getBytes());
				for (int j = 0; j < 2000; j++) {
					int r = decoder.readInt(in);
					Assert::AreEqual((int)i, r);
				}
				bool a = decoder.hasNext(in);
				Assert::AreEqual(false, decoder.hasNext(in));
			}
		}

		TEST_METHOD(IntMultipleValues) {
			ByteArrayOutputStream out;
			IntRleEncoder encoder;
			IntRleDecoder decoder;
			for (int j = 0; j < 2000; j++) {
				encoder.encode((int)(j * pow(-1, j)), out);
			}
			encoder.flush(out);
			ByteBuffer in(out.getBytes());
			for (int j = 0; j < 2000; j++) {
				int r = decoder.readInt(in);
				Assert::AreEqual((int)(j * pow(-1, j)), r);
			}
			bool a = decoder.hasNext(in);
			Assert::AreEqual(false, decoder.hasNext(in));
		}

		TEST_METHOD(IntFinalTest) {
			vector<int> v;
			for (int i = 0; i < 20000; i++) {
				v.push_back(rand());
			}
			ByteArrayOutputStream out;
			IntRleEncoder encoder;
			IntRleDecoder decoder;
			for (int i = 0; i < 2000; i++) {
				encoder.encode(v[i], out);
			}
			encoder.flush(out);
			ByteBuffer in(out.getBytes());
			for (int i = 0; i < 2000; i++) {
				int r = decoder.readInt(in);
				Assert::AreEqual(v[i], r);
			}
			Assert::AreEqual(false, decoder.hasNext(in));
		}
	};
}
