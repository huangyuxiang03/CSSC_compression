#include "IntFunctionEncoder.h"

void IntFunctionEncoder::addDictionary(int num)
{
	if (this->curDictinctPoolNum == 0) {
		dictinctPool[0] = num;
		this->curDictinctPoolNum = 1;
		return;
	}
	
	int i = 0;
	for (; i < this->curDictinctPoolNum; i++) {
		if (num > dictinctPool[i]) break;
		if (num == dictinctPool[i]) return;
	}
	if (i == this->curDictinctPoolNum) {
		dictinctPool[i] = num;
	} 
	else {
		int tmpValue = dictinctPool[i];
		dictinctPool[i] = num;
		i++;
		int tmpValue2 = dictinctPool[i];
		while (i < this->curDictinctPoolNum + 1) {
			tmpValue2 = dictinctPool[i];
			dictinctPool[i]= tmpValue;
			tmpValue = tmpValue2;
			i++;
	    }
	}
	this->curDictinctPoolNum++;
}


void IntFunctionEncoder::encode(int num, ByteArrayOutputStream baos)
{
	readyEncodeBuffer.append(num);
	addDictionary(num);
	if (this->curDictinctPoolNum < this->definitionalDomainSize) return;
	beta = (dictinctPool[this->definitionalDomainSize - 1] - dictinctPool[0]) / this->definitionalDomainSize;
	c = dictinctPool[0];
	for (int i = 0; i < this->definitionalDomainSize; i++) {
		keyPool[i] = dictinctPool[i] - (i * beta + c);
		double a = log(keyPool[i]) / log(2)+1;
		if(eta < floor(a)) eta = floor(a);
	}

	readyEncodeBuffer.clear();
	this->curDictinctPoolNum = 0;
	dictinctPool = new int[this->definitionalDomainSize];
	keyPool = new int[this->definitionalDomainSize];
}
