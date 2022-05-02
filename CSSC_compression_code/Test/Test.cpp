#include "pch.h"
#include "CppUnitTest.h"
#include "../CSSC_compression_code/ByteBuffer.h"
#include "../CSSC_compression_code/ByteArrayOutputStream.h"
#include "../CSSC_compression_code/LongDeltaEncoder.h"
#include "../CSSC_compression_code/LongDeltaDecoder.h"
#include "../CSSC_compression_code/TS_2DIFF_encoder.h"
#include "../CSSC_compression_code/TS_2DIFF_decoder.h"

#include "../CSSC_compression_code/ByteBuffer.cpp"
#include "../CSSC_compression_code/ByteArrayOutputStream.cpp"
#include "../CSSC_compression_code/LongDeltaEncoder.cpp"
#include "../CSSC_compression_code/LongDeltaDecoder.cpp"

#include "../CSSC_compression_code/TS_2DIFF_encoder.cpp"
#include "../CSSC_compression_code/TS_2DIFF_decoder.cpp"


#include <corecrt_math.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Test
{
	TEST_CLASS(Test)
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
}
