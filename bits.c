/*  * CS:APP Data Lab 
 * 
 * Stefán Hafsteinsson, stefanh13
 * 
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.  
 */

#if 0
 
  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>
    
  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

FLOATING POINT CODING RULES

For the problems that require you to implent floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to 
     check the legality of your solutions.
  2. Each function has a maximum number of operators (! ~ & ^ | + << >>)
     that you are allowed to use for your implementation of the function. 
     The max operator count is checked by dlc. Note that '=' is not 
     counted; you may use as many of these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the btest checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies 
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the btest checker to formally verify that your solutions produce 
 *      the correct answers.
 */


#endif
/* 
 * tmin - return minimum two's complement integer 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmin(void) {

	//Move 1 to the mostsigificant bit.
	return 1 << 31;
}
/*
 * isTmax - returns 1 if x is the maximum, two's complement number,
 *     and 0 otherwise 
 *   Legal ops: ! ~ & ^ | +
 *   Max ops: 10
 *   Rating: 1
 */
int isTmax(int x) {

	int maybeTmax;

	//If x isTmax, set to Tmin, overflow it and set again to Tmax.
	maybeTmax = ~x + ~0;

	//Check if maybeTmax is equal to x and also check if x is -1
	// because that will kill the test above.
	return (!(maybeTmax ^ x)) & (!!(x ^ ~0));
}
/*
 * bitAnd - x&y using only ~ and | 
 *   Example: bitAnd(6, 5) = 4
 *   Legal ops: ~ |
 *   Max ops: 8
 *   Rating: 1
 */
int bitAnd(int x, int y) {
	//DeMorgans
	return ~(~x | ~y);
}

/* upperBits - pads n upper bits with 1's
 *  You may assume 0 <= n <= 32
 *  Example: upperBits(4) = 0xF0000000
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 10
 *  Rating: 1
 */
int upperBits(int n) {

	int shift;
	int checkIfZero;

	//shift = -n
	shift = ~n + 1;

	//This variable will be set as zero if n = 0. If n!=0, then create
	//a mask for upperBits
	checkIfZero = !n + (~1 + 1);

	//	Mask the upperbits	shift them 32 - n
	return (~0 & checkIfZero)  << ( 32 + shift);

}
/* 
 * isEqual - return 1 if x == y, and 0 otherwise 
 *   Examples: isEqual(5,5) = 1, isEqual(4,5) = 0
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int isEqual(int x, int y) {

	//If x == y, xor will return 0.
	return !(x ^ y);
}
/* 
 * divpwr2 - Compute x/(2^n), for 0 <= n <= 30
 *  Round toward zero
 *   Examples: divpwr2(15,1) = 7, divpwr2(-33,4) = -2
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
int divpwr2(int x, int n) {

	int checkSign;
	int fix;

	//For special case if x is negative.
	checkSign = x >> 31;

	//Create a mask that will that will raise x so that it will round
	//right when x is negative.
	fix = (1 << n) + ~0;

	//Add new number to x if x is negative, then divide.
	return (x + (checkSign & fix)) >> n;
}
/* 
 * byteSwap - swaps the nth byte and the mth byte
 *  Examples: byteSwap(0x12345678, 1, 3) = 0x56341278
 *            byteSwap(0xDEADBEEF, 0, 2) = 0xDEEFBEAD
 *  You may assume that 0 <= n <= 3, 0 <= m <= 3
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 25
 *  Rating: 2
 */
int byteSwap(int x, int n, int m) {

	int nthByte;
	int mthByte;
	int nMask;
	int mMask;
	int moveN;
	int moveM;
	int mask;

	mask = 0 | 0xFF;
	//n*3
	moveN = n << 3;

	//m*3
	moveM = m << 3;

	//Get the nth byte and set it where the mth byte was.
	nthByte = (0 | ((x >> (moveN)) & 0xFF)) << (moveM);

	//Get the mth byte and set it where the nth byte was.
	mthByte = (0 | ((x >> (moveM)) & 0xFF)) << (moveN);

	//Create masks to turn off bits where nth and mth byte were.
	nMask = ~(mask  << (moveN));
	mMask = ~(mask << (moveM));

	x = (((x & nMask) & mMask)) | nthByte | mthByte;

	return x;
}
/* 
 * anyOddBit - return 1 if any odd-numbered bit in word set to 1
 *   Examples anyOddBit(0x5) = 0, anyOddBit(0x7) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */
int anyOddBit(int x) {

	int mask;

	mask = 0;

	//Create a mask that will check if x is anyOddBit
	mask = (mask | 0xaa) << 24;
	mask = (mask | 0xaa << 16);
	mask = (mask | 0xaa << 8);
	mask = (mask | 0xaa);

	//If x masked xor-ed with 0 is not 0, then x has Oddbit.
	return !!(mask & x) ^ 0;
}
/* 
 * isGreater - if x > y  then return 1, else return 0 
 *   Example: isGreater(4,5) = 0, isGreater(5,4) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isGreater(int x, int y) {
	int xSign;
	int ySign;
	int check1;
	int check2;
	int sum;

	//Check sign of x.
	xSign = (x >> 31) & 1;

	//Check sign of y.
	ySign = (y >> 31) & 1;

	// x - y
	sum = x + ~y;

	//If signs of x and y are the same then I also have to check
	//the sign of the sum.
	check1 = (!(xSign ^ ySign)) & (sum >> 31); 

	//Check if signs are not equal.
	check2 = (!ySign) & xSign;

	//if both checks are false then x is greater then y.
	return !(check1) & (!check2);
}
/* 
 * logicalShift - shift x to the right by n, using a logical shift
 *   Can assume that 0 <= n <= 31
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3
 */
int logicalShift(int x, int n) {

	int shiftX;
	int mask;

	shiftX = x >> n;

	//Create a mask using the upperBits logic.
	mask = (~0 & (!n + (~1 + 1))) << (32 + (~n + 1));

	//Turn of bits if x was negative.
	return shiftX & ~mask;
}
/* 
 *  isAsciiDigit - return 1 if 0x30 <= x <= 0x39 (ASCII codes for characters '0' to '9')
 *   Example: isAsciiDigit(0x35) = 1.
 *            isAsciiDigit(0x3a) = 0.
 *            isAsciiDigit(0x05) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 3
 */
int isAsciiDigit(int x) {
	int firstFourLegal;
	int lastFourLegal;

	//Check if second hex is 3
	firstFourLegal = !((x >> 4) ^ 3);

	//If first hex has 4th bit 0 it is from 0-7
	//if middle 2 bits in the first hex, then it is 8 or 9.
	lastFourLegal = (!((x & 0x8) ^ 0)) | (!((x & 0x6) ^ 0));


	return firstFourLegal & lastFourLegal;
}
/* 
 * subOK - Determine if possible to compute x-y without overflow
 *   Example: subOK(0x80000000,0x80000000) = 1,
 *            subOK(0x80000000,0x70000000) = 0, 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3
 */
int subOK(int x, int y) {
	int isSignSame;
	int xSign;
	int ySign;
	int subSign;

	//Get signs of x and y.
	xSign = x >> 31;
	ySign = y >> 31;

	//Get sign of x - y
	subSign = (x + ~y + 1) >> 31;

	//Check if sign of x and y is the same.
	isSignSame = (xSign ^ ySign);

	//			Check if x has same sign as x-y
	return !(isSignSame & (subSign ^ xSign));
}
/* 
 * isNonZero - Check whether x is nonzero using
 *              the legal operators except !
 *   Examples: isNonZero(3) = 1, isNonZero(0) = 0
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 10
 *   Rating: 4 
 */
int isNonZero(int x) {
	int checkIfZero;

	//This will only return zero if x = 0.
	checkIfZero = x | (~x + 1);

	//If x != the MSB is 1.
	return (checkIfZero  >> 31) & 1 ;
}
/* 
 * logicalNeg - implement the ! operator, using all of 
 *              the legal operators except !
 *   Examples: logicalNeg(3) = 0, logicalNeg(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4 
 */
int logicalNeg(int x) {
	int checkIfZero;

	//Same method as above to check if x contains any i bit.
	checkIfZero = x | (~x + 1);

	//Return 0 if x has any 1 bit.
	return ~(checkIfZero >> 31) & 1;
}
/* 
 * float_abs - Return bit-level equivalent of absolute value of f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representations of
 *   single-precision floating point values.
 *   When argument is NaN, return argument..
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 10
 *   Rating: 2
 */
unsigned float_abs(unsigned uf) {

	int exp;
	int mantissa;

	//Get mantissa and exponent of uf
	mantissa = uf &  0x007fffff;
	exp = (uf >> 23) & 0xff;

	//If NaN
	if(mantissa != 0 && exp == 0xff){

		return uf;
	}
	//Else return regular uf with most significant turned off.
	else return uf &  0x7fffffff;
}
/* 
 * float_half - Return bit-level equivalent of expression 0.5*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned float_half(unsigned uf) {

	int mant;
	int exp;
	int sign;
	int shiftMant;

	//Single out mantissa, sign and exponent of uf.
	mant = uf & 0x007fffff;
	sign = uf & 0x80000000;
	exp = uf & 0x7f800000;

	//shiftMant checks if the two least signifancts bits are turned on.
	//If they are, then add 1 to the mantiss.
	shiftMant = (mant + (!((0x3 & mant) ^ 0x3))) >> 1;


	//Check the special case.
	if((exp >> 23) == 0xff){
		return uf;
	}
	//Check if exponent is 1.
	else if(!((exp >> 23)^1)){

		//Switch to denormalized float from normalized and put
		//the numer together again.
		return sign | 1 << 22 | shiftMant;
	}
	//Check if exponent is 0.
	else if(exp == 0){

		//Then do as above but we don't have to switch to denormalized
		return sign | shiftMant;
	}
	//Normal case
	else{
		//decrease exponent by 1 and put together the number again.
		return sign | ((exp + ~0) & 0x7f800000) | mant;
	}
}
/* 
 * float_i2f - Return bit-level equivalent of expression (float) x
 *   Result is returned as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point values.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned float_i2f(int x) {
  return 2;
}
