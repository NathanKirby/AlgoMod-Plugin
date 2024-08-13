#include "pch.h"
#include "AlgoMod.h"

void AlgoMod::LevelLoadCheck() {
	initialMapLoad = false;

	// Run code on a 0.5 second timeout (ensures everything is loaded before things are checked)
	gameWrapper->SetTimeout([this](GameWrapper*) {
		isIntialLoadValid = GetKismetSequence();

		// If there is kismet in the map and it's not main menu, run algo mod init
		if (GetKismetSequence() == true && (gameWrapper->GetCurrentMap() != "menu_main_p")) {
			// Car color
			CarColor = cvarManager->getCvar("cl_freeplay_carcolor").getBoolValue();
			cvarManager->executeCommand("cl_freeplay_carcolor 0");
			CarColorSet = true;

			Chocolate();
			CURLIDs();
			UserID();
			IsVerifiedMethod();
			CURLInfo();

			// Waits until rawIDS and rawInfo are set (cURL)
			do {
				std::this_thread::sleep_for(std::chrono::milliseconds(100));
			} while (rawIds.empty() || rawInfo.empty());

			// If verified, check to see if user is verified for this specific mod
			if (bVerified) {
				GetMapName();
				IsVerifiedForMod();
				ProcessInfo();
			}

			intialSpeedRunToolsOff = false;
		}

		// Turn on freeplay car color when leveload and CarCar == true (means car color was turned off by the pluing previously)
		if (CarColorSet) {
			if (CarColor == true && (GetKismetSequence() == false)) {
				cvarManager->executeCommand("cl_freeplay_carcolor 1;");
				CarColorSet = false;
			}
		}

		// Turns back on speedruntools plugin if it was turned off by the plugin
		if (GetKismetSequence() == false) {
			if (DidHaveSpeedRun == true) {
				cvarManager->executeCommand("plugin load speedruntools;");
				DidHaveSpeedRun = false;
			}

			isIntialLoadValid = false;
		}

		// Check plugin version
		if (GetPluginVersion() <= pluginVersion) {
			std::pair<bool, std::_Tree_iterator<std::_Tree_val<std::_Tree_simple_types<std::pair<const std::string, SequenceVariableWrapper>>>>> IsPluginUpToDateKismetVar = GetKismetVarByName("ispluginuptodate");
			if (IsPluginUpToDateKismetVar.first == true) {
				IsPluginUpToDateKismetVar.second->second.SetBool(true);
				LOG("plugin version up to date");
			}
		}
		else {
			std::pair<bool, std::_Tree_iterator<std::_Tree_val<std::_Tree_simple_types<std::pair<const std::string, SequenceVariableWrapper>>>>> IsPluginUpToDateKismetVar = GetKismetVarByName("ispluginuptodate");
			if (IsPluginUpToDateKismetVar.first == true) {
				LOG("Error: plugin version({}) NOT up to date");//check if crash
				IsPluginUpToDateKismetVar.second->second.SetBool(false);
			}
		}
		}, 0.5);
}



/*
* Helper methods for level load initialization
* Methods below are set in the order of which they're called
*/


/// <summary>
/// Gets sequence, kismet vars, and returns whether or not it's a algomod map you loaded into.
/// </summary>
/// <returns>Returns false if not in an algomod map, true if it is and everything is successful.</returns>
bool AlgoMod::GetKismetSequence() {
	if (!gameWrapper->GetGameEventAsServer()) {
		return false;
	}

	sequence = gameWrapper->GetMainSequence();
	if (sequence.memory_address == NULL) {
		return false;
	}

	allVars = sequence.GetAllSequenceVariables(false);

	std::map<std::string, SequenceVariableWrapper>::iterator kismetChocolateStringValue = allVars.find("REDACTED");
	if (kismetChocolateStringValue == allVars.end()) {
		return false;
	}

	return true;
}


/// <summary>
/// Sets the value of a kismet variable named "REDACTED" to "algo" to tell kismet the plugin is valid.
/// </summary>
void AlgoMod::Chocolate() {
	// Return if no kismet is available
	if (!gameWrapper->GetMainSequence()) {
		return;
	}

	// Find the chocolate variable
	std::map<std::string, SequenceVariableWrapper>::iterator kismetChocolateValue = allVars.find("REDACTED");

	// Return if it wasn't found
	if (kismetChocolateValue == allVars.end()) {
		return;
	}

	// Set variable to "algo" which allows the map to start up and attach car if the plugin is enabled and the user has internet
	if (isEnabled) {
		kismetChocolateValue->second.SetString("algo");
	}

	// If the plugin is not enabled, show why
	if (!isEnabled) {
		if (internetIssue) {
			LOG("Error: This mod requires an internet connection to use");
			LOG("Exiting to Main Menu...");

			kismetChocolateValue->second.SetString("internet");
		}
		else {
			LOG("Error: Plugin version disabled. Please get an up to date version");
			LOG("Closing Game...");
		}

		// Close match since they're not verified
		gameWrapper->SetTimeout([this](GameWrapper*) {
			cvarManager->executeCommand("unreal_command disconnect;");
			}, 5.0);
	}
}


/// <summary>
/// Gets user ID
/// </summary>
/// <remarks>User ID is stored in <see cref"PlayerID"/> and can represent either a Steam or Epic ID</remarks>
void AlgoMod::UserID() {
	// Returns if you're in a game
	if (!gameWrapper->GetGameEventAsServer() || !gameWrapper->GetCurrentGameState()) {
		return;
	}

	// Get car wrapper
	CarWrapper car = gameWrapper->GetLocalCar();
	if (!car) {
		return;
	}

	// Create instance of ID wrapper
	UniqueIDWrapper id = car.GetPRI().GetUniqueIdWrapper();
	PriWrapper pri = car.GetPRI();

	// Set variables
	playerName = pri.GetPlayerName().ToString();
	epicID = id.GetEpicAccountID();
	allstringId = id.GetIdString();

	// Get as string
	std::string stringId = id.GetIdString();
	std::vector<std::string> values;

	// Find the position of the first "|" character
	size_t pos = stringId.find("|");

	// Split the string at each "|" character
	while (pos != std::string::npos) {
		// Extract the substring before the "|" character
		std::string value = stringId.substr(0, pos);
		values.push_back(value);

		// Remove the processed part of the string
		stringId = stringId.substr(pos + 1);

		// Find the next "|" character
		pos = stringId.find("|");
	}

	// Add the remaining part of the string to the vector
	values.push_back(stringId);
	steamId = values[1];

	if (steamId != "" && steamId.length() > 15) {
		PlayerID = steamId;
	}
	else if (epicID != "" && epicID.length() > 8) {
		PlayerID = epicID;
	}
}


/// <summary>
/// Checks to see if ids.txt from algorl.com contains the user's player ID
/// </summary>
/// <remarks>Result is set to <see cref"bVerified"/></remarks>
void AlgoMod::IsVerifiedMethod() {
	if (rawIds.find(playerID) != std::string::npos) {
		LOG("bVerifeid = true");
		bVerified = true;
	}
	else {
		LOG("bVerifeid = false");
		bVerified = false;
	}
}


/*
* Methods below run if you're verified
* Checks to see if you're verified for the mod you're currently in
*/


/// <summary>
/// Gets the algomod map name and sets which map to load in the perpare map change kismet
/// </summary>
void AlgoMod::GetMapName() {
	std::map<std::string, SequenceVariableWrapper>::iterator kismetstringvalue = allVars.find("REDACTED");
	std::map<std::string, SequenceVariableWrapper>::iterator kismetRocketLeagueMap = allVars.find("REDACTED");

	// Returns if no kismet is found
	if (kismetstringvalue == allVars.end() || kismetRocketLeagueMap == allVars.end()) {
		return;
	}

	// Sets mapLoaded to the name of the mod you're loading into
	mapLoaded = kismetstringvalue->second.GetString();

	// Sets kismet int to user map selection before it loads
	kismetRocketLeagueMap->second.SetInt(RocketLeagueMap);
}


/// <summary>
/// Finds current user's line and checks to see if it contains the map name
/// </summary>
void AlgoMod::IsVerifiedForMod() {
	std::vector<std::string> idsList;

	// Splitting the rawIds string by comma
	size_t pos = 0;
	while ((pos = rawIds.find(',')) != std::string::npos) {
		std::string token = rawIds.substr(0, pos);
		idsList.push_back(token);
		rawIds.erase(0, pos + 1);
	}
	// Adding the last token
	idsList.push_back(rawIds);

	// Checking each idline in the idsList
	for (const std::string& idline : idsList) {
		if (!idline.empty()) {
			if (idline.find(playerID) != std::string::npos) {
				LOG(idline);
				LOG(mapLoaded);
				if (idline.find(mapLoaded) != std::string::npos) {
					// Has access to mod
					LOG("HAS ACCESS TO MOD");
					// runs with a delay
					gameWrapper->SetTimeout([this](GameWrapper*) {
						RunRemoteEvent();
						}, 0.2);
				}
				else {
					// Doesn't have access to mod
					LOG("DOES NOT HAS ACCESS TO MOD");
				}
			}
		}

		break;
	}
}


/// <summary>
/// Runs kismet remote event to start the mod
/// </summary>
void AlgoMod::RunRemoteEvent() {
	// Find extracheck vars
	std::map<std::string, SequenceVariableWrapper>::iterator extracheck = allVars.find("REDACTED");
	std::map<std::string, SequenceVariableWrapper>::iterator extracheck2 = allVars.find("REDACTED");

	// If they're not found, return
	if (extracheck == allVars.end() || extracheck2 == allVars.end()) {
		return;
	}

	// Set extra check vars to values which will be checked in kismet
	extracheck->second.SetString("REDACTED");
	extracheck2->second.SetString("REDACTED");

	// Activate verification remote events in kismet
	sequence.ActivateRemoteEvents("REDACTED");
	sequence.ActivateRemoteEvents("REDACTED");
}


/*
* Methods below run if you're verified for the specific mod you're in
* Initializes algomod kismet
*/


/// <summary>
/// Processes raw info from algorl.com/algomod/info.txt and adds them into an array for further processing
/// </summary>
void AlgoMod::ProcessInfo() {
	if (!rawInfo.empty()) {
		std::string delimiter = "|||";
		std::vector<std::string> parts;
		size_t pos = 0;
		size_t found;

		while ((found = rawInfo.find(delimiter, pos)) != std::string::npos) {
			parts.push_back(rawInfo.substr(pos, found - pos));
			pos = found + delimiter.length();
		}
		parts.push_back(rawInfo.substr(pos));

		std::string info = parts[1];

		std::stringstream ss(info);
		std::string token;
		std::vector<std::string> infoparts;

		while (std::getline(ss, token, '|')) {
			infoparts.push_back(token);
		}

		SetKismetInfo(infoparts);
	}
}


/// <summary>
/// Sets kismet info variables from website info
/// </summary>
/// <param name="InfoArray">Array of info gathered from website</param>
void AlgoMod::SetKismetInfo(std::vector<std::string> infoArray) {
	gameWrapper->SetTimeout([this, infoArray](GameWrapper*) {
		std::map<std::string, SequenceVariableWrapper>::iterator info0 = allVars.find("info0");
		if (info0 != allVars.end() && infoArray[0] != "" && infoArray.size() >= 1) {
			info0->second.SetString(infoArray[0]);
		}
		std::map<std::string, SequenceVariableWrapper>::iterator info1 = allVars.find("info1");
		if (info1 != allVars.end() && infoArray[1] != "" && infoArray.size() >= 2) {
			info1->second.SetString(infoArray[1]);
		}
		std::map<std::string, SequenceVariableWrapper>::iterator info2 = allVars.find("info2");
		if (info2 != allVars.end() && infoArray[2] != "" && infoArray.size() >= 3) {
			info2->second.SetString(infoArray[2]);
		}
		std::map<std::string, SequenceVariableWrapper>::iterator info3 = allVars.find("info3");
		if (info3 != allVars.end() && infoArray[3] != "" && infoArray.size() >= 4) {
			info3->second.SetString(infoArray[3]);
		}
		std::map<std::string, SequenceVariableWrapper>::iterator info4 = allVars.find("info4");
		if (info4 != allVars.end() && infoArray[4] != "" && infoArray.size() >= 5) {
			info4->second.SetString(infoArray[4]);
		}
		}, 0.5);
}


/*
* Speedruntools code
*/


/// <summary>
/// Checks to see if the speedruntools plugin is enabled or not
/// </summary>
/// <returns>Returns a bool based on if the speedruntools plugin is enabled or not</returns>
bool AlgoMod::IsSpeedRunLoaded() {
	PluginManagerWrapper pluginManager = gameWrapper->GetPluginManager();
	if (pluginManager.memory_address == NULL) {
		return false;
	}

	std::vector<std::shared_ptr<BakkesMod::Plugin::LoadedPlugin>>* pluginList = pluginManager.GetLoadedPlugins();
	for (const std::vector<std::shared_ptr<BakkesMod::Plugin::LoadedPlugin>>::iterator::value_type& thisPlugin : *pluginList) {
		if (std::string(thisPlugin->_details->className) == "SpeedrunTools") {
			return true;
		}
	}

	return false;
}


/*
* Command and Hook code
*/


/// <summary>
/// algo_load command code to load up an algomod match
/// </summary>
void AlgoMod::LoadMod() {
	if (gameWrapper->IsInOnlineGame()) {
		LOG("Warning: Can't Load mod from online match. Please exit to main menu");
		return;
	}

	if (isEnabled) {
		gameWrapper->SetTimeout([this](GameWrapper*) {
			gameWrapper->ExecuteUnrealCommand("open Labs_Underpass_P?Playtest?game=TAGame.GameInfo_Soccar_TA?GameTags=BotsNone,FreePlay");
			}, 0.1f);
	}
}


/// <summary>
/// Detach car mesh under the map when kismet hook requests
/// </summary>
void AlgoMod::DetachCarMesh() {
	if (GetKismetSequence() && CarMesh) {
		ServerWrapper server = gameWrapper->GetGameEventAsServer();
		if (server) {
			CarWrapper car = server.GetGameCar();
			if (car) {
				Vector underFieldLoc(0.0f, 0.0f, -200.0f);

				// Sets car location to under the field
				Vector oldLocation = car.GetLocation();
				underFieldLoc = { oldLocation.X, oldLocation.Y, underFieldLoc.Z };
				car.SetLocation(underFieldLoc);

				// Delays hiding/detaching car by 0.01 seconds to ensure location is properly set
				gameWrapper->SetTimeout([this, oldLocation, underFieldLoc](GameWrapper*) {
					CarMesh.SetHiddenGame(true);
					}, 0.01);
			}
		}
	}
}


/*
* Kismet integrated code
*/


/// <summary>
/// Gets all named variables in a map's kismet, searches for specified variable and returns it's value if found
/// </summary>
std::pair<bool, std::_Tree_iterator<std::_Tree_val<std::_Tree_simple_types<std::pair<const std::string, SequenceVariableWrapper>>>>> AlgoMod::GetKismetVarByName(const std::string& varToLookFor) {
	if (!GetKismetSequence() || !gameWrapper->GetGameEventAsServer() || !gameWrapper->GetMainSequence()) {
		return { false, {} };
	}

	std::map<std::string, SequenceVariableWrapper> allKismetVars = sequence.GetAllSequenceVariables(false);
	std::map<std::string, SequenceVariableWrapper>::iterator kismetVar = allKismetVars.find(varToLookFor);

	if (kismetVar == allKismetVars.end()) {
		return { false, {} };
	}
	else {
		return { true, kismetVar };
	}
}


/// <summary>
/// Used for selecting different rocket league maps to play in
/// </summary>
/// <param name="RocketLeagueMap">Int used in kismet to select a map to load</param>
void AlgoMod::SetKismetRocketLeagueMapVar(int rocketLeagueMap) {
	if (!allVars.empty() && isEnabled && gameWrapper->GetMainSequence() && sequence.memory_address != NULL) {
		// Find map num variable in kismet
		std::map<std::string, SequenceVariableWrapper>::iterator kismetRocketLeagueMap = allVars.find("RocketLeagueMapNum");

		if (kismetRocketLeagueMap != allVars.end()) {
			// Sets value of rocketleaguemap after command entered
			kismetRocketLeagueMap->second.SetInt(rocketLeagueMap);

			// Set algomap.txt to new map
			Kirklib::delete_file(algoMapPath);
			Kirklib::string_to_file(algoMapPath, std::to_string(rocketLeagueMap));

			LoadMod();
		}
	}
}


/// <summary>
/// Get plugin version variable value
/// </summary>
/// <returns>Returns plugin version found from kismet</returns>
int AlgoMod::GetPluginVersion() {
	std::pair<bool, std::_Tree_iterator<std::_Tree_val<std::_Tree_simple_types<std::pair<const std::string, SequenceVariableWrapper>>>>> kismetMapVersion = GetKismetVarByName("REDACTED");

	if (kismetMapVersion.first == true) {
		mapRequiredPluginVersion = kismetMapVersion.second->second.GetInt();
	}
	else {
		mapRequiredPluginVersion = 0;
	}

	return mapRequiredPluginVersion;
}


/*
* Decryption
*/


/// <summary>
/// Decrypts IDs file content
/// </summary>
/// <param name="encryptedText">Encrypted text</param>
/// <param name="key">Decryption key</param>
/// <returns>Plain text</returns>
std::string AlgoMod::DecryptIDS(const std::string& encryptedText, const std::string& key) {
	std::string decryptedText = "";

	// CODE REDACTED

	return decryptedText;
}

/// <summary>Helper method for DecryptIDS</summary>
void AlgoMod::CustomErase(std::string& str, size_t pos, size_t len) {
	str = str.substr(0, pos) + str.substr(pos + len);
}
