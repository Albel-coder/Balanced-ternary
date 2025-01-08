#include <iostream>
#include <Windows.h>
#include <fstream>
#include <thread>
#include <stdio.h>
#include <cstdlib>

using namespace std;

int CheckInput(const char* msg)
{
	string tmp;
	int value;
	while (true)
	{
		cout << msg;
		cin >> tmp;
		try
		{
			value = stoi(tmp);
			cin.ignore((numeric_limits<unsigned char>::max)(), '\n');
			return value;
		}
		catch (invalid_argument)
		{
			cin.clear();
			cin.ignore(cin.rdbuf()->in_avail());
		}
		catch (out_of_range)
		{
			cin.ignore((numeric_limits<unsigned char>::max)(), '\n');
		}
	}
}
void ConvertDecimal(unsigned long int x, unsigned short Base)
{
	int i = 0;
	ofstream out;
	out.open("save.txt");
	if (out.is_open())
	{
		while (x > 0)
		{
			out << x % Base << " ";
			x /= Base; i++;
		}
	}
	out.close(); i++;
	short* array = new short[i];
	for (int j = 0; j < i; j++)
		array[j] = 0;
	ifstream in;
	in.open("save.txt");
	if (in.is_open())
	{
		for (int j = i - 1; j >= 0; j--)
			in >> array[j];
	}
	in.close();
	bool tmp = 0;
	while (true)
	{
		for (int j = i - 1; j >= 0; j--)
		{
			if (array[j] > (Base - 1) / 2)
			{
				tmp++;
				array[j] -= Base;
				array[j - 1]++;
			}
		}
		if (!tmp)
			break;
		tmp = 0;
	}
	if (array[0] != 0)
		cout << array[0] << " ";
	for (int j = 1; j < i; j++)
		cout << array[j] << " ";
	cout << "\n";
	remove("save.txt");
}
int main()
{
	bool t;
	t = CheckInput("Enter 0 to convert decimal to balanced ternary\nEnter 1 to convert balenced ternary\n");
	int base = 3;	
	while (true)
	{
		base = CheckInput("Enter the base of balanced ternary\n");
		if (base % 2 == 1)
			break;
		else
			cout << "Base must be odd\n";
	}
	if (t)
	{
		int j = 0; cout << "Enter through space odds of balenced ternary\nEnter " << (base + 1) / 2 << " to end input\n";
		short a;
		ofstream out;
		out.open("Odds.txt");
		if (out.is_open())
		{
			while (true)
			{
				cin >> a;
				if (a > (base - 1) / 2 || a < (1 - base) / 2)
				{
					break;
				}
				out << a << " ";
				j++;
			}
		}
		out.close();
		short* array = new short[j];
		ifstream in("Odds.txt");
		if (in.is_open())
		{
			for (int i = 0; i < j; i++)
				in >> array[i];
		}
		in.close();
		remove("Odds.txt");
		//ConvertBalancedTernary(array, j, base);
	}
	else
	{		
		unsigned long int k = CheckInput("Enter number\n");
		ConvertDecimal(k, base);
	}
	return 0;
}