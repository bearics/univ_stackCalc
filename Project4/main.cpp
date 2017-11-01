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

		cout << "수식을 입력하세요(infix만 가능, 뛰어쓰기 금지) : ";
		cin >> exprInfix;
		cout << "입력한 수식(infix)   : " << exprInfix << endl;
		exprPostfix = ev.infixToPostfix(exprInfix);
		cout << "입력한 수식(postfix) : " << exprPostfix << endl;
		cout << "계산 결과 값은 " << ev.evaluate(exprPostfix) << "입니다.\n" << endl;
		
	}
	
	return 0;
}