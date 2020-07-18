/* Implementation of encryption and decryption using the Affine Cipher
 * Includes self-made functions for modulus, the Extended Euclidean Algorithm, and modular inverse
 * Prompts user through terminal based UI menu options
 */

#include <iostream>
#include <string>
using namespace std;

int mod(int a, int n)
{
        // function calculates a mod n, can handle negative integers
        int r = a % n;
        if (r < 0)
                r += n;
        return r;
};
string Encrypt(string plaintext, int a, int b)
{
	/* precondition: key values a and b must be valid, plaintext string can contain any characters
	 * postcondition: plaintext string is parsed and relevant characters are encrypted. Ciphertext string is returned
	 */
	int i, x, y, length = plaintext.length();
	string ciphertext = "";
	char pChar, cChar;

	for (int i = 0; i < length; i++)
	{
		pChar = plaintext.at(i);
		if(pChar >= 65 && pChar <= 90)
			x = pChar - 65; // convert ASCII value of letter to 0-25 for A-Z 
		else if(pChar >= 97 && pChar <= 122)
			x = pChar - 97;
		else
			x = -1;
		if (x >= 0 && x <= 25) // ignore any characters that aren't A-Z
		{
			y = ((a*x) + b);
			y = mod(y, 26);
			cChar = y + 65; // convert 0-25 value of letter to ASCII value
			ciphertext.push_back(cChar);
		}
	}
	return ciphertext;
};
int ExtendedEuclidAlg(int a, int b, int&s, int &t)
{
        /* precondition: a>=b>=0
         * postcondition: return d=gcd(a,b), s and t are set so that d=sa+tb
         *                therefore s will be the multiplicative inverse of b*/

        int d, r, x, y; // d is GCD of a and b. r is remainder, x and y are coefficients of remainder and divisor.

        if(b == 0) //base case, gcd of any # and 0 is 0
        {
                s = 0;
                t = 1;
                d = a;
        }
        else
        {
                r = a % b; // r is remainder of a and b
                d = ExtendedEuclidAlg(b, r, x, y); // calculate gcd using new remainder as divisor.
                s = y - (a/b) * x; 
                t = x;
        }
        return d;
};
int InverseOfA(int a)
{
        int ai, d, t; //ai is the inverse of a, and d = 26(ai) + at
	d = ExtendedEuclidAlg(26, a, ai, t); //use Euclidean Algorithm to calculate ai 
	ai = mod(ai, 26); 
	return ai;
};
string Decrypt(string ciphertext, int a, int b)
{  /* precondition: key values a and b are valid. Ciphertext can be any string.
    * postcondition: relevant characters are decrypted, decryption string is returned
    */
	int i, x, y, length = ciphertext.length(), ai = InverseOfA(a);
	string decryption = "";
	char cChar, dChar;
	for (int i = 0; i < length; i++)
	{
		cChar = ciphertext.at(i);
		if(cChar >= 65 && cChar <= 90)
                        y = cChar - 65; // convert ASCII value of letter to 0-25 for A-Z 
                else if(cChar >= 97 && cChar <= 122)
                        y = cChar - 97;
		else
			y = -1;
		if (y >= 0 && y <= 25)
		{
			x = (ai*(y - b));
		        x = mod(x, 26);	
			dChar = x + 65;
			decryption.push_back(dChar);
		}
	}
	return decryption;
};

int main()
{
	int a=5, b=12, menu = 0; //placeholder values
	bool valid = false;
	cout << endl << "\e[1;36m *** AFFINE CIPHER ***" << endl;
	while (menu != 5)
	{ //MAIN MENU
		cout << endl;
		cout << "\e[4;31m     MAIN MENU       \e[0m" << endl;
		cout << "\e[36m 1.\e[37m Change key values"  << endl;
		cout << "\e[36m 2.\e[37m View key values"    << endl;
		cout << "\e[36m 3.\e[37m Encrypt a message"  << endl;
		cout << "\e[36m 4.\e[37m Decrypt a message"  << endl;
		cout << "\e[36m 5.\e[37m Quit \e[0m"		<< endl;
		cout << endl << "\e[31mEnter menu option : ";
		cin >> menu;
		cout << endl;

		string plaintext, ciphertext, decryption;

		if(menu == 1)
		{ // MENU CHOICE 1: CHANGE KEY VALUES
			cout <<"\e[4;31m CHANGE KEY VALUES \e[0m" << endl;
			valid = false;
			while (valid == false)
			{
				cout << "\e[37mEnter an integer for '\e[36ma\e[37m' of the key : ";
				cin >> a;
				cout << "\e[37mEnter an integer for '\e[36mb\e[37m' of the key : ";
				cin >> b;
				cout << endl;
				int s, t, d = ExtendedEuclidAlg(26, a, s, t); //use Euclidean Alg to ensure a and 26 are relatively prime
				if((b >= 0 && b <= 25) && (a >= 0 && a <= 25) && (d == 1)) // if key values are in range and a is relatively prime to 26
				{
					valid = true;
				}
				else
					cout << "\e[33mINVALID KEY" << endl;
			}
		}
		else if(menu == 2)
		{ //MENU CHOICE 2 : VIEW KEY VALUES
			cout << "\e[4;31m    KEY VALUES    \e[0m " << endl;
			cout << "\e[36m a\e[37m =\e[36m " << a << endl;
			cout << " b\e[37m =\e[36m " << b << endl;
			cout << " inverse of a\e[37m = \e[36m" << InverseOfA(a) << endl;
		}
		else if(menu == 3)
		{ //MENU CHOICE 3 : ENCRYPT A MESSAGE
			cout <<"\e[4;31m ENCRYPT PLAINTEXT \e[0m" << endl;
			cin.ignore();
			cout << "\e[37mEnter a message : ";
			getline(cin,plaintext);
			ciphertext = Encrypt(plaintext, a, b);
			cout << "\e[36mENCRYPTION : " << ciphertext << endl;
		}
		else if(menu == 4)
		{ //MENU CHOICE 4 : DECRYPT A MESSAGE
			cout <<"\e[4;31m DECRYPT CIPHERTEXT \e[0m" << endl;
			cin.ignore();
			cout << "\e[37mEnter ciphertext : ";
			getline(cin, ciphertext);
			decryption = Decrypt(ciphertext, a, b);
			cout << "\e[36mDECRYPTION : " << decryption << endl;
		}
	}
	cout << "Thanks for using the Affine Cipher ! " << endl;
};
