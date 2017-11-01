#pragma once
#include <iostream>
#include <string>
#include "stack.h"

using namespace std;

class eval
{

public:
	double evaluate(string expr);
	string infixToPostfix(string expr);
	int operLevel(char oper);
	int evaluate_stack(stack<double>& numbers, stack<char>& operations);
};

double eval::evaluate(string expr)
{
	const char DECIMAL = '.';
	const char RIGHT_PARENTHESIS = ')';

	stack<double> numbers;
	stack<char> operations;
	double number;
	char symbol;
	int i = 0;

	while (expr[i] != NULL)
	{
		if (isdigit(expr[i])) {
			string num = "";
			while (isdigit(expr[i]) || expr[i] == '.')
				num += expr[i++];
			numbers.push(stof(num));
		}
		else if (strchr("+-*/", expr[i]) != NULL) {
			operations.push(expr[i]);
			if (evaluate_stack(numbers, operations) < 0)
				break;
			i++;
		}
		else {
			i++;
		}
	}
	if (expr[i] != NULL) return 0;
	return numbers.top();

}

string eval::infixToPostfix(string expr)
{
	string conv = "";

	const char DECIMAL = '.';
	const char RIGHT_PARENTHESIS = ')';
	stack<char> operations;
	double number;
	char symbol;
	int i = 0;

	while (expr[i] != NULL)
	{
		if (isdigit(expr[i])) {
			string num = "";
			while (isdigit(expr[i]) || expr[i] == '.')
				num += expr[i++];
			conv += num + " ";
		}
		else if (expr[i] == '(') {
			operations.push(expr[i++]);
		}
		else if (strchr("+-*/", expr[i]) != NULL) {
			while (!operations.empty() && operLevel(expr[i]) <= operLevel(operations.top())) {
				conv += operations.top();
				conv += " ";
				operations.pop();
			}
			operations.push(expr[i++]);
		}
		else if (expr[i] == RIGHT_PARENTHESIS) {
			while (operations.top() != '(') {
				conv += operations.top();
				conv += " ";
				operations.pop();
			}
			operations.pop();
			i++;
		}
		else {
			i++;
		}
	}
	// stack에 남아 있는거 모두 출력
	while (!operations.empty()) {
		conv += operations.top();
		conv += " ";
		operations.pop();
	}


	return conv;
}

int eval::operLevel(char oper)
{
	if (oper == '(') return 0;
	else if (oper == '+' || oper == '-') return 1;
	else if (oper == '*' || oper == '/') return 2;
	else return 3;

}

int eval::evaluate_stack(stack<double>& numbers, stack<char>& operations)
{
	double operand1, operand2;
	operand2 = numbers.top();
	numbers.pop();
	operand1 = numbers.top();
	numbers.pop();

	switch (operations.top()) {
	case '+': numbers.push(operand1 + operand2); break;
	case '-': numbers.push(operand1 - operand2); break;
	case '*': numbers.push(operand1 * operand2); break;
	case '/':
		if (operand2 == 0) {
			cout << "0으로 나눌 수 없어요\n";
			return -1;
		}
		numbers.push(operand1 / operand2); break;
	}
	operations.pop();
	return 0;
}