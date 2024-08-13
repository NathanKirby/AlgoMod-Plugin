#include "pch.h"
#include "AlgoMod.h"
#include "Kirklib.h"
#include <bakkesmod/wrappers/kismet/SequenceWrapper.h>
#include <bakkesmod/wrappers/kismet/SequenceVariableWrapper.h>
#include <fstream>
#include <sstream>
#include <Windows.h>
#include <filesystem>
#include <windows.h>
#include <iostream>
#include <tchar.h>
#define UNICODE
#include <string>
#include <vector>
#include <regex>
#include <sstream>
#include <thread> // for std::this_thread::sleep_for
#include <chrono> // for std::chrono::seconds
#define CURL_REQUEST_H
using namespace std;

BAKKESMOD_PLUGIN(AlgoMod, "Algo Mod!", plugin_version, PLUGINTYPE_FREEPLAY)
std::shared_ptr<CVarManagerWrapper> _globalCvarManager;
std::filesystem::path RocketLeagueExecutableFolder;


/// <summary>
/// AlgoMod entrance code
/// </summary>
void AlgoMod::onLoad() {
	_globalCvarManager = cvarManager;

	if (isPlayerVerified != false || doeshavemap != false) {
		cvarManager->executeCommand("unreal_command exit;");
	}

	Hooks();
	IsInternetConnected();

	if (!Kirklib::file_exists(algoMapPath)) {
		Kirklib::string_to_file(algoMapPath, "0");
	}

	cvarManager->executeCommand("bind F7 Algo_Loadp");
	CarColor = cvarManager->getCvar("cl_freeplay_carcolor").getBoolValue();
}


/// <summary>
/// Hook code
/// </summary>
void AlgoMod::Hooks() {
	// Detects when a map loads then runs find map function
	gameWrapper->HookEvent("Function ProjectX.NetModeSystem_X.LevelLoaded", [this](std::string eventName) {
		LevelLoadCheck();
		});

	// Hooks to car spawn IsEnabledFunction which is also called on load and then checks checkIfEnabled one sec later
	gameWrapper->HookEvent("Function TAGame.GameEvent_TA.AddCar", [this](std::string eventName) {
		if (initialMapLoad == true && GetKismetSequence() == true) {
			IsInternetConnected();
			gameWrapper->SetTimeout([this](GameWrapper*) {
				cvarManager->executeCommand("cl_freeplay_carcolor 0");
				Chocolate();
				}, 1.0);
		}

		initialMapLoad = true;
		});

	// Detects every physics tick to ensure speedruntools plugin is disabled
	gameWrapper->HookEvent("Function TAGame.Car_TA.SetVehicleInput", [this](std::string eventName) {
		if (isIntialLoadValid == true && IsSpeedRunLoaded() == true) {
			cvarManager->executeCommand("plugin unload speedruntools;");

			if (intialSpeedRunToolsOff == false) {
				DidHaveSpeedRun = true;
				intialSpeedRunToolsOff = true;
			}
		}
		else {
			intialSpeedRunToolsOff = true;
		}
		});

	// Detaches car mesh when get edition node is activated in kismet
	gameWrapper->HookEvent("Function TAGame.SeqAct_GetEdition_TA.Activated", [this](std::string eventName) {
		DetachCarMesh();
		});

	// Gets car mesh for hiding during replays
	gameWrapper->HookEventWithCallerPost<PrimitiveComponentWrapper>("Function TAGame.CarMeshComponentBase_TA.SetIsLocalPlayer", [this](PrimitiveComponentWrapper caller, void* params, std::string eventname) {
		if (GetKismetSequence()) {
			if (!caller.IsNull()) {
				CarMesh = caller;
			}
			else {
				LOG("Error: CAR MESH NULL");
			}
		}
		});

	// Removes wheels if requested
	gameWrapper->HookEventWithCaller<PrimitiveComponentWrapper>("Function TAGame.SkeletalMeshComponent_TA.OnAttached", [this](PrimitiveComponentWrapper caller, void* params, std::string eventname) {
		if (GetKismetSequence()) {
			// Find the HideWheels variable and see if it's true
			if (GetKismetVarByName("HideWheels").first) {
				ServerWrapper server = gameWrapper->GetGameEventAsServer();
				if (server) {
					CarWrapper car = server.GetGameCar();
					if (car) {
						// Makes sure the component is a wheel by checking it's RB channel position
						if (caller.GetRBChannel() != 3 && caller) {
							car.DetachPrimitiveComponent(caller);
						}
					}
				}
			}
		}
		});

	// Removes static mesh comp from car
	gameWrapper->HookEventWithCaller<PrimitiveComponentWrapper>("Function TAGame.StaticMeshComponent_TA.OnAttached", [this](PrimitiveComponentWrapper caller, void* params, std::string eventname) {
		caller.SetScale(1.1);
		});
}


/// <summary>
/// Exit code
/// </summary>
void AlgoMod::onUnload() {
	if (GetKismetSequence() == true) {
		cvarManager->log("Plugin Unloaded in game. Exiting...");
		cvarManager->executeCommand("unreal_command disconnect;");
	}
}
