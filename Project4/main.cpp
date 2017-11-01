#pragma once
#include <iostream>
#include <string>
#include <math.h>
#include "stack.h"

#define D_MAX_ARRAY_SIZE 30;

using namespace std;

string* stringSplit(string strOri, char tok); // 문자열 자르는 함수
void evaluate_stack(stack<double>& numbers, stack<char>& operations);
double read_and_evaluate(istream& ins);
double evaluate(string expr);
string infixToPostfix(string expr);
int operLevel(char oper);	// 연산자 우선순위 정해주는 함수

int main()
{

	string expr;

	while (1) {
		cout << "수식을 입력하세요(infix만 가능) : ";
		cin >> expr;
		cout << "입력한 수식(infix)   : " << expr << endl;
		cout << "입력한 수식(postfix) : " << infixToPostfix(expr) << endl;
		cout << "계산 결과 값은 " << evaluate(expr) << "입니다." << endl;
		
	}
	
	return 0;
}

// postfix : 3 A B * +
// infix : 3 + A * B
double evaluate(string expr)
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
		cout << "b\n";
		if (isdigit(expr[i])) {
			if (expr[i] >= '0' && expr[i] <= '9')
				number = (double)(expr[i] - '0');	// char를 소수로 변환
			while (expr[i + 1] >= '0' && expr[i + 1] <= '9') {
				number = number * 10 + (double)(expr[++i] - '0');
			}
			numbers.push(number);
			if (expr[i+1] == DECIMAL) {
				i++;
				number = numbers.top();
				numbers.pop();
				int pre = 1;
				while (expr[i + 1] >= '0' && expr[i + 1] <= '9') {
					number = number + (double)(expr[++i] - '0') / pow(10, pre++);
				}
				numbers.push(number);
			}
		}
		else if (strchr("+-*/", expr[i]) != NULL) {
			symbol = expr[i];
			operations.push(symbol);
		}
		else if (expr[i] == RIGHT_PARENTHESIS) {
			evaluate_stack(numbers, operations);
		}
		else {
		}
		i++;
	}

	return numbers.top();

}

string infixToPostfix(string expr)
{
	string conv="";

	const char DECIMAL = '.';
	const char RIGHT_PARENTHESIS = ')';
	stack<char> operations;
	double number;
	char symbol;
	int i = 0;


	while (expr[i] != NULL)
	{
		cout << "b\n";
		if (isdigit(expr[i])) {
			conv += expr[i];
			while (isdigit(expr[i+1]) || expr[i+1] == DECIMAL ) {
				conv += expr[++i];
			}
		}
		else if (strchr("(+-*/", expr[i]) != NULL) {
			symbol = expr[i];
			if (symbol == '*' || symbol == '/') {
				while (operLevel(operations.top()) >= operLevel(symbol)) {
					if (operations.top() == '(') break;
					operations.pop();
				}
				
			}
			operations.push(symbol);
		}
		else if (expr[i] == RIGHT_PARENTHESIS) {
			while (operations.top() != '(') {
				conv += operations.top();
				operations.pop();
			}
			operations.pop();
		}
		else {
		}
		conv += " ";
		i++;
	}

	return conv;
}

int operLevel(char oper)
{
	if (oper == '+' || oper == '-') return 1;
	else if (oper == '*' || oper == '/') return 2;
	else {}
	
}

void evaluate_stack(stack<double>& numbers, stack<char>& operations)
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
	case '/': numbers.push(operand1 / operand2); break;
	}
	operations.pop();
}