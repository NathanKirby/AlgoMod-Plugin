#include "pch.h"
#include "AlgoMod.h"

void AlgoMod::Commands() {
	if (isEnabled == false) {
		return;
	}

	cvarManager->registerNotifier("algo_folder", [this](std::vector<std::string> args) {
		LOG(RocketLeagueFolder);
		}, "", PERMISSION_ALL);

	cvarManager->registerNotifier("algo_load", [this](std::vector<std::string> args) {
		LoadMod();
		}, "", PERMISSION_ALL);

	cvarManager->registerNotifier("Algo_Loadp", [this](std::vector<std::string> args) {
		std::string mapArgs = Kirklib::read_all_text(algoMapPath);
		if (mapArgs.empty()) {
			mapArgs = "0";
		}
		RocketLeagueMap = std::stoi(mapArgs);

		SetKismetRocketLeagueMapVar(RocketLeagueMap);
		LoadMod();
		}, "", PERMISSION_ALL);

	// Algo map commands
	cvarManager->registerNotifier("algo_map_beckwith_park", [this](std::vector<std::string> args) {
		RocketLeagueMap = 0;
		SetKismetRocketLeagueMapVar(RocketLeagueMap);
		LOG("ROCKET LEAGUE MAP: {}", "Beckwith Park - You may need to restart training to apply");
		}, "", PERMISSION_ALL);

	cvarManager->registerNotifier("algo_map_aquadome", [this](std::vector<std::string> args) {
		RocketLeagueMap = 1;
		SetKismetRocketLeagueMapVar(RocketLeagueMap);
		LOG("ROCKET LEAGUE MAP: {}", "Aquadome - You may need to restart training to apply");
		}, "", PERMISSION_ALL);

	cvarManager->registerNotifier("algo_map_beckwith_park_night", [this](std::vector<std::string> args) {
		RocketLeagueMap = 2;
		SetKismetRocketLeagueMapVar(RocketLeagueMap);
		LOG("ROCKET LEAGUE MAP: {}", "Beckwith Park Night - You may need to restart training to apply");
		}, "", PERMISSION_ALL);

	cvarManager->registerNotifier("algo_map_beckwith_park_stormy", [this](std::vector<std::string> args) {
		RocketLeagueMap = 3;
		SetKismetRocketLeagueMapVar(RocketLeagueMap);
		LOG("ROCKET LEAGUE MAP: {}", "Beckwith Park Stormy - You may need to restart training to apply");
		}, "", PERMISSION_ALL);

	cvarManager->registerNotifier("algo_map_champions_field", [this](std::vector<std::string> args) {
		RocketLeagueMap = 4;
		SetKismetRocketLeagueMapVar(RocketLeagueMap);
		LOG("ROCKET LEAGUE MAP: {}", "Champions Field - You may need to restart training to apply");
		}, "", PERMISSION_ALL);

	cvarManager->registerNotifier("algo_map_champions_field_day", [this](std::vector<std::string> args) {
		RocketLeagueMap = 5;
		SetKismetRocketLeagueMapVar(RocketLeagueMap);
		LOG("ROCKET LEAGUE MAP: {}", "Champions Field Day - You may need to restart training to apply");
		}, "", PERMISSION_ALL);

	cvarManager->registerNotifier("algo_map_dfh_stadium", [this](std::vector<std::string> args) {
		RocketLeagueMap = 6;
		SetKismetRocketLeagueMapVar(RocketLeagueMap);
		LOG("ROCKET LEAGUE MAP: {}", "DFH Stadium - You may need to restart training to apply");
		}, "", PERMISSION_ALL);

	cvarManager->registerNotifier("algo_map_dfh_stadium_day", [this](std::vector<std::string> args) {
		RocketLeagueMap = 7;
		SetKismetRocketLeagueMapVar(RocketLeagueMap);
		LOG("ROCKET LEAGUE MAP: {}", "DFH Stadium Day - You may need to restart training to apply");
		}, "", PERMISSION_ALL);

	cvarManager->registerNotifier("algo_map_dfh_stadium_stormy", [this](std::vector<std::string> args) {
		RocketLeagueMap = 8;
		SetKismetRocketLeagueMapVar(RocketLeagueMap);
		LOG("ROCKET LEAGUE MAP: {}", "DFH Stadium Stormy - You may need to restart training to apply");
		}, "", PERMISSION_ALL);

	cvarManager->registerNotifier("algo_map_dfh_stadium_snowy", [this](std::vector<std::string> args) {
		RocketLeagueMap = 9;
		SetKismetRocketLeagueMapVar(RocketLeagueMap);
		LOG("ROCKET LEAGUE MAP: {}", "DFH Stadium Snowy - You may need to restart training to apply");
		}, "", PERMISSION_ALL);

	cvarManager->registerNotifier("algo_map_dropshot_core_707", [this](std::vector<std::string> args) {
		RocketLeagueMap = 10;
		SetKismetRocketLeagueMapVar(RocketLeagueMap);
		LOG("ROCKET LEAGUE MAP: {}", "Dropshot Core 707 - You may need to restart training to apply");
		}, "", PERMISSION_ALL);

	cvarManager->registerNotifier("algo_map_hoops_dunk_house", [this](std::vector<std::string> args) {
		RocketLeagueMap = 11;
		SetKismetRocketLeagueMapVar(RocketLeagueMap);
		LOG("ROCKET LEAGUE MAP: {}", "Hoops Dunk House - You may need to restart training to apply");
		}, "", PERMISSION_ALL);

	cvarManager->registerNotifier("algo_map_farmstead", [this](std::vector<std::string> args) {
		RocketLeagueMap = 12;
		SetKismetRocketLeagueMapVar(RocketLeagueMap);
		LOG("ROCKET LEAGUE MAP: {}", "Farmstead - You may need to restart training to apply");
		}, "", PERMISSION_ALL);

	cvarManager->registerNotifier("algo_map_farmstead_night", [this](std::vector<std::string> args) {
		RocketLeagueMap = 13;
		SetKismetRocketLeagueMapVar(RocketLeagueMap);
		LOG("ROCKET LEAGUE MAP: {}", "Farmstead Night - You may need to restart training to apply");
		}, "", PERMISSION_ALL);

	cvarManager->registerNotifier("algo_map_farmstead_upside_down", [this](std::vector<std::string> args) {
		RocketLeagueMap = 14;
		SetKismetRocketLeagueMapVar(RocketLeagueMap);
		LOG("ROCKET LEAGUE MAP: {}", "Farmstead Upside Down - You may need to restart training to apply");
		}, "", PERMISSION_ALL);

	cvarManager->registerNotifier("algo_map_forbidden_temple", [this](std::vector<std::string> args) {
		RocketLeagueMap = 15;
		SetKismetRocketLeagueMapVar(RocketLeagueMap);
		LOG("ROCKET LEAGUE MAP: {}", "Forbidden Temple - You may need to restart training to apply");
		}, "", PERMISSION_ALL);

	cvarManager->registerNotifier("algo_map_forbidden_temple_day", [this](std::vector<std::string> args) {
		RocketLeagueMap = 16;
		SetKismetRocketLeagueMapVar(RocketLeagueMap);
		LOG("ROCKET LEAGUE MAP: {}", "Forbidden Temple Day - You may need to restart training to apply");
		}, "", PERMISSION_ALL);

	cvarManager->registerNotifier("algo_map_labs_circle_pillars", [this](std::vector<std::string> args) {
		RocketLeagueMap = 17;
		SetKismetRocketLeagueMapVar(RocketLeagueMap);
		LOG("ROCKET LEAGUE MAP: {}", "Labs Circle Pillars - You may need to restart training to apply");
		}, "", PERMISSION_ALL);

	cvarManager->registerNotifier("algo_map_labs_basin", [this](std::vector<std::string> args) {
		RocketLeagueMap = 18;
		SetKismetRocketLeagueMapVar(RocketLeagueMap);
		LOG("ROCKET LEAGUE MAP: {}", "Labs Basin - You may need to restart training to apply");
		}, "", PERMISSION_ALL);

	cvarManager->registerNotifier("algo_map_labs_corridor", [this](std::vector<std::string> args) {
		RocketLeagueMap = 19;
		SetKismetRocketLeagueMapVar(RocketLeagueMap);
		LOG("ROCKET LEAGUE MAP: {}", "Labs Corridor - You may need to restart training to apply");
		}, "", PERMISSION_ALL);

	cvarManager->registerNotifier("algo_map_labs_cosmic", [this](std::vector<std::string> args) {
		RocketLeagueMap = 20;
		SetKismetRocketLeagueMapVar(RocketLeagueMap);
		LOG("ROCKET LEAGUE MAP: {}", "Labs Cosmic - You may need to restart training to apply");
		}, "", PERMISSION_ALL);

	cvarManager->registerNotifier("algo_map_labs_cosmicv2", [this](std::vector<std::string> args) {
		RocketLeagueMap = 21;
		SetKismetRocketLeagueMapVar(RocketLeagueMap);
		LOG("ROCKET LEAGUE MAP: {}", "Labs Cosmicv2 - You may need to restart training to apply");
		}, "", PERMISSION_ALL);

	cvarManager->registerNotifier("algo_map_labs_double_goal", [this](std::vector<std::string> args) {
		RocketLeagueMap = 22;
		SetKismetRocketLeagueMapVar(RocketLeagueMap);
		LOG("ROCKET LEAGUE MAP: {}", "Labs Double Goal - You may need to restart training to apply");
		}, "", PERMISSION_ALL);

	cvarManager->registerNotifier("algo_map_labs_double_goal_v2", [this](std::vector<std::string> args) {
		RocketLeagueMap = 23;
		SetKismetRocketLeagueMapVar(RocketLeagueMap);
		LOG("ROCKET LEAGUE MAP: {}", "LabsDoubleGoalV2 - You may need to restart training to apply");
		}, "", PERMISSION_ALL);

	cvarManager->registerNotifier("algo_map_labs_galleon", [this](std::vector<std::string> args) {
		RocketLeagueMap = 24;
		SetKismetRocketLeagueMapVar(RocketLeagueMap);
		LOG("ROCKET LEAGUE MAP: {}", "LabsGalleon - You may need to restart training to apply");
		}, "", PERMISSION_ALL);

	cvarManager->registerNotifier("algo_map_labs_octagon", [this](std::vector<std::string> args) {
		RocketLeagueMap = 25;
		SetKismetRocketLeagueMapVar(RocketLeagueMap);
		LOG("ROCKET LEAGUE MAP: {}", "LabsOctagon - You may need to restart training to apply");
		}, "", PERMISSION_ALL);

	cvarManager->registerNotifier("algo_map_labs_octagon_v2", [this](std::vector<std::string> args) {
		RocketLeagueMap = 26;
		SetKismetRocketLeagueMapVar(RocketLeagueMap);
		LOG("ROCKET LEAGUE MAP: {}", "LabsOctagonv2 - You may need to restart training to apply");
		}, "", PERMISSION_ALL);

	cvarManager->registerNotifier("algo_map_labs_utopia", [this](std::vector<std::string> args) {
		RocketLeagueMap = 27;
		SetKismetRocketLeagueMapVar(RocketLeagueMap);
		LOG("ROCKET LEAGUE MAP: {}", "LabsUtopia - You may need to restart training to apply");
		}, "", PERMISSION_ALL);

	cvarManager->registerNotifier("algo_map_mannfield", [this](std::vector<std::string> args) {
		RocketLeagueMap = 28;
		SetKismetRocketLeagueMapVar(RocketLeagueMap);
		LOG("ROCKET LEAGUE MAP: {}", "Mannfield - You may need to restart training to apply");
		}, "", PERMISSION_ALL);

	cvarManager->registerNotifier("algo_map_mannfield_night", [this](std::vector<std::string> args) {
		RocketLeagueMap = 29;
		SetKismetRocketLeagueMapVar(RocketLeagueMap);
		LOG("ROCKET LEAGUE MAP: {}", "MannfieldNight - You may need to restart training to apply");
		}, "", PERMISSION_ALL);

	cvarManager->registerNotifier("algo_map_mannfield_stormy", [this](std::vector<std::string> args) {
		RocketLeagueMap = 30;
		SetKismetRocketLeagueMapVar(RocketLeagueMap);
		LOG("ROCKET LEAGUE MAP: {}", "MannfieldStormy - You may need to restart training to apply");
		}, "", PERMISSION_ALL);


	cvarManager->registerNotifier("algo_map_mannfield_snowy", [this](std::vector<std::string> args) {
		RocketLeagueMap = 31;
		SetKismetRocketLeagueMapVar(RocketLeagueMap);
		LOG("ROCKET LEAGUE MAP: {}", "MannfieldSnowy - You may need to restart training to apply");
		}, "", PERMISSION_ALL);

	cvarManager->registerNotifier("algo_map_neon_fields", [this](std::vector<std::string> args) {
		RocketLeagueMap = 32;
		SetKismetRocketLeagueMapVar(RocketLeagueMap);
		LOG("ROCKET LEAGUE MAP: {}", "NeonFields - You may need to restart training to apply");
		}, "", PERMISSION_ALL);

	cvarManager->registerNotifier("algo_map_tokyo_underpass", [this](std::vector<std::string> args) {
		RocketLeagueMap = 33;
		SetKismetRocketLeagueMapVar(RocketLeagueMap);
		LOG("ROCKET LEAGUE MAP: {}", "TokyoUnderpass - You may need to restart training to apply");
		}, "", PERMISSION_ALL);

	cvarManager->registerNotifier("algo_map_neo_tokyo", [this](std::vector<std::string> args) {
		RocketLeagueMap = 34;
		SetKismetRocketLeagueMapVar(RocketLeagueMap);
		LOG("ROCKET LEAGUE MAP: {}", "NeoTokyo - You may need to restart training to apply");
		}, "", PERMISSION_ALL);

	cvarManager->registerNotifier("algo_map_deadeye_canyon", [this](std::vector<std::string> args) {
		RocketLeagueMap = 35;
		SetKismetRocketLeagueMapVar(RocketLeagueMap);
		LOG("ROCKET LEAGUE MAP: {}", "deadeye_canyon - You may need to restart training to apply");
		}, "", PERMISSION_ALL);

	cvarManager->registerNotifier("algo_map_salty_shores", [this](std::vector<std::string> args) {
		RocketLeagueMap = 36;
		SetKismetRocketLeagueMapVar(RocketLeagueMap);
		LOG("ROCKET LEAGUE MAP: {}", "salty_shores - You may need to restart training to apply");
		}, "", PERMISSION_ALL);

	cvarManager->registerNotifier("algo_map_salty_shores_night", [this](std::vector<std::string> args) {
		RocketLeagueMap = 37;
		SetKismetRocketLeagueMapVar(RocketLeagueMap);
		LOG("ROCKET LEAGUE MAP: {}", "salty_shores_night - You may need to restart training to apply");
		}, "", PERMISSION_ALL);

	cvarManager->registerNotifier("algo_map_throwback_stadium", [this](std::vector<std::string> args) {
		RocketLeagueMap = 38;
		SetKismetRocketLeagueMapVar(RocketLeagueMap);
		LOG("ROCKET LEAGUE MAP: {}", "throwback_stadium - You may need to restart training to apply");
		}, "", PERMISSION_ALL);

	cvarManager->registerNotifier("algo_map_urban_central", [this](std::vector<std::string> args) {
		RocketLeagueMap = 39;
		SetKismetRocketLeagueMapVar(RocketLeagueMap);
		LOG("ROCKET LEAGUE MAP: {}", "urban_central - You may need to restart training to apply");
		}, "", PERMISSION_ALL);

	cvarManager->registerNotifier("algo_map_urban_central_dawn", [this](std::vector<std::string> args) {
		RocketLeagueMap = 40;
		SetKismetRocketLeagueMapVar(RocketLeagueMap);
		LOG("ROCKET LEAGUE MAP: {}", "urban_central_dawn - You may need to restart training to apply");
		}, "", PERMISSION_ALL);

	cvarManager->registerNotifier("algo_map_urban_central_night", [this](std::vector<std::string> args) {
		RocketLeagueMap = 41;
		SetKismetRocketLeagueMapVar(RocketLeagueMap);
		LOG("ROCKET LEAGUE MAP: {}", "UrbanCentralNight - You may need to restart training to apply");
		}, "", PERMISSION_ALL);

	cvarManager->registerNotifier("algo_map_urban_central_spooky", [this](std::vector<std::string> args) {
		RocketLeagueMap = 42;
		SetKismetRocketLeagueMapVar(RocketLeagueMap);
		LOG("ROCKET LEAGUE MAP: {}", "UrbanCentralSpooky - You may need to restart training to apply");
		}, "", PERMISSION_ALL);

	cvarManager->registerNotifier("algo_map_urban_central_haunted", [this](std::vector<std::string> args) {
		RocketLeagueMap = 43;
		SetKismetRocketLeagueMapVar(RocketLeagueMap);
		LOG("ROCKET LEAGUE MAP: {}", "UrbanCentralHaunted - You may need to restart training to apply");
		}, "", PERMISSION_ALL);

	cvarManager->registerNotifier("algo_map_utopia_coliseum", [this](std::vector<std::string> args) {
		RocketLeagueMap = 44;
		SetKismetRocketLeagueMapVar(RocketLeagueMap);
		LOG("ROCKET LEAGUE MAP: {}", "UtopiaColiseum - You may need to restart training to apply");
		}, "", PERMISSION_ALL);

	cvarManager->registerNotifier("algo_map_utopia_coliseum_dusk", [this](std::vector<std::string> args) {
		RocketLeagueMap = 45;
		SetKismetRocketLeagueMapVar(RocketLeagueMap);
		LOG("ROCKET LEAGUE MAP: {}", "UtopiaColiseumDusk - You may need to restart training to apply");
		}, "", PERMISSION_ALL);

	cvarManager->registerNotifier("algo_map_utopia_coliseum_gilded", [this](std::vector<std::string> args) {
		RocketLeagueMap = 46;
		SetKismetRocketLeagueMapVar(RocketLeagueMap);
		LOG("ROCKET LEAGUE MAP: {}", "UtopiaColiseumNight - You may need to restart training to apply");
		}, "", PERMISSION_ALL);

	cvarManager->registerNotifier("algo_map_utopia_coliseum_snowy", [this](std::vector<std::string> args) {
		RocketLeagueMap = 47;
		SetKismetRocketLeagueMapVar(RocketLeagueMap);
		LOG("ROCKET LEAGUE MAP: {}", "UtopiaColiseumSnowy - You may need to restart training to apply");
		}, "", PERMISSION_ALL);

	cvarManager->registerNotifier("algo_map_badlands", [this](std::vector<std::string> args) {
		RocketLeagueMap = 48;
		SetKismetRocketLeagueMapVar(RocketLeagueMap);
		LOG("ROCKET LEAGUE MAP: {}", "Badlands - You may need to restart training to apply");
		}, "", PERMISSION_ALL);

	cvarManager->registerNotifier("algo_map_badlands_night", [this](std::vector<std::string> args) {
		RocketLeagueMap = 49;
		SetKismetRocketLeagueMapVar(RocketLeagueMap);
		LOG("ROCKET LEAGUE MAP: {}", "BadlandsNight - You may need to restart training to apply");
		}, "", PERMISSION_ALL);

	cvarManager->registerNotifier("algo_map_wasteland", [this](std::vector<std::string> args) {
		RocketLeagueMap = 50;
		SetKismetRocketLeagueMapVar(RocketLeagueMap);
		LOG("ROCKET LEAGUE MAP: {}", "Wasteland - You may need to restart training to apply");
		}, "", PERMISSION_ALL);

	cvarManager->registerNotifier("algo_map_wasteland_night", [this](std::vector<std::string> args) {
		RocketLeagueMap = 51;
		SetKismetRocketLeagueMapVar(RocketLeagueMap);
		LOG("ROCKET LEAGUE MAP: {}", "WastelandNight - You may need to restart training to apply");
		}, "", PERMISSION_ALL);

	cvarManager->registerNotifier("algo_map_sovereign_heights", [this](std::vector<std::string> args) {
		RocketLeagueMap = 52;
		SetKismetRocketLeagueMapVar(RocketLeagueMap);
		LOG("ROCKET LEAGUE MAP: {}", "SovereignHeights - You may need to restart training to apply");
		}, "", PERMISSION_ALL);

	cvarManager->registerNotifier("algo_map_forbidden_temple_fire_and_ice", [this](std::vector<std::string> args) {
		RocketLeagueMap = 53;
		SetKismetRocketLeagueMapVar(RocketLeagueMap);
		LOG("ROCKET LEAGUE MAP: {}", "ForbiddenTempleFireandIce - You may need to restart training to apply");
		}, "", PERMISSION_ALL);

	cvarManager->registerNotifier("algo_map_throwback_stadium_snowy", [this](std::vector<std::string> args) {
		RocketLeagueMap = 54;
		SetKismetRocketLeagueMapVar(RocketLeagueMap);
		LOG("ROCKET LEAGUE MAP: {}", "ThrowbackStadiumSnowy - You may need to restart training to apply");
		}, "", PERMISSION_ALL);

	cvarManager->registerNotifier("algo_map_hoops_the_block", [this](std::vector<std::string> args) {
		RocketLeagueMap = 55;
		SetKismetRocketLeagueMapVar(RocketLeagueMap);
		LOG("ROCKET LEAGUE MAP: {}", "HoopsTheBlock - You may need to restart training to apply");
		}, "", PERMISSION_ALL);


	cvarManager->registerNotifier("algo_map_starbase_arc", [this](std::vector<std::string> args) {
		RocketLeagueMap = 56;
		SetKismetRocketLeagueMapVar(RocketLeagueMap);
		LOG("ROCKET LEAGUE MAP: {}", "StarbaseARC - You may need to restart training to apply");
		}, "", PERMISSION_ALL);

	cvarManager->registerNotifier("algo_map_arctagon", [this](std::vector<std::string> args) {
		RocketLeagueMap = 57;
		SetKismetRocketLeagueMapVar(RocketLeagueMap);
		LOG("ROCKET LEAGUE MAP: {}", "Arctagon - You may need to restart training to apply");
		}, "", PERMISSION_ALL);

	cvarManager->registerNotifier("algo_map_starbase_arc_aftermath", [this](std::vector<std::string> args) {
		RocketLeagueMap = 58;
		SetKismetRocketLeagueMapVar(RocketLeagueMap);
		LOG("ROCKET LEAGUE MAP: {}", "StarbaseARCAftermath - You may need to restart training to apply");
		}, "", PERMISSION_ALL);


	cvarManager->registerNotifier("algo_map_beckwith_park_batman", [this](std::vector<std::string> args) {
		RocketLeagueMap = 59;
		SetKismetRocketLeagueMapVar(RocketLeagueMap);
		LOG("ROCKET LEAGUE MAP: {}", "Beckwith Park Batman - You may need to restart training to apply");
		}, "", PERMISSION_ALL);

	cvarManager->registerNotifier("algo_map_labs_underpass_old", [this](std::vector<std::string> args) {
		RocketLeagueMap = 60;
		SetKismetRocketLeagueMapVar(RocketLeagueMap);
		LOG("ROCKET LEAGUE MAP: {}", "Labs Underpass Old - You may need to restart training to apply");
		}, "", PERMISSION_ALL);

	cvarManager->registerNotifier("algo_map_labs_pillar_wings", [this](std::vector<std::string> args) {
		RocketLeagueMap = 61;
		SetKismetRocketLeagueMapVar(RocketLeagueMap);
		LOG("ROCKET LEAGUE MAP: {}", "Labs Pillar Wings - You may need to restart training to apply");
		}, "", PERMISSION_ALL);

	cvarManager->registerNotifier("algo_map_labs_pillar_heat", [this](std::vector<std::string> args) {
		RocketLeagueMap = 62;
		SetKismetRocketLeagueMapVar(RocketLeagueMap);
		LOG("ROCKET LEAGUE MAP: {}", "Labs Pillar Heat - You may need to restart training to apply");
		}, "", PERMISSION_ALL);

	cvarManager->registerNotifier("algo_map_labs_pillar_glass", [this](std::vector<std::string> args) {
		RocketLeagueMap = 63;
		SetKismetRocketLeagueMapVar(RocketLeagueMap);
		LOG("ROCKET LEAGUE MAP: {}", "Labs Pillar Glass - You may need to restart training to apply");
		}, "", PERMISSION_ALL);

	cvarManager->registerNotifier("algo_map_labs_holy_field", [this](std::vector<std::string> args) {
		RocketLeagueMap = 64;
		SetKismetRocketLeagueMapVar(RocketLeagueMap);
		LOG("ROCKET LEAGUE MAP: {}", "Labs Holy Field - You may need to restart training to apply");
		}, "", PERMISSION_ALL);

	cvarManager->registerNotifier("algo_map_labs_galleon_mast", [this](std::vector<std::string> args) {
		RocketLeagueMap = 65;
		SetKismetRocketLeagueMapVar(RocketLeagueMap);
		LOG("ROCKET LEAGUE MAP: {}", "Labs Galleon Mast - You may need to restart training to apply");
		}, "", PERMISSION_ALL);

	cvarManager->registerNotifier("algo_map_champions_field_gridiron", [this](std::vector<std::string> args) {
		RocketLeagueMap = 66;
		SetKismetRocketLeagueMapVar(RocketLeagueMap);
		LOG("ROCKET LEAGUE MAP: {}", "Champions Field Gridiron - You may need to restart training to apply");
		}, "", PERMISSION_ALL);

	cvarManager->registerNotifier("algo_map_beckwith_park_snowy", [this](std::vector<std::string> args) {
		RocketLeagueMap = 67;
		SetKismetRocketLeagueMapVar(RocketLeagueMap);
		LOG("ROCKET LEAGUE MAP: {}", "Beckwith Park Snowy - You may need to restart training to apply");
		}, "", PERMISSION_ALL);

	cvarManager->registerNotifier("algo_map_neo_tokyo_comic", [this](std::vector<std::string> args) {
		RocketLeagueMap = 68;
		SetKismetRocketLeagueMapVar(RocketLeagueMap);
		LOG("ROCKET LEAGUE MAP: {}", "Neo Tokyo Comic - You may need to restart training to apply");
		}, "", PERMISSION_ALL);

	cvarManager->registerNotifier("algo_map_dfh_stadium_circut", [this](std::vector<std::string> args) {
		RocketLeagueMap = 69;
		SetKismetRocketLeagueMapVar(RocketLeagueMap);
		LOG("ROCKET LEAGUE MAP: {}", "DFH Stadium Circut - You may need to restart training to apply");
		}, "", PERMISSION_ALL);

	cvarManager->registerNotifier("algo_map_champions_field_nike", [this](std::vector<std::string> args) {
		RocketLeagueMap = 70;
		SetKismetRocketLeagueMapVar(RocketLeagueMap);
		LOG("ROCKET LEAGUE MAP: {}", "Champions Field Nike - You may need to restart training to apply");
		}, "", PERMISSION_ALL);

	cvarManager->registerNotifier("algo_map_rivals_arena", [this](std::vector<std::string> args) {
		RocketLeagueMap = 71;
		SetKismetRocketLeagueMapVar(RocketLeagueMap);
		LOG("ROCKET LEAGUE MAP: {}", "Rivals Arena - You may need to restart training to apply");
		}, "", PERMISSION_ALL);
}
