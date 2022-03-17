// string-to-integer.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <vector>

using std::string;

enum class StateType
{
	q0 = 0,
	q1,
	q2,
	qd
};

class StateMachine
{
	public:
		StateMachine() : state(StateType::q0), number(0), sign(1)
		{

		};

		void Clear()
		{
			state = StateType::q0;
			number = 0;
			sign = 1;
		}

		int getNumber() const
		{
			return number;
		};

		StateType getState() const
		{
			return state;
		};

		bool isDigit(char c)
		{
			return (c >= '0' && c <= '9');
		}

		bool isSign(char c)
		{
			return ((c == '+') || (c == '-'));
		}

		bool isOverflow(int digit)
		{
			return ((number > INT_MAX / 10) || (number == INT_MAX / 10 && digit > INT_MAX % 10));
		}

		void toQd()
		{
			number *= sign;

			state = StateType::qd;
		}

		void addToNumber(int digit)
		{
			if (isOverflow(digit))
			{
				number  = (sign == -1) ? INT_MIN : INT_MAX;

				//toQd();
				state = StateType::qd;
			}
			else
			{
				number = number * 10 + digit;
			}
		}

		void transition(char c)
		{
			switch (state)
			{
				case StateType::q0:
				{
					if (isSign(c))
					{
						sign = (c == '-') ? -1 : 1;
						state = StateType::q1;
					}
					else
					{
						if (isDigit(c))
						{
							int digit = c - '0';
							addToNumber(digit);
							state = StateType::q2;
						}
						else
						{
							if(c != ' ')
								toQd();
						}
					}
				}break;

				case StateType::q1:
				{
					if (isDigit(c))
					{
						int digit = c - '0';
						addToNumber(digit);
						state = StateType::q2;
					}
					else
					{
						toQd();
					}
				}break;

				case StateType::q2:
				{
					if (isDigit(c))
					{
						int digit = c - '0';
						addToNumber(digit);
					}
					else
					{
						toQd();
					}
				}break;
			}
		}

	private:
		StateType state;
		int number;
		int sign;
};

int myAtoi(string s)
{
	StateMachine machine;

	for (int i = 0; machine.getState() != StateType::qd; i++)
	{
		machine.transition(s[i]);
	}

	return machine.getNumber();
}

int main()
{
	std::vector<std::string> strings =
	{
		"-2147483647",
		"",
		"0032",
		"       -56",
		"42",
		"-42",
		"+-12",
		"2147483646",
		"        123     asdasd    345",
		"        +-123 sadasd   "
	};

	for (std::string& str : strings)
	{
		std::cout << myAtoi(str) << std::endl;
	}

	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
