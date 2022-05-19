#include "IntFunctionEncoder.h"

typedef struct { 
	uint8_t b0 : 1; 
	uint8_t b1 : 1;
	uint8_t b2 : 1;
	uint8_t b3 : 1;
	uint8_t b4 : 1;
	uint8_t b5 : 1;
	uint8_t b6 : 1;
	uint8_t b7 : 1;
} bool8_t; 
bool8_t b;
uint8_t c = *(uint8_t*)(&b);

int IntFunctionEncoder::get_index(int t)
{
	for (int i = 0; i < definitionalDomainSize; i++)
	{
		if (dictinctPool[i] == t) return i;
	}
	return -1;
}

void IntFunctionEncoder::addDictionary(int num)
{
	if (this->curDictinctPoolNum == 0) {
		dictinctPool[0] = num;
		this->curDictinctPoolNum = 1;
		return;
	}
	
	int i = 0;
	for (; i < this->curDictinctPoolNum; i++) {
		if (num < dictinctPool[i]) break;
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


void IntFunctionEncoder::encode(int num, ByteArrayOutputStream& baos)
{
	readyEncodeBuffer->append(num);
	addDictionary(num);
	if (this->curDictinctPoolNum < this->definitionalDomainSize) return;
	flush(baos);
}

void IntFunctionEncoder::flush(ByteArrayOutputStream& baos)
{
	if (this->curDictinctPoolNum==0) return;
	int* xi = new int[this->curDictinctPoolNum];
	for (int i = 0; i < this->curDictinctPoolNum; i++) xi[i] = i;
	calculatelsm(this->curDictinctPoolNum, xi, dictinctPool, beta, alpha);
	beta = (dictinctPool[this->curDictinctPoolNum - 1] - dictinctPool[0]) / this->curDictinctPoolNum;
	alpha = dictinctPool[0];
	for (int i = 0; i < this->curDictinctPoolNum; i++) {
		int origin = dictinctPool[i] - (i * beta + alpha);
		keyPool[i] = origin >= 0 ? 2 * origin : 2 * (-origin) + 1;
		double a = log(keyPool[i]) / log(2) + 1;
		if (sigma < floor(a)) sigma = floor(a);
	}

	char etac = eta;
	char sigmac = sigma;
	baos.write(etac);
	baos.write(sigmac);
	baos.write(beta);
	baos.write(alpha);
	//cout << baos.getBytes().size() << endl;
	int encodeSize = readyEncodeBuffer->get_size();
	char encodeSizec = encodeSize;
	baos.write(encodeSizec);
	int length = (eta + sigma) * encodeSize;
	//int block8num = encodeSize / 8;
	Array<char>* tmp = new Array<char>(length);
	//for (int j=0; j < block8num; j++) {

	for (int i = 0; i < encodeSize; i++) {
		int id = get_index(readyEncodeBuffer->element[i]);
		for (int j = eta; j >= 0; j--) tmp->append((id >> j) & 1);
		int ei = keyPool[id];
		for (int j = sigma; j >= 0; j--) tmp->append((ei >> j) & 1);
	}
	int length_compress = length / 8;
	int i = 0;
	for (; i < length_compress; i++) {
		int single_num = 0;
		for (int j = 0; j < 8; j++) {
			single_num = (tmp->get_element(i * 8 + j) == '1') + single_num * 2;
		}
		char c = single_num;
		baos.write(c);
	}
	int single_num = 0;
	for (int j = i * 8; j < (i + 1) * 8; j++) {
		if (j < length) single_num = (tmp->get_element(j) == '1') + single_num * 2;
		else  single_num = single_num * 2;
	}
	char c = single_num;
	baos.write(c);
	//	bool8_t b;
	//	uint8_t c = *(uint8_t*)(&b);
	//}

	//cout<< baos.getBytes().size() << endl;

	delete[] xi;
	readyEncodeBuffer->clear();
	this->sigma = 0;
	this->beta = 0;
	this->alpha = 0;
	this->curDictinctPoolNum = 0;
	delete[] dictinctPool;
	delete[] keyPool;
	dictinctPool = new int[this->definitionalDomainSize];
	keyPool = new int[this->definitionalDomainSize];
}

void IntFunctionEncoder::calculatelsm(int length, int* x, int* y, int& beta, int& alpha)
{
	
	int x_sum = 0;
	int y_sum = 0;
	int xy_sum = 0;
	int x_square_sum = 0;
	for (int i = 0; i < length; i++) {
		x_sum += x[i];
		y_sum += y[i];
		xy_sum += x[i]* y[i];
		x_square_sum += x[i] * x[i];
	}
	int x_mean = x_sum / length;
	int y_mean = y_sum / length;
	beta = (xy_sum - length * x_mean * y_mean) / (x_square_sum - length*x_mean*x_mean);
	alpha = y_mean - x_mean * beta;

}
