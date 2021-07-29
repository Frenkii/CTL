#include "stdafx.h"
#include "ctlController.hpp"

extern "C" IMAGE_DOS_HEADER __ImageBase;

bool blink;
bool debugMode;

int disCount;

ifstream sidDatei;
char DllPathFile[_MAX_PATH];
string pfad;

vector<string> clearedAircraft;
vector<string> landingAlert;

// Run on Plugin Initialization
CCTLPlugin::CCTLPlugin(void) :CPlugIn(EuroScopePlugIn::COMPATIBILITY_CODE, MY_PLUGIN_NAME, MY_PLUGIN_VERSION, MY_PLUGIN_DEVELOPER, MY_PLUGIN_COPYRIGHT)
{
	string loadingMessage = "Version: ";
	loadingMessage += MY_PLUGIN_VERSION;
	loadingMessage += " loaded.";
	sendMessage(loadingMessage);

	// Register Tag Item "VCT"
	RegisterTagItemType("CTL", TAG_ITEM_CTL);
	
	RegisterTagItemFunction("Toggle Cleared To Land", TAG_FUNC_CTL_TOGGLE);

	

	// Get Path of the VCTdata.json
	GetModuleFileNameA(HINSTANCE(&__ImageBase), DllPathFile, sizeof(DllPathFile));
	pfad = DllPathFile;
	pfad.resize(pfad.size() - strlen("CTL.dll"));

	debugMode = false;
	//getSids();
	// getEvents();
}

// Run on Plugin destruction, Ie. Closing EuroScope or unloading plugin
CCTLPlugin::~CCTLPlugin()
{
}

// All the Euroscope functions

void CCTLPlugin::debugMessage(string type, string message) {
	// Display Debug Message if debugMode = true
	if (debugMode) {
		DisplayUserMessage("CTL", type.c_str(), message.c_str(), true, true, true, false, false);
	}
}

void CCTLPlugin::sendMessage(string type, string message) {
	// Show a message
	DisplayUserMessage("CTL", type.c_str(), message.c_str(), true, true, true, true, false);
}

void CCTLPlugin::sendMessage(string message) {
	DisplayUserMessage("Message", "CTL", message.c_str(), true, true, true, false, false);
}

void CCTLPlugin::OnGetTagItem(CFlightPlan FlightPlan, CRadarTarget RadarTarget, int ItemCode, int TagData, char sItemString[16], int* pColorCode, COLORREF* pRGB, double* pFontSize)
{
	if (ItemCode == TAG_ITEM_CTL)
	{
		if (find(clearedAircraft.begin(), clearedAircraft.end(), FlightPlan.GetCallsign()) != clearedAircraft.end()) {
			*pColorCode = TAG_COLOR_RGB_DEFINED;
			*pRGB = TAG_GREEN;
			strcpy_s(sItemString, 16, cleared);
		}

		
		else if (
			(find(clearedAircraft.begin(), clearedAircraft.end(), FlightPlan.GetCallsign()) == clearedAircraft.end())
			&& FlightPlan.GetTrackingControllerIsMe() 
			&& FlightPlan.GetDistanceToDestination() < 6
			&& RadarTarget.GetPosition().GetPressureAltitude() < 1500
			) {
			*pColorCode = TAG_COLOR_RGB_DEFINED;
			*pRGB = TAG_YELLOW;
			strcpy_s(sItemString, 16, "CLR");
		}
		
		else {
			strcpy_s(sItemString, 16, notCleared);
		} 
		
		/* 
		*pColorCode = TAG_COLOR_RGB_DEFINED;
		int ctl = 172;
		bool landStatus = false;
		if (!landStatus) {
			*pRGB = TAG_GREEN;
			strcpy_s(sItemString, 16, notCleared);
		}
		else {
			strcpy_s(sItemString, 16, cleared);
		}
		*/

	}
	
}


void CCTLPlugin::OnFunctionCall(int FunctionId, const char* sItemString, POINT Pt, RECT Area) {

	if (FunctionId == TAG_FUNC_CTL_TOGGLE) {
		setClearence(FlightPlanSelectASEL());
	}
	
}


void CCTLPlugin::setClearence(CFlightPlan flightPlan) {
	if (find(clearedAircraft.begin(), clearedAircraft.end(), flightPlan.GetCallsign()) == clearedAircraft.end()) {
		clearedAircraft.push_back(flightPlan.GetCallsign());
	} else {
		clearedAircraft.erase(remove(clearedAircraft.begin(), clearedAircraft.end(), flightPlan.GetCallsign()), clearedAircraft.end());
	}

		
}

void CCTLPlugin::removeClearence(CFlightPlan flightPlan) {
	if (find(clearedAircraft.begin(), clearedAircraft.end(), flightPlan.GetCallsign()) != clearedAircraft.end()) {
		clearedAircraft.erase(remove(clearedAircraft.begin(), clearedAircraft.end(), flightPlan.GetCallsign()), clearedAircraft.end());
	}
}



bool CCTLPlugin::isCleared(CFlightPlan flightPlan) {
	if (find(clearedAircraft.begin(), clearedAircraft.end(), flightPlan.GetCallsign()) == clearedAircraft.end()) {
		return false;
	} else {
		return true;
	}
}





bool CCTLPlugin::OnCompileCommand(const char* sCommandLine) {
	
	if (startsWith(".ctl debug", sCommandLine))
	{
		if (debugMode) {
			debugMessage("DebugMode", "Deactivating Debug Mode!");
			debugMode = false;
		}
		else {
			debugMode = true;
			debugMessage("DebugMode", "Activating Debug Mode!");
		}
		return true;
	}
	return false;
}

void CCTLPlugin::OnTimer(int Counter) {

	for (string callsign : clearedAircraft) {
		CFlightPlan flightPlan = FlightPlanSelect(callsign.c_str());
		CRadarTarget radarTarget = RadarTargetSelect(callsign.c_str());
		if (!flightPlan.IsValid()) {
			removeClearence(flightPlan);
		}
	}

	



	blink = !blink;

	if (blink) {
		if (disCount < 6) {
			disCount++;
		}
		else {
			disCount = 0;
		}
	}

}


