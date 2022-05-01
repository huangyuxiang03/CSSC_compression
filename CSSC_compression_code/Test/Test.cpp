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
			//ll data[] = { 0,1,22,333,4444,5555,6666,12131123122,2143487800 };
			ll data[] = { 1 };
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
	};
}
