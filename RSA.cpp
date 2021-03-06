/* Implementation of RSA cryptosystem
 * includes custom made functions for the Extended Euclidean Algorithm, modular inverse, and relative primes.
 * Prompts user to enter message for encryption.
 */

#include <iostream>
#include <math.h>
#include <assert.h>
using namespace std;

int EuclidAlgGCD(int a, int b)
{
	/* precondition: a >= b >= 0
	 * postcondition: return gcd(a,b) */

	int d, r;

	if (b == 0)
		d = a;
	else
	{
		r = a % b;
		d = EuclidAlgGCD(b, r);
	}
	return d;

}
int ExtendedEuclidAlgGCD(int a, int b, int &s, int &t)
{
	/* precondition: a>=b>=0
	 * postcondition: return d=gcd(a,b), s and t are set so that d=sa+tb */
	 
	int d, r, x, y;
	
	if(b == 0)
	{
		s = 0;
		t = 1;
		d = a;
	}
	else
	{
		r = a % b;
		d = ExtendedEuclidAlgGCD(b, r, x, y);
		s = y - (a/b) * x;
		t = x;
	}
	return d;
	
}
int mod(int a, int n)
{
	/* precondition: n is greater than 1, a can be negative
	 * postcondition: return a mod n
	 *	a mod n = r if and only if a = nk+r, 0 <= r < n */
	int r = a % n;
	if (r < 0)
		r += n;
	return r;
}
int inverse(int a, int n)
{
	int s, t;
	int d = ExtendedEuclidAlgGCD(n, a, s, t);
	return (mod(s, n));	
}
bool IsPrime(int n)
{
	/* precondition: n > 1
	 * postcondition: return true if n is prime, false if n is not prime */

	bool prime = true;	
	int i = 2, s = sqrt(n);

	while (prime == true && i <= s)
	{
		if (n%i == 0)
			prime = false;
		i++;
	}
	return prime;
}
int RelativelyPrime(int n)
{
	bool found = false;
	int i = 2;
	while(found == false)
	{
		if((EuclidAlgGCD(n, i) == 1) && (i != (n-1)))
			found = true;
		else
			i++;
	}
	return i;
}
int Encode(int M, int e, int PQ)
{
	int Me = pow(M, e);
	return (mod(Me, PQ));	
}
int Decode(int C, int d, int PQ)
{
	int Cd = pow(C, d);
	return (mod(Cd, PQ));
}

char NumtoChar(int num)
{
	char c = num;
	return c;
}
int ChartoNum(char c)
{
	int n = c;
	return n;
}
int main()
{

	// CALCULATE VALUES FOR RSA
	const int P = 7, Q = 3; // since variables are integer based, small values work best for P and Q.
        int PQ = P*Q;
        int relp = (P-1) * (Q-1);
        int e = RelativelyPrime(relp);
        int d = inverse(e, relp);	
	bool quit = false;
	char tempC;
	int tempI;
	string M, C, Ptext;

	cout << "Enter a message : ";
	cin  >> M;
	int length = M.length();
	cout << "******************************" << endl;
	// ENCODE MESSAGE
	for(int i = 0; i < length; i++)
	{
		tempC = M.at(i);
		if(tempC >= 'a' && tempC <= 'z') //accept only lowercase letters
		{
			tempI = ChartoNum(tempC) - 96; //keep numbers in 1-26 range;
			tempI = Encode(tempI, e, PQ);
			tempI = mod(tempI, 26);
			tempC = NumtoChar(tempI+96);
			C += tempC;
		}
	}
	cout << "CIPHERTEXT: "<< C << endl;

	//DECODE CIPHERTEXT
	for(int i = 0; i < length; i++)
	{
                tempC = C.at(i);
                if(tempC >= 'a' && tempC <= 'z') //accept only lowercase letters
                {
                        tempI = ChartoNum(tempC) - 96; //keep numbers in 1-26 range;
                        tempI = Decode(tempI, d, PQ);
                        tempI = mod(tempI, 26);
                        tempC = NumtoChar(tempI+96);
                        Ptext += tempC;
                }
        }
        cout << "DECODED MESSAGE: " << Ptext << endl;
	cout << "******************************" << endl;
}
