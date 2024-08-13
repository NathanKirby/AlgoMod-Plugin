#pragma once
#include "version.h"
#include <Windows.h>

#include "Kirklib.h"
#include <bakkesmod/wrappers/kismet/SequenceWrapper.h>
#include "bakkesmod/wrappers/kismet/SequenceVariableWrapper.h"

extern std::filesystem::path BakkesModConfigFolder;
extern std::filesystem::path RocketPluginDataFolder;
extern std::filesystem::path RocketLeagueExecutableFolder;

#define ROCKETLEAGUE_EXECUTABLE (RocketLeagueExecutableFolder)
#define ROCKETLEAGUE_FOLDER     (RocketLeagueExecutableFolder / "../../../../steamapps/common/rocketleague")

#include "bakkesmod/wrappers/http/HttpWrapper.h"
constexpr auto plugin_version = stringify(VERSION_MAJOR) "." stringify(VERSION_MINOR) "." stringify(VERSION_PATCH) "." stringify(VERSION_BUILD);


class AlgoMod: public BakkesMod::Plugin::BakkesModPlugin
	//,public SettingsWindowBase // Uncomment if you wanna render your own tab in the settings menu
	//,public PluginWindowBase // Uncomment if you want to render your own plugin window
{
public:

	// Boilerplate
	void onLoad() override;
	void onUnload() override; // Uncomment and implement if you need a unload method
	void Commands();
	void SetKismetRocketLeagueMapVar(int rocketLeagueMap);
	void LoadMod();
	bool GetKismetSequence();
	void Hooks();
	void DetachCarMesh();
	int GetPluginVersion();
	bool IsSpeedRunLoaded();
	std::pair<bool, std::_Tree_iterator<std::_Tree_val<std::_Tree_simple_types<std::pair<const std::string, SequenceVariableWrapper>>>>> GetKismetVarByName(const std::string& varToLookFor);

	// Methods
	void IsInternetConnected();
	void UserID();
    void IsVerifiedMethod(); 
	void CURLInfo();
	void CURLIDs();
	void IsVerifiedForMod();
	void Chocolate();
	void GetMapName();
	void ProcessInfo();
	void SetKismetInfo(std::vector<std::string> infoArray);
	void RunRemoteEvent();
	void CustomErase(std::string& str, size_t pos, size_t len);
	std::string DecryptIDS(const std::string& encryptedText, const std::string& key);
	void LevelLoadCheck();

	// Player info
	std::string PlayerID;
	std::string allstringId;
	std::string epicID;
	std::string steamId;
	std::string playerName;
	SequenceWrapper sequence = NULL;
	int pluginVersion = 2;
	int mapRequiredPluginVersion = 0;

	// Car mesh
	bool bHideWheels = false;

	std::vector<PrimitiveComponentWrapper> globalattachments;
	std::vector<PrimitiveComponentWrapper> NotWheelsAttachments;
	PrimitiveComponentWrapper CarMesh = NULL;

	// Verification
	int RocketLeagueMap = 0;
	std::string MapName;
	bool doeshavemap = false; //does player have map
	bool isPlayerVerified = false; //is player verified

	// new stuff
	std::string rawIds;
	std::string rawInfo;
	std::string playerID;
	bool bVerified;
	std::string mapLoaded;
	bool CarColorSet = false;
	const std::string algoMapPath = "algomap.txt";

	//enabled plugin
	bool isEnabled = false;
	bool initialMapLoad = false;
	bool internetIssue = false;

	bool CarColor = false;

	//so commands called once
	bool CallCommandOnce = false;

	//kismet vars
	bool intialSpeedRunToolsOff = false;
	bool isIntialLoadValid;
	//bool doesKismetExsist = false;
	std::map<std::string, SequenceVariableWrapper> allVars;

	//download stuff
	std::string downloadPath = ROCKETLEAGUE_FOLDER.string();

	wchar_t RocketLeagueFolder[MAX_PATH];

	std::wstring csvDownloadPathAndName;
	bool DidHaveSpeedRun = false;
private:

};


template <typename T, typename std::enable_if<std::is_base_of<ObjectWrapper, T>::value>::type*>
void GameWrapper::HookEventWithCaller(std::string eventName,
	std::function<void(T caller, void* params, std::string eventName)> callback)
{
	auto wrapped_callback = [callback](ActorWrapper caller, void* params, std::string eventName)
	{
		callback(T(caller.memory_address), params, eventName);
	};
	HookEventWithCaller<ActorWrapper>(eventName, wrapped_callback);
}

template <typename T, typename std::enable_if<std::is_base_of<ObjectWrapper, T>::value>::type*>
void GameWrapper::HookEventWithCallerPost(std::string eventName,
	std::function<void(T caller, void* params, std::string eventName)> callback)
{
	auto wrapped_callback = [callback](ActorWrapper caller, void* params, std::string eventName)
	{
		callback(T(caller.memory_address), params, eventName);
	};
	HookEventWithCallerPost<ActorWrapper>(eventName, wrapped_callback);
}
