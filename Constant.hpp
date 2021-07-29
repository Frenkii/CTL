#pragma once
#include "stdafx.h"

const int TAG_ITEM_CTL = 1;

const int TAG_FUNC_CTL_TOGGLE = 205;


const COLORREF TAG_GREEN = RGB(0, 190, 0);
const COLORREF TAG_RED = RGB(190, 0, 0);
const COLORREF TAG_YELLOW = RGB(222, 181, 18);

const char notCleared[] = "\xac";
const char cleared[] = "\xa4";

const int FAC_FSS = 1;
const int FAC_DEL = 2;
const int FAC_GND = 3;
const int FAC_TWR = 4;
const int FAC_APP = 5;
const int FAC_CTR = 6;


inline static bool startsWith(const char* pre, const char* str)
{
	size_t lenpre = strlen(pre), lenstr = strlen(str);
	return lenstr < lenpre ? false : strncmp(pre, str, lenpre) == 0;
};