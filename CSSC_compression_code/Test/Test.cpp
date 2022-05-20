#include "pch.h"
#include "CppUnitTest.h"
#include "../CSSC_compression_code/ByteBuffer.h"
#include "../CSSC_compression_code/ByteArrayOutputStream.h"
#include "../CSSC_compression_code/LongDeltaEncoder.h"
#include "../CSSC_compression_code/LongDeltaDecoder.h"
#include "../CSSC_compression_code/IntDeltaEncoder.h"
#include "../CSSC_compression_code/IntDeltaDecoder.h"
#include "../CSSC_compression_code/TS_2DIFF_encoder.h"
#include "../CSSC_compression_code/TS_2DIFF_decoder.h"
#include "../CSSC_compression_code/FloatDeltaDecoder.h"
#include "../CSSC_compression_code/FloatDeltaEncoder.h"

#include "../CSSC_compression_code/ByteBuffer.cpp"
#include "../CSSC_compression_code/ByteArrayOutputStream.cpp"
#include "../CSSC_compression_code/LongDeltaEncoder.cpp"
#include "../CSSC_compression_code/LongDeltaDecoder.cpp"
#include "../CSSC_compression_code/IntDeltaEncoder.cpp"
#include "../CSSC_compression_code/IntDeltaDecoder.cpp"
#include "../CSSC_compression_code/FloatDeltaDecoder.cpp"
#include "../CSSC_compression_code/FloatDeltaEncoder.cpp"

#include "../CSSC_compression_code/TS_2DIFF_encoder.cpp"
#include "../CSSC_compression_code/TS_2DIFF_decoder.cpp"
#include "../CSSC_compression_code/main.cpp"


#include <corecrt_math.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Test
{
	TEST_CLASS(LongDeltaDecoderTest)
	{
	public:
		
		TEST_METHOD(SingleValue)
		{
			ll data[] = { 0,1,22,333,4444,5555,6666,12131123122,2143487800 };
			//ll data[] = { 1 };
			for (auto d : data) {
				ByteArrayOutputStream out;
				LongDeltaEncoder encoder;
				LongDeltaDecoder decoder;
				encoder.encode(d, out);
				encoder.flush(out);
				ByteBuffer in(out.getBytes());
				ll r = decoder.readLong(in);
				Assert::AreEqual(d, r);
			}
		}

		TEST_METHOD(RepeatValue)
		{
			for (int i = 0; i < 100; i++) {
				ByteArrayOutputStream out;
				LongDeltaEncoder encoder;
				LongDeltaDecoder decoder;
				for (int j = 0; j < 2000; j++) {
					encoder.encode(i, out);
				}
				encoder.flush(out);
				ByteBuffer in(out.getBytes());
				for (int j = 0; j < 2000; j++) {
					ll r = decoder.readLong(in);
					Assert::AreEqual((ll)i, r);
				}
				bool a = decoder.hasNext(in);
				Assert::AreEqual(false, decoder.hasNext(in));
			}
		}

		TEST_METHOD(MultipleValues) {
			ByteArrayOutputStream out;
			LongDeltaEncoder encoder;
			LongDeltaDecoder decoder;
			for (int j = 0; j < 2000; j++) {
				encoder.encode((ll)(j * pow(-1, j)), out);
			}
			encoder.flush(out);
			ByteBuffer in(out.getBytes());
			for (int j = 0; j < 2000; j++) {
				ll r = decoder.readLong(in);
				Assert::AreEqual((ll)(j * pow(-1, j)), r);
			}
			bool a = decoder.hasNext(in);
			Assert::AreEqual(false, decoder.hasNext(in));
		}

		TEST_METHOD(FinalTest) {
			vector<ll> v;
			for (int i = 0; i < 20000; i++) {
				v.push_back(rand());
			}
			ByteArrayOutputStream out;
			LongDeltaEncoder encoder;
			LongDeltaDecoder decoder;
			for (int i = 0; i < 2000; i++) {
				encoder.encode(v[i], out);
			}
			encoder.flush(out);
			ByteBuffer in(out.getBytes());
			for (int i = 0; i < 2000; i++) {
				ll r = decoder.readLong(in);
				Assert::AreEqual(v[i], r);
			}
			Assert::AreEqual(false, decoder.hasNext(in));
		}
	};

	TEST_CLASS(IntDeltaDecoderTest) {
		TEST_METHOD(FloatSingleValue)
		{
			int data[] = {0, 1, 22, 333, 4444, 5555, 6666, 1213122, 2187800	};
			//ll data[] = { 1 };
			for (auto d : data) {
				ByteArrayOutputStream out;
				IntDeltaEncoder encoder;
				IntDeltaDecoder decoder;
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
				IntDeltaEncoder encoder;
				IntDeltaDecoder decoder;
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
			IntDeltaEncoder encoder;
			IntDeltaDecoder decoder;
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
			IntDeltaEncoder encoder;
			IntDeltaDecoder decoder;
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

	TEST_CLASS(FloatDecoderTest) {
		TEST_METHOD(FloatSingleValue)
		{
			float data[] = {0, 1.1, 2.2, 3.33, 44.44, 5.555, 6666.6, 121.3122, 218.7800	};
			//ll data[] = { 1 };
			for (auto d : data) {
				ByteArrayOutputStream out;
				FloatDeltaEncoder encoder;
				FloatDeltaDecoder decoder;
				encoder.encode(d, out);
				encoder.flush(out);
				ByteBuffer in(out.getBytes());
				float r = decoder.readFloat(in);
				Assert::AreEqual(d, r);
			}
		}

		TEST_METHOD(floatRepeatValue)
		{
			for (int i = 0; i < 100; i++) {
				ByteArrayOutputStream out;
				FloatDeltaEncoder encoder;
				FloatDeltaDecoder decoder;
				float f = i + (float)i / 50;
				for (int j = 0; j < 2000; j++) {
					encoder.encode(f, out);
				}
				encoder.flush(out);
				ByteBuffer in(out.getBytes());
				for (int j = 0; j < 2000; j++) {
					float r = decoder.readFloat(in);
					Assert::AreEqual(f, r);
				}
				bool a = decoder.hasNext(in);
				Assert::AreEqual(false, decoder.hasNext(in));
			}
		}

		TEST_METHOD(IntFinalTest) {
			vector<float> v;
			for (int i = 0; i < 20000; i++) {
				v.push_back(rand()+(float)rand()/1000);
			}
			ByteArrayOutputStream out;
			FloatDeltaEncoder encoder;
			FloatDeltaDecoder decoder;
			for (int i = 0; i < 2000; i++) {
				encoder.encode(v[i], out);
			}
			encoder.flush(out);
			ByteBuffer in(out.getBytes());
			for (int i = 0; i < 2000; i++) {
				float r = decoder.readFloat(in);
				Assert::AreEqual(v[i], r);
			}
			Assert::AreEqual(false, decoder.hasNext(in));
		}

		TEST_METHOD(MinusZeroTest) {
			vector<int> v;
			for (int i = 0; i < 20; i++) {
				float r = -0.0;
				int a;
				memcpy(&a, &r, sizeof(int));
				v.push_back(a);
			}
			ByteArrayOutputStream out;
			IntDeltaEncoder encoder;
			IntDeltaDecoder decoder;
			for (int i = 0; i < 20; i++) {
				encoder.encode(v[i], out);
			}
			encoder.flush(out);
			ByteBuffer in(out.getBytes());
			for (int i = 0; i < 20; i++) {
				int r = decoder.readInt(in);
				Assert::AreEqual(v[i], r);
				float r1;
				memcpy(&r1, &r, sizeof(int));
			}
			Assert::AreEqual(false, decoder.hasNext(in));
		}

		TEST_METHOD(RoundDouble) {
			float r = -0.000000;
			float r1 = round_double(r, 5);
			Assert::AreEqual(r1, r);
		}
	};
}
