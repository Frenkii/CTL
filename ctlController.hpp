#pragma once
#include "EuroScopePlugIn.h"
#include <sstream>
#include <iostream>
#include <string>
#include "Constant.hpp"
#include <fstream>
#include <vector>
#include <atlstr.h>
#include <algorithm>
#include <regex>

#include "rapidjson/document.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/writer.h"

#define MY_PLUGIN_NAME      "CTL"
#define MY_PLUGIN_VERSION   "0.0.1"
#define MY_PLUGIN_DEVELOPER "Frenkii"
#define MY_PLUGIN_COPYRIGHT "GPL v3"
#define MY_PLUGIN_VIEW_AVISO  "Cleared To Land"

using namespace std;
using namespace rapidjson;
using namespace EuroScopePlugIn;

// Other stuff


class CCTLPlugin :
	public EuroScopePlugIn::CPlugIn
{
public:
	CCTLPlugin();
	virtual ~CCTLPlugin();

	// Euroscope functions

	virtual void debugMessage(string type, string message);

	virtual void sendMessage(string type, string message);

	virtual void sendMessage(string message);

	virtual void OnGetTagItem(CFlightPlan FlightPlan, CRadarTarget RadarTarget, int ItemCode, int TagData, char sItemString[16], int* pColorCode, COLORREF* pRGB, double* pFontSize);

	virtual void OnFunctionCall(int FunctionId, const char* sItemString, POINT Pt, RECT Area);

	virtual bool OnCompileCommand(const char* sCommandLine);

	virtual void OnTimer(int Count);

	// Plugin functions

	virtual void setClearence(CFlightPlan flightPlan);

	virtual bool isCleared(CFlightPlan flightPlan);

	virtual void removeClearence(CFlightPlan flightPlan);

};