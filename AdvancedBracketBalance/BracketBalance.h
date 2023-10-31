#pragma once

enum BALANCE_RETURNS
{
	notBalanced = -1,
	balanced = 0,
	ok = 0,
	memoryError = 1,
	nullPointerError = 2,
};

int checkBalance(const char* const string);