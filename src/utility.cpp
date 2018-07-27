#include "utility.h"

void toByteArray(int n, char result[4]) {
	result[0] = n & 0xff;
	result[1] = (n>>8)  & 0xff;
	result[2] = (n>>16) & 0xff;
	result[3] = (n>>24) & 0xff;
}