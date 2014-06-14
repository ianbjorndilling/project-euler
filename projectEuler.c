/*
 * projectEuler.c
 *
 *  Created on: Apr 3, 2014
 *      Author: IanDilling
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

/**
 * |------------------- Problem 1 ----------------------|
 */
int sumOfMutliples(int num1, int num2, int threshold) {
	int min, rem1, rem2;

	min = (num1 <= num2) ? num1 : num2;
	threshold--;

	if (threshold <= min)
		return 0;

	rem1 = threshold % num1;
	rem2 = threshold % num2;
	threshold -= (rem1 <= rem2) ? rem1 : rem2;
	return threshold + sumOfMutliples(num1, num2, threshold);
}

/**
 * |------------------- Problem 2 ----------------------|
 */
long evenFibSum(int max) {
	int i = 1, j = 2;
	long sum = 0;
	while (j <= max) {
		if (j%2 == 0)
			sum += j;

		j = j + i;
		i = j - i;
	}
	return sum;
}

/**
 * |------------------- Problem 3 ----------------------|
 */
long largestPrime(long num) {

	for (long i=2; i < (long)sqrt(num)+1; i++) {

		if (num%i == 0) {

			return largestPrime(num/i);

		}

	}

	return num;

}

/**
 * |------------------- Problem 4 ----------------------|
 */

/**
 * A very interesting reverse string function I found using an XOR swap.
 * reference - http://stackoverflow.com/questions/784417/reversing-a-string-in-c
 */
void reverseString(char *str) {

	if (str) {
	    char * end = str + strlen(str) - 1;

	    // swap the values in the two given variables
	    // XXX: fails when a and b refer to same memory location
		#define XOR_SWAP(a,b) do {\
	      a ^= b;\
	      b ^= a;\
	      a ^= b;\
	    } while (0)

	    // walk inwards from both ends of the string,
	    // swapping until we get to the middle
	    while (str < end) {
			XOR_SWAP(*str, *end);
			str++;
			end--;
	    }
		#undef XOR_SWAP
	}

}

int largestPalendromeProduct(int digits) {

	int largest,smallest = 0;
	int final = 0;
	smallest = (int)pow(10, digits-1);

	for (int i = digits-1; i >=0; i--)
		largest = largest + 9*(int)pow(10, i);

	for (int i = largest; i >= smallest; i--) {

		for (int j = i; j >= smallest; j--) {

			int prod = i*j;
			char str[15];
			char rev[15];
			sprintf(str, "%d", prod);
			strcpy(rev, str);
			reverseString(str);

			if(strcmp(str, rev) == 0)
				final = (prod > final) ? prod : final;

		}

	}

	return final;

}

/**
 * |------------------- Problem 5 ----------------------|
 */

// parameters of type long must be used to avoid overflow.
long gcd(long a, long b) {
	if (b == 0)
		return a;
	else
		return gcd(b, a % b);
}

long lcm(long a, long b) {
	return (a*b)/gcd(a,b);
}

/**
 * Returns the lcm of every number from 1 to the specified range.
 * The function is iterative because so can be as efficient as a recursive solution
 * without adding an extra parameter.
 */
long smallestMultiple(int range) {
	int stop = range/2;
	long l = range;
	while (range > stop) {
		l = lcm(--range, l);
	}
	return l;
}

/**
 * Returns the lcm of every number from parameter 1 to parameter 2.
 * I added this here because I wanted make recursive solution that could solve the same
 * problem. You have to specify a minimum in this solution. For this problem, the optimal minimum would
 * be 11. Any higher and you would get a wrong answer, any lower and the function would do useless recursion.
 *
 * No overloading in C :-(
 */
long smallestMultipleInRange(int min, int max) {
	if (max == min)
		return min;
	else
		return lcm(smallestMultipleInRange(min, max - 1), max);
}

/**
 * |------------------- Problem 7 ----------------------|
 */
int nthPrime(int n) {

	int primes[n];
	int index = 0;
	int num = 2;
	primes[0] = num;

	while (index < n-1) {

		int bool = 1;
		num++;

		for (int i = 0; i <= index; i++) {

			if (num % primes[i] == 0) {

				bool = 0;
				break;

			}

		}

		if (bool) {

			index++;
			primes[index] = num;

		}

	}

	return primes[index];


}


/**
 * |------------------- Problem 8 ----------------------|
 */
int greatestConsecDigProduct (char *num, int consec) {

	int len = strlen(num);
	int greatestConsec = 1;

	if (len > consec) {

		for (int i = 0; i <= len - consec; i++) {

			int temp = 1;

			for (int c = 0; c < consec; c++)
				temp *= (int)num[i+c] - 48; //ascii decimal integer for char 0

			if (temp > greatestConsec)
				greatestConsec = temp;

		}

	}

	return greatestConsec;

}
/**
 * |------------------- Problem 9 ----------------------|
 */
int pythagoreanTripletProduct(int targetSum) {

	for (int c = 3; c < targetSum-1; c++) {

		for (int b = 2; b < c; b++) {

			for (int a = 1; a < b; a++) {

				if (a+b+c == targetSum && a*a + b*b == c*c) {

					return a*b*c;

				}

			}

		}

	}

	return 0;

}

/**
 * |------------------- Problem 10 ----------------------|
 */

/**
 * Currently No solution for this problem... yet.
 */

/**
 * |------------------- Problem 11 ----------------------|
 */

/**
 * I solved this problem by breaking down the 20x20 matrix into several 4x4 matricies.
 * The maximum value from each cube is stored in a variable and then it increments 1 space over
 * and does it all over again.
 * Unfortunatley, there is no input abstraction in this answer. The input matrix must be a filled 20x20 matrix.
 */
int largestMatrixProduct(int matrix[20][20]) {
	int m[4][4];
	int y, x;
	int i, k, j, d;
	int prods[4]; // 0 - diag1, 1 - diag2, 2 - horiz, 3 - virt
	int max = 0, maxprod2 = 0, maxprod3 = 0;

	// > enter loop hell
	for (i = 0; i <= 16; i++) {
		for (k = 0; k <= 16; k++) {
			y = 0;
			prods[0] = 1, prods[1] = 1, prods[2] = 1, prods[3] = 1;
			for (j = i; j < i+4; j++) {
				x = 0;
				for (d = k; d < k+4; d++) {
					m[y][x++] = matrix[j][d];
				}
				y++;
			}
			for (j = 0; j < 4; j++) {
				prods[0] *= m[j][j];
				prods[1] *= m[j][3-j];
				for (d = 0; d < 4; d++) {
					prods[2] *= m[j][d];
					prods[3] *= m[d][j];
				}
				if (prods[2] > maxprod2) maxprod2 = prods[2];
				if (prods[3] > maxprod3) maxprod3 = prods[3];
				prods[2] = 1; prods[3] = 1;
			}

			prods[2] = maxprod2; prods[3] = maxprod3;
			for (j = 0; j < 4; j++) {
				if (prods[j] > max) {
					max = prods[j];
				}
			}

		}
	}

	return max;
}

/**
 * changes the string of integers from problem 11 into a 2d array. Spaces must be between each integer in the string.
 */
void toIntMatrix(char *numString, int matrix[20][20]) {
	int i, j;
	char c;
	for (i = 0; i < 20; i++) {
		for (j = 0; j < 20; j++) {
			char charInt[4] = "\0";
			int res;

			c = numString[0];
			while(!isspace(c)) {
				int len = strlen(charInt);
				c = *numString++;
				charInt[len++] = c;
				charInt[len] = '\0';
			}

			sscanf(charInt, "%d", &res);
			matrix[i][j] = res;
		}
	}
}

int main () {
	printf("%d\n", pythagoreanTripletProduct(1000));
	return 0;


}
