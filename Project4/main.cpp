#pragma once
#include <iostream>
#include <string>
#include "eval.h"

using namespace std;

int main()
{

	string exprInfix;
	string exprPostfix;

	eval ev;

	while (1) {

		cout << "������ �Է��ϼ���(infix�� ����, �پ�� ����) : ";
		cin >> exprInfix;
		cout << "�Է��� ����(infix)   : " << exprInfix << endl;
		exprPostfix = ev.infixToPostfix(exprInfix);
		cout << "�Է��� ����(postfix) : " << exprPostfix << endl;
		cout << "��� ��� ���� " << ev.evaluate(exprPostfix) << "�Դϴ�.\n" << endl;
		
	}
	
	return 0;
}