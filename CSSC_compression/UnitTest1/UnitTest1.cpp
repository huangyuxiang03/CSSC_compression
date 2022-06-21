#include "pch.h"
#include "CppUnitTest.h"
#include "../CSSC_compression0619/ByteArrayOutputStream.h"
#include "../CSSC_compression0619/ByteBuffer.h"
#include "../CSSC_compression0619/IntRleEncoder.h"
#include "../CSSC_compression0619/IntRleDecoder.h"
#include "../CSSC_compression0619/ByteArrayOutputStream.cpp"
#include "../CSSC_compression0619/ByteBuffer.cpp"
#include "../CSSC_compression0619/IntRleEncoder.cpp"
#include "../CSSC_compression0619/IntRleDecoder.cpp"

#include "../CSSC_compression0619/RleEncoder.h"
#include "../CSSC_compression0619/RleEncoder.cpp"

#include "../CSSC_compression0619/RleDecoder.h"
#include "../CSSC_compression0619/RleDecoder.cpp"

#include "../CSSC_compression0619/IntPacker.h"
#include "../CSSC_compression0619/IntPacker.cpp"

#include "../CSSC_compression0619/GZIP.cpp"
#include "../CSSC_compression0619/GZIP.h"



#include <string>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(RLETEST)
	{
	public:

		TEST_METHOD(IntSingleValue)
		{
			//int data[] = { 0, 1, 22, 333, 4444, 5555, 6666, 1213122, 2187800 };
			int data[] = { 1804289383 };
			for (auto d : data) {
				ByteArrayOutputStream out;
				IntRleEncoder encoder;
				IntRleDecoder decoder;
				encoder.encode(d, out);
				encoder.flush(out);
				ByteBuffer in(out.getBytes());
				int r = decoder.readInt(in);
				Assert::AreEqual(d, r);
				Assert::AreEqual(false, decoder.hasNext(in));
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
			for (int i = 0; i < 200000; i++) {
				v.push_back(rand());
			}
			ByteArrayOutputStream out;
			IntRleEncoder encoder;
			IntRleDecoder decoder;
			for (int i = 0; i < 200000; i++) {
				encoder.encode(v[i], out);
			}
			encoder.flush(out);
			ByteBuffer in(out.getBytes());
			for (int i = 0; i < 200000; i++) {
				int r = decoder.readInt(in);
				Assert::AreEqual(v[i], r);
			}
			Assert::AreEqual(false, decoder.hasNext(in));
		}

	};
}
