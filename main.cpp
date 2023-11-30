/******************************************************************************
* Author:		Patrick Foster
* Date:			4/20/2022
* 
* Description:	This program generates two random numbers and asks the user
*               for an asnwer. If the user gets the answer right, they are
*               congratulated. If the user gets the answer wrong, they are
*               shown the right answer.
* 
* Inputs:       The user chooses between options.
*               The user enters the answer.
* 
* Output:       Program messages will output tot the screen.
*               The problem and the answer will output to the screen.
******************************************************************************/
#include <iostream>
#include <iomanip>
#include <random>
#include <string>

using namespace std;

void createAdditionProblem(int numOneDigits, int numTwoDigits);
void createSubtractionProblem(int numOneDigits, int numTwoDigits, bool allowNegative);
void createMultiplicationProblem(int numOneDigits, int numTwoDigits);
void createDivisionProblem(int numOneDigits, int numTwoDigits);
void createDivisionRemainderProblem(int numOneDigits, int numTwoDigits);
void createOrderOfOperationsProblem(int numOneDigits, int numTwoDigits, int numThreeDigits);
void displayProblem(int numberOne, int numberTwo, char symbol, int answer, bool showAnswer = false, bool withRemainder = false, int remainder = 0);
void checkAnswer(int userAnswer, int correctAnswer, bool withRemainder = false, int userRemainder = 0, int correctRemainder = 0);
void playAgainMessage(int& currentState);
void showTitle(string titleName);
void showSettings(int& numOneDigits, int& numTwoDigits, int& numThreeDigits, bool& allowNegative, int& currentState);
void addGap();
void addMargin();
void addSpaces(int numSpaces);
void addFill(char fillChar, int numSpaces, int spacesBefore = 0);

int getDigits(int number);
int getIntAnswer();
int setupRandomNumber(int number);

string makeLowerCase(string value);

const int MARGIN = 10;

const int MENU = 0;
const int ADDITION = 1;
const int SUBTRACTION = 2;
const int MULTIPLICATION = 3;
const int DIVISION = 4;
const int DIVISION_REMAINDER = 5;
const int ORDER_OF_OPERATIONS = 6;
const int SETTINGS = 9;

int main()
{
	// Setting up options
	bool playing = true;
	bool choiceValid = false;
	bool allowNegative = false;
	char playingAnswer = 'y';
	int currentState = MENU;
	int numOneDigits = 1;
	int numTwoDigits = 1;
	int numThreeDigits = 1;
	string choice = " ";

	srand(time(0));

	while (playing)
	{
		switch (currentState)
		{
			case MENU:
				choiceValid = false;

				showTitle("Menu");
				addGap();
				addMargin();
				cout << "| Enter 1 for Addition." << endl;
				addMargin();
				cout << "| Enter 2 for Subtraction." << endl;
				addMargin();
				cout << "| Enter 3 for Multiplication." << endl;
				addMargin();
				cout << "| Enter 4 for Division." << endl;
				addMargin();
				cout << "| Enter 5 for Division with Remainder." << endl;
				addMargin();
				cout << "| Enter 6 for Order of Operations Problem." << endl;
				addGap();
				addMargin();
				cout << "| Enter 9 for Settings Menu." << endl;
				addMargin();
				cout << "| Enter 0 to Quit." << endl;

				while (!choiceValid)
				{
					addGap();
					addMargin();
					cout << "Choice: ";
					getline(cin, choice);

					if (choice == "0")
					{
						playing = false;
						choiceValid = true;
					}
					else if (choice == "1")
					{
						currentState = ADDITION;
						choiceValid = true;
					}
					else if (choice == "2")
					{
						currentState = SUBTRACTION;
						choiceValid = true;
					}
					else if (choice == "3")
					{
						currentState = MULTIPLICATION;
						choiceValid = true;
					}
					else if (choice == "4")
					{
						currentState = DIVISION;
						choiceValid = true;
					}
					else if (choice == "5")
					{
						currentState = DIVISION_REMAINDER;
						choiceValid = true;
					}
					else if (choice == "6")
					{
						currentState = ORDER_OF_OPERATIONS;
						choiceValid = true;
					}
					else if (choice == "9")
					{
						currentState = SETTINGS;
						choiceValid = true;
					}
					else
					{
						addGap();
						addMargin();
						cout << "You have made an invalid choice. Try again." << endl;
					}
				}
				break;

			case ADDITION:
				createAdditionProblem(numOneDigits, numTwoDigits);
				playAgainMessage(currentState);
				break;

			case SUBTRACTION:
				createSubtractionProblem(numOneDigits, numTwoDigits, allowNegative);
				playAgainMessage(currentState);
				break;

			case MULTIPLICATION:
				createMultiplicationProblem(numOneDigits, numTwoDigits);
				playAgainMessage(currentState);
				break;

			case DIVISION:
				createDivisionProblem(numOneDigits, numTwoDigits);
				playAgainMessage(currentState);
				break;

			case DIVISION_REMAINDER:
				createDivisionRemainderProblem(numOneDigits, numTwoDigits);
				playAgainMessage(currentState);
				break;

			case ORDER_OF_OPERATIONS:
				createOrderOfOperationsProblem(numOneDigits, numTwoDigits, numThreeDigits);
				playAgainMessage(currentState);
				break;

			case SETTINGS:
				showSettings(numOneDigits, numTwoDigits, numThreeDigits, allowNegative, currentState);
				break;
		};
	}

	addGap();
	addMargin();
	addFill('=', 21);
	addMargin();
	cout << "|" << setw(18) << " Hope you had fun! |" << endl;
	addMargin();
	addFill('=', 21);

	return 0;
}

void createAdditionProblem(int numOneDigits, int numTwoDigits)
{
	// Set up the problem
	int numberOne = setupRandomNumber(numOneDigits);
	int numberTwo = setupRandomNumber(numTwoDigits);
	int correctAnswer = 0;
	int userAnswer = 0;

	// Keeping larger numbers on top since it looks nicer
	if (numberTwo > numberOne)
	{
		int tempValue = numberOne;
		numberOne = numberTwo;
		numberTwo = tempValue;
	}

	correctAnswer = numberOne + numberTwo;

	showTitle("Addition");
	displayProblem(numberOne, numberTwo, '+', correctAnswer);
	
	userAnswer = getIntAnswer();
	checkAnswer(userAnswer, correctAnswer);
	
	// Display the full problem with answer
	displayProblem(numberOne, numberTwo, '+', correctAnswer, true);
}

void createSubtractionProblem(int numOneDigits, int numTwoDigits, bool allowNegative)
{
	// Set up the problem
	int numberOne = setupRandomNumber(numOneDigits);
	int numberTwo = setupRandomNumber(numTwoDigits);
	int correctAnswer = 0;
	int userAnswer = 0;

	//If don't want negative answers, keep larger number on top
	if (!allowNegative && numberTwo > numberOne)
	{
		int tempValue = numberOne;
		numberOne = numberTwo;
		numberTwo = tempValue;
	}

	correctAnswer = numberOne - numberTwo;

	showTitle("Subtraction");
	displayProblem(numberOne, numberTwo, '-', correctAnswer);

	userAnswer = getIntAnswer();
	checkAnswer(userAnswer, correctAnswer);

	// Display the full problem with answer
	displayProblem(numberOne, numberTwo, '-', correctAnswer, true);
}

void createMultiplicationProblem(int numOneDigits, int numTwoDigits)
{
	// Set up the problem
	int numberOne = setupRandomNumber(numOneDigits);
	int numberTwo = setupRandomNumber(numTwoDigits);
	int correctAnswer = 0;
	int userAnswer = 0;

	// Looks nicer if the larger number is on top
	if (numberTwo > numberOne)
	{
		int tempValue = numberOne;
		numberOne = numberTwo;
		numberTwo = tempValue;
	}

	correctAnswer = numberOne * numberTwo;

	showTitle("Multiplication");
	displayProblem(numberOne, numberTwo, 'x', correctAnswer);

	userAnswer = getIntAnswer();
	checkAnswer(userAnswer, correctAnswer);

	// Display the full problem with answer
	displayProblem(numberOne, numberTwo, 'x', correctAnswer, true);
}

void createDivisionProblem(int numOneDigits, int numTwoDigits)
{
	// Set up the problem
	int numberOne = setupRandomNumber(numOneDigits);
	int numberTwo = setupRandomNumber(numTwoDigits);
	int correctAnswer = 0;
	int userAnswer = 0;

	// Want larger number on top since not dealing with fractions
	if (numberTwo > numberOne)
	{
		int tempValue = numberOne;
		numberOne = numberTwo;
		numberTwo = tempValue;
	}

	correctAnswer = numberOne / numberTwo;

	//Need to make the first number evenly divisible
	numberOne = correctAnswer * numberTwo;

	showTitle("Division");
	displayProblem(numberOne, numberTwo, 'ö', correctAnswer);

	userAnswer = getIntAnswer();
	checkAnswer(userAnswer, correctAnswer);

	// Display the full problem with answer
	displayProblem(numberOne, numberTwo, 'ö', correctAnswer, true);
}

void createDivisionRemainderProblem(int numOneDigits, int numTwoDigits)
{
	// Set up the problem
	int numberOne = setupRandomNumber(numOneDigits);
	int numberTwo = setupRandomNumber(numTwoDigits);
	int correctAnswer = 0;
	int correctRemainder = 0;
	int userAnswer = 0;
	int userRemainder = 0;

	// Want larger number on top since not dealing with fractions
	if (numberTwo > numberOne)
	{
		int tempValue = numberOne;
		numberOne = numberTwo;
		numberTwo = tempValue;
	}

	correctAnswer = numberOne / numberTwo;
	correctRemainder = numberOne % numberTwo;

	showTitle("Division with Remainders");
	displayProblem(numberOne, numberTwo, 'ö', correctAnswer);

	userAnswer = getIntAnswer();
	addMargin();
	cout << "Remainder: ";
	userRemainder = getIntAnswer();
	checkAnswer(userAnswer, correctAnswer, true, userRemainder, correctRemainder);

	// Display the full problem with answer
	displayProblem(numberOne, numberTwo, 'ö', correctAnswer, true, true, correctRemainder);
}

void createOrderOfOperationsProblem(int numOneDigits, int numTwoDigits, int numThreeDigits)
{
	// Set up the problem
	int numberOne = setupRandomNumber(numOneDigits);
	int numberTwo = setupRandomNumber(numTwoDigits);
	int numberThree = setupRandomNumber(numThreeDigits);

	int correctAnswer = 0;
	int userAnswer = 0;
	string problemString = "";

	int parenthesesFirst = rand() % 3;
	int firstSymbol = rand() % 3;
	int secondSymbol = rand() % 3;

	if (parenthesesFirst == 1)
	{
		if (firstSymbol == 0 && secondSymbol == 0)
		{
			problemString = "(" + to_string(numberOne) + " + " + to_string(numberTwo) + ") + " + to_string(numberThree);
			correctAnswer = (numberOne + numberTwo) + numberThree;
		}
		else if (firstSymbol == 0 && secondSymbol == 1)
		{
			problemString = "(" + to_string(numberOne) + " + " + to_string(numberTwo) + ") - " + to_string(numberThree);
			correctAnswer = (numberOne + numberTwo) - numberThree;
		}
		else if (firstSymbol == 0 && secondSymbol == 2)
		{
			problemString = "(" + to_string(numberOne) + " + " + to_string(numberTwo) + ") X " + to_string(numberThree);
			correctAnswer = (numberOne + numberTwo) * numberThree;
		}
		else if (firstSymbol == 1 && secondSymbol == 0)
		{
			problemString = "(" + to_string(numberOne) + " - " + to_string(numberTwo) + ") + " + to_string(numberThree);
			correctAnswer = (numberOne - numberTwo) + numberThree;
		}
		else if (firstSymbol == 1 && secondSymbol == 1)
		{
			problemString = "(" + to_string(numberOne) + " - " + to_string(numberTwo) + ") - " + to_string(numberThree);
			correctAnswer = (numberOne - numberTwo) - numberThree;
		}
		else if (firstSymbol == 1 && secondSymbol == 2)
		{
			problemString = "(" + to_string(numberOne) + " - " + to_string(numberTwo) + ") X " + to_string(numberThree);
			correctAnswer = (numberOne - numberTwo) * numberThree;
		}
		else if (firstSymbol == 2 && secondSymbol == 0)
		{
			problemString = "(" + to_string(numberOne) + " X " + to_string(numberTwo) + ") + " + to_string(numberThree);
			correctAnswer = (numberOne * numberTwo) + numberThree;
		}
		else if (firstSymbol == 2 && secondSymbol == 1)
		{
			problemString = "(" + to_string(numberOne) + " X " + to_string(numberTwo) + ") - " + to_string(numberThree);
			correctAnswer = (numberOne * numberTwo) - numberThree;
		}
		else if (firstSymbol == 2 && secondSymbol == 2)
		{
			problemString = "(" + to_string(numberOne) + " X " + to_string(numberTwo) + ") X " + to_string(numberThree);
			correctAnswer = (numberOne * numberTwo) * numberThree;
		}
	}
	else if (parenthesesFirst == 2)
	{
		if (firstSymbol == 0 && secondSymbol == 0)
		{
			problemString = to_string(numberOne) + " + (" + to_string(numberTwo) + " + " + to_string(numberThree) + ")";
			correctAnswer = numberOne + (numberTwo + numberThree);
		}
		else if (firstSymbol == 0 && secondSymbol == 1)
		{
			problemString = to_string(numberOne) + " + (" + to_string(numberTwo) + " - " + to_string(numberThree) + ")";
			correctAnswer = numberOne + (numberTwo - numberThree);
		}
		else if (firstSymbol == 0 && secondSymbol == 2)
		{
			problemString = to_string(numberOne) + " + (" + to_string(numberTwo) + " X " + to_string(numberThree) + ")";
			correctAnswer = numberOne + (numberTwo * numberThree);
		}
		else if (firstSymbol == 1 && secondSymbol == 0)
		{
			problemString = to_string(numberOne) + " - (" + to_string(numberTwo) + " + " + to_string(numberThree) + ")";
			correctAnswer = numberOne - (numberTwo + numberThree);
		}
		else if (firstSymbol == 1 && secondSymbol == 1)
		{
			problemString = to_string(numberOne) + " - (" + to_string(numberTwo) + " - " + to_string(numberThree) + ")";
			correctAnswer = numberOne - (numberTwo - numberThree);
		}
		else if (firstSymbol == 1 && secondSymbol == 2)
		{
			problemString = to_string(numberOne) + " - (" + to_string(numberTwo) + " X " + to_string(numberThree) + ")";
			correctAnswer = numberOne - (numberTwo * numberThree);
		}
		else if (firstSymbol == 2 && secondSymbol == 0)
		{
			problemString = to_string(numberOne) + " X (" + to_string(numberTwo) + " + " + to_string(numberThree) + ")";
			correctAnswer = numberOne * (numberTwo + numberThree);
		}
		else if (firstSymbol == 2 && secondSymbol == 1)
		{
			problemString = to_string(numberOne) + " X (" + to_string(numberTwo) + " - " + to_string(numberThree) + ")";
			correctAnswer = numberOne * (numberTwo - numberThree);
		}
		else if (firstSymbol == 2 && secondSymbol == 2)
		{
			problemString = to_string(numberOne) + " X (" + to_string(numberTwo) + " X " + to_string(numberThree) + ")";
			correctAnswer = numberOne * (numberTwo * numberThree);
		}
	}
	else
	{
		if (firstSymbol == 0 && secondSymbol == 0)
		{
			problemString = to_string(numberOne) + " + " + to_string(numberTwo) + " + " + to_string(numberThree);
			correctAnswer = numberOne + numberTwo + numberThree;
		}
		else if (firstSymbol == 0 && secondSymbol == 1)
		{
			problemString = to_string(numberOne) + " + " + to_string(numberTwo) + " - " + to_string(numberThree);
			correctAnswer = numberOne + numberTwo - numberThree;
		}
		else if (firstSymbol == 0 && secondSymbol == 2)
		{
			problemString = to_string(numberOne) + " + " + to_string(numberTwo) + " X " + to_string(numberThree);
			correctAnswer = numberOne + numberTwo * numberThree;
		}
		else if (firstSymbol == 1 && secondSymbol == 0)
		{
			problemString = to_string(numberOne) + " - " + to_string(numberTwo) + " + " + to_string(numberThree);
			correctAnswer = numberOne - numberTwo + numberThree;
		}
		else if (firstSymbol == 1 && secondSymbol == 1)
		{
			problemString = to_string(numberOne) + " - " + to_string(numberTwo) + " - " + to_string(numberThree);
			correctAnswer = numberOne - numberTwo - numberThree;
		}
		else if (firstSymbol == 1 && secondSymbol == 2)
		{
			problemString = to_string(numberOne) + " - " + to_string(numberTwo) + " X " + to_string(numberThree);
			correctAnswer = numberOne - numberTwo * numberThree;
		}
		else if (firstSymbol == 2 && secondSymbol == 0)
		{
			problemString = to_string(numberOne) + " X " + to_string(numberTwo) + " + " + to_string(numberThree);
			correctAnswer = numberOne * numberTwo + numberThree;
		}
		else if (firstSymbol == 2 && secondSymbol == 1)
		{
			problemString = to_string(numberOne) + " X " + to_string(numberTwo) + " - " + to_string(numberThree);
			correctAnswer = numberOne * numberTwo - numberThree;
		}
		else if (firstSymbol == 2 && secondSymbol == 2)
		{
			problemString = to_string(numberOne) + " X " + to_string(numberTwo) + " X " + to_string(numberThree);
			correctAnswer = numberOne * numberTwo * numberThree;
		}
	}

	showTitle("Order of Operations");
	addGap();
	addMargin();
	cout << "SOLVE: " << problemString << endl;

	userAnswer = getIntAnswer();

	checkAnswer(userAnswer, correctAnswer);
	addMargin();
	cout << "ANSWER: " << problemString << " = " << correctAnswer;
	addGap();
	addGap();

}

void displayProblem(int numberOne, int numberTwo, char symbol, int answer, bool showAnswer, bool withRemainder, int remainder)
{
	//Need to figure out the number of digits for each random number
	int numberOneDigits = getDigits(numberOne);
	int numberTwoDigits = getDigits(numberTwo);
	int numberAnswerDigits = getDigits(answer);

	int largest = numberAnswerDigits;
	if (largest < numberOneDigits)
	{
		largest = numberOneDigits;
	}
	if (largest < numberTwoDigits)
	{
		largest = numberTwoDigits;
	}

	int spacesToSymbol = 4;
	int spacesIncludeSymbol = spacesToSymbol + 2;	// Includes: "symbol "
	int extraSpacesNumOne = largest - numberOneDigits;
	int extraSpacesNumTwo = largest - numberTwoDigits;
	int extraSpaceAnswer = largest - numberAnswerDigits;

	addMargin();
	addSpaces(spacesIncludeSymbol + extraSpacesNumOne);
	cout << numberOne << endl;
	addMargin();
	addSpaces(spacesToSymbol);
	cout << symbol;
	addSpaces(1 + extraSpacesNumTwo);	// Adding 1 to start one space past the symbol
	cout << numberTwo << endl;
	addMargin();
	addFill('-', 2 + largest + 2, 4);

	if (showAnswer)
	{
		addMargin();
		if (answer > 0)
		{
			addSpaces(spacesIncludeSymbol + extraSpaceAnswer);
		}
		else
		{
			// Account for - symbol in negative numbers
			addSpaces(spacesIncludeSymbol + extraSpaceAnswer - 1);
		}
		cout << answer;
		if (withRemainder)
		{
			cout << "  Remainder: " << remainder;
		}
		addGap();
		addGap();
	}
}

void checkAnswer(int userAnswer, int correctAnswer, bool withRemainder, int userRemainder, int correctRemainder)
{
	if (withRemainder)
	{
		if (userAnswer == correctAnswer && userRemainder == correctRemainder)
		{
			addMargin();
			cout << "You are correct!" << endl;
		}
		else
		{
			addMargin();
			cout << "You are incorrect." << endl;
			addGap();
			addMargin();
			cout << "The correct answer is:" << endl;
		}
	}
	else
	{
		if (userAnswer == correctAnswer)
		{
			addMargin();
			cout << "You are correct!" << endl;
		}
		else
		{
			addMargin();
			cout << "You are incorrect." << endl;
			addGap();
			addMargin();
			cout << "The correct answer is:" << endl;
		}
	}

}

int getDigits(int number)
{
	int rem = 1;
	int testDigit = 1;
	int digits = 0;
	while (rem != 0)
	{
		rem = number / testDigit;
		if (rem != 0)
		{
			testDigit *= 10;
			digits += 1;
		}
	}

	return digits;
}

void playAgainMessage(int& currentState)
{
	string answer = " ";
	bool keepLooping = true;

	while (keepLooping)
	{
		addMargin();
		cout << "Would you like to try again?" << endl;
		addMargin();
		cout << "(y or 1 / n or 0): ";
		getline(cin, answer);

		answer = makeLowerCase(answer);

		if (answer == "n" || answer == "0")
		{
			currentState = MENU;
			keepLooping = false;
		}
		else if (answer == "y" || answer == "1")
		{
			keepLooping = false;
		}
		else
		{
			addGap();
			addMargin();
			cout << "Invalid input. Try again." << endl;
		}
	}
}

void showTitle(string titleName)
{
	string name = "|    " + titleName + "    |";

	addMargin();
	addFill('=', name.length());
	addMargin();
	cout << name << endl;
	addMargin();
	addFill('=', name.length());
}

void showSettings(int& numOneDigits, int& numTwoDigits, int& numThreeDigits, bool& allowNegative, int& currentState)
{
	bool choiceValid = false;
	string choice = " ";
	string tempDigits = " ";
	string negativeString = "";

	while (currentState == SETTINGS)
	{
		negativeString = (allowNegative) ? "True" : "False";
		//system(CLEAR_SCREEN);

		showTitle("Settings");
		addMargin();
		cout << "* Third number is only used in Order of Operations problem." << endl;
		addGap();
		addMargin();
		cout << "First  Number Digits: " << numOneDigits << endl;
		addMargin();
		cout << "Second Number Digits: " << numTwoDigits << endl;
		addMargin();
		cout << "Third  Number Digits: " << numThreeDigits << endl;
		addGap();
		addMargin();
		cout << "Subtraction Negative Numbers: " << negativeString << endl;
		addGap();
		addMargin();
		cout << "| Enter 1 to change number of digits for first number." << endl;
		addMargin();
		cout << "| Enter 2 to change number of digits for second number." << endl;
		addMargin();
		cout << "| Enter 3 to change number of digits for third number." << endl;
		addMargin();
		cout << "| Enter 4 to toggle allowing negative numbers in subtraction." << endl;
		addGap();
		addMargin();
		cout << "| Enter 0 to go back to the main menu." << endl;
		addGap();
		addGap();

		while (!choiceValid)
		{
			addGap();
			addMargin();
			cout << "Choice: ";
			getline(cin, choice);

			if (choice == "0")
			{
				currentState = MENU;
				choiceValid = true;
			}
			else if (choice == "1")
			{
				choiceValid = true;

				addGap();
				addMargin();
				cout << "Enter number of digits for first number: ";
				getline(cin, tempDigits);

				for (int i = 0; i < tempDigits.length(); i++)
				{
					if (!isdigit(tempDigits[i]))
					{
						addGap();
						addMargin();
						cout << "Invalid input." << endl;
						choiceValid = false;
						break;
					}
				}

				if (choiceValid == true)
				{
					numOneDigits = stoi(tempDigits);
				}
			}
			else if (choice == "2")
			{
				choiceValid = true;

				addGap();
				addMargin();
				cout << "Enter number of digits for second number: ";
				getline(cin, tempDigits);

				for (int i = 0; i < tempDigits.length(); i++)
				{
					if (!isdigit(tempDigits[i]))
					{
						addGap();
						addMargin();
						cout << "Invalid input." << endl;
						choiceValid = false;
						break;
					}
				}

				if (choiceValid == true)
				{
					numTwoDigits = stoi(tempDigits);
				}
			}
			else if (choice == "3")
			{
				choiceValid = true;

				addGap();
				addMargin();
				cout << "Enter number of digits for third number: ";
				getline(cin, tempDigits);

				for (int i = 0; i < tempDigits.length(); i++)
				{
					if (!isdigit(tempDigits[i]))
					{
						addGap();
						addMargin();
						cout << "Invalid input." << endl;
						choiceValid = false;
						break;
					}
				}

				if (choiceValid == true)
				{
					numThreeDigits = stoi(tempDigits);
				}
			}
			else if (choice == "4")
			{
				choiceValid = true;
				allowNegative = !allowNegative;
			}
			else
			{
				addGap();
				addMargin();
				cout << "You have made an invalid choice. Try again." << endl;
			}
		}

		choiceValid = false;
	}
}

void addGap()
{
	cout << endl;
}

void addMargin()
{
	if (MARGIN > 0)
	{
		cout << setw(MARGIN) << " ";
	}
}

void addSpaces(int numSpaces)
{
	if (numSpaces > 0)
	{
		cout << setw(numSpaces) << " ";
	}
}

void addFill(char fillChar, int fillAmount, int spacesBefore)
{
	if (spacesBefore > 0)
	{
		cout << setw(spacesBefore) << " " << setfill(fillChar) << setw(fillAmount) << fillChar << setfill(' ');
	}
	else
	{
		cout << setfill(fillChar) << setw(fillAmount) << fillChar << setfill(' ');
	}

	cout << endl;
}

int getIntAnswer()
{
	string answer = " ";
	bool keepLooping = true;

	while (keepLooping)
	{
		addGap();
		addMargin();
		cout << "Enter the answer: ";
		getline(cin, answer);
		addGap();

		// Check if there are any of the characters are not numbers
		for (int i = 0; i < answer.length(); i++)
		{
			if (answer[0] == '-' && answer.size() == 1)
			{
				addMargin();
				cout << "You can't use just -.";
				break;
			}
			else if (!isdigit(answer[i]) && (answer[0] != '-'))
			{
				addMargin();
				cout << "You can only have numbers or - in your answer.";
				break;
			}
			else if (i == answer.length() - 1)
			{
				keepLooping = false;
			}
		}
	}

	return stoi(answer);
}

int setupRandomNumber(int number)
{
	int maxRandom = 0;

	for (int i = 0; i < number; i++)
	{
		if (i != 0)
		{
			maxRandom *= 10;
		}

		maxRandom++;
	}
	maxRandom *= 9;

	// Adding 1 so zero isn't used
	return (rand() % maxRandom) + 1;

}

string makeLowerCase(string value)
{
	for (int i = 0; i < value.length(); i++)
	{
		value[i] = tolower(value[i]);
	}

	return value;
}
