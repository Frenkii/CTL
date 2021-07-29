// rStatus.cpp : Defines the initialization routines for the DLL.
//
#include "stdafx.h"
#include "EuroScopePlugIn.h"
#include "ctlController.hpp"

CCTLPlugin* gpMyPlugin = NULL;

void    __declspec (dllexport)    EuroScopePlugInInit(EuroScopePlugIn::CPlugIn** ppPlugInInstance)
{

	// create the instance
	*ppPlugInInstance = gpMyPlugin = new CCTLPlugin();
}

//---EuroScopePlugInExit-----------------------------------------------

void    __declspec (dllexport)    EuroScopePlugInExit(void)
{

	// delete the instance
	delete gpMyPlugin;
}