#include "stdafx.h"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int isNotAlphaNum(char c)
{
	return !isalnum(c);
}

bool isNumeric(string s)
{
	string::const_iterator it = s.begin();
	while (it != s.end() && isdigit(*it)) ++it;
	return !s.empty() && it == s.end();
}

string convertDigit(int number, int place)
{
	string builtResult = "";
	string I = "I";
	string V = "V";
	string X = "X";

	switch (place)
	{
	case 1:{
			   break;
	}
	case 2:{
			   I = "X";
			   V = "L";
			   X = "C";
			   break;
	}
	case 3:{
			   I = "C";
			   V = "D";
			   X = "M";
			   break;
	}
	case 4:{
			   I = "M";
			   V = "";
			   X = "";
			   break;
	}
	}
	if (number < 4)
	{
		for (int i = 0; i < number; i++)
		{
			builtResult += I;
		}
	}
	else if (place == 4 && number >= 4)
	{
		for (int i = 0; i < number; i++)
		{
			builtResult += I;
		}
	}
	else if (number == 4)
	{
		builtResult = I + V;
	}
	else if (number > 4 && number < 9)
	{
		builtResult += V;
		for (int i = 0; i < number % 5; i++)
		{
			builtResult += I;
		}
	}
	else
	{
		builtResult = I + X;
	}
	return builtResult;
}

int main()
{
	bool bRunning = true;
	while (bRunning)
	{
		string input;
		std::cout << "Please enter a Roman numeral or a whole integer: ";
		cin >> input;

		string untreatedInput = input;
		input.erase(std::remove_if(input.begin(), input.end(), isNotAlphaNum), input.end());

		if (isNumeric(input))
		{
			if (stoi(input) > 9999 || stoi(input) < 1 || untreatedInput.find("-") != std::string::npos)
			{
				std::cout << "Sorry, only numbers between 1 & 10000." << endl << endl;
			}
			else
			{
				string sResult;
				int dec = input.size() - 1;
				while (dec >= 0)
				{
					int nNumber = input[dec] - 48;
					sResult = convertDigit(nNumber, input.size() - dec) + sResult;
					dec--;
				}
				std::cout << "Roman numeral conversion: " << sResult << endl << endl;
			}
		}
		else
		{
			int nResult = 0;
			vector<int> conversion;
			bool bInvalidCharacter = false;

			for (int i = 0; i < input.length(); i++)
			{
				input[i] = toupper(input[i]);
				switch (input[i])
				{
				case 'I':{
							 conversion.push_back(1);
							 break;
				}
				case 'V':{
							 conversion.push_back(5);
							 break;
				}
				case 'X':{
							 conversion.push_back(10);
							 break;
				}
				case 'L':{
							 conversion.push_back(50);
							 break;
				}
				case 'C':{
							 conversion.push_back(100);
							 break;
				}
				case 'D':{
							 conversion.push_back(500);
							 break;
				}
				case 'M':{
							 conversion.push_back(1000);
							 break;
				}
				default:{
							bInvalidCharacter = true;
							break;
				}
				}
			}

			if (bInvalidCharacter)
			{
				std::cout << "Sorry, invalid Roman numeral characters detected. Try again." << endl << endl;
			}
			else
			{
				int ic = 0;
				int previous = 0;
				int subtotal = 0;
				while (ic < conversion.size())
				{
					if (ic == 0 || conversion[ic] == previous)
					{
						subtotal += conversion[ic];
					}

					else if (conversion[ic] > previous)
					{
						nResult += conversion[ic] - subtotal;
						subtotal = 0;
					}

					else if (conversion[ic] < previous)
					{
						nResult += subtotal;
						subtotal = conversion[ic];
					}

					if (ic == conversion.size() - 1)
					{
						nResult += subtotal;
					}

					previous = conversion[ic];
					ic++;
				}
				std::cout << "Integer conversion: " << nResult << endl << endl;
			}
		}
	}
}