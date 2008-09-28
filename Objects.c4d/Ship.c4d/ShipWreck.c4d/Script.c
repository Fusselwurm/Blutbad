#strict 2

/* Wrecked Crewcarrier */

/*
	the crew carrier serves as factory/controller/whatnot for the team it belongs to.
	yes, it is a team member.
	it creates clonks, knows their energy, gives 'em weapons...
	Options etc shall be stored in the _LOC object, but for now the wreck is okay, also
	TODO: dont let it be a team member. this stinks. it even gets a name -.-
	TODO: localization
*/

local aimStyle; // 1... rotating, 2.. point-to-point
local _KC1_player; // the single living clonk of the team
local clonkEnergy; // "health"  -
local lives; // lives left
local playerWeapons; //array of Weapon IDs
local weaponMenuArray;

//-------------------------------

/**
 * changes energy, and changes current health keep the percentage of full health equal
 */
global func ChangePhysicalEnergy(object clonk, int newPhysicalEnergy) {
	var prevPhysicalEnergy = GetPhysical("Energy", 0, clonk);
	var prevHealth = GetEnergy(clonk);
	SetPhysical("Energy", newPhysicalEnergy, PHYS_Temporary, clonk);
	DoEnergy(((newPhysicalEnergy * prevHealth) / prevPhysicalEnergy) - prevHealth, clonk);
}

//----------------------------------

protected func Initialize()
{
	aimStyle = 1;
	lives = 20;
	clonkEnergy = 100000;
	playerWeapons = []; // we use the length of this array to check if the player already has all the weapons he needs
	SetAction("Delay");
	weaponMenuArray = [
		[_WFS, "$NapalmThrower$", "Feuerregen..."],
		[_WSP, "$Spray$", "Sprühzeugs..."],
		[_WDD, "$DoomsdayRocket$", "Projektilsturm..."],
		[_WBZ, "$AntiTankMissile$", "bumm..."],
		[_WLP, "$Larpa$", "verstreut gefährliche Smarties..."],
		[_WBL, "$Blaster$", "Blastet... äh..."],
		[_WCN, "$Cannon$", "Kanone..."],
		[_WHR, "$Hellrider$", "Apokalyptischer Reiter..."],
		[_WMC, "$MolotovCoctail$", "Ein Molli, wie man ihn liebt...."],
		[_WSG, "$Shotgun$", "ewiglange Info zur Waffe..."],
		[_WSS, "$SuperShotgun$", "Sprühzeugs..."],
		[_WMS, "$Mines$", "Der automatische Camper..."],
		[_WEX, "$Explosives$", "Sprühzeugs..."],
		[_WSB, "$Spikeballs$", "Sprühzeugs..."],
		[_WCR, "$Crackler$", "Sprühzeugs..."],
		[_WKR, "$Grenades$", "Sprühzeugs..."],
		[_WDB, "$Spray$", "$DirtBall$..."],
		[_WHG, "$HandGun$", "Sprühzeugs..."],
		[_WUZ, "$Uzi$", "Für das Al-Clapone-Feeling..."]
	];

	return(1);
}

protected func CheckLives()
{
	Message("$lives_left_for_player$", 0, GetPlayerName(GetOwner()), lives);
	if (lives < 1)
		return(TheEnd());
	else
		Options();
	return(1);
}

protected func Hit()
{
// 	Explode(Sum(15, Random(30)), CreateObject(ROCK, Sum(-50, Random(100)), Sum(-50, Random(100))));
// 	Explode(Sum(15, Random(30)), CreateObject(ROCK, Sum(-50, Random(100)), Sum(-50, Random(100))));
	for (var i = 0; i < 4; i++) {
		Smoke(RandomX(-50, 50), RandomX(-50, 50), 10 + Random(20));
	}
	return(1);
}

protected func DeployPlayer()
{
	// if the 5th weapon is not set... let the player choose all his playerWeapons again :P
	if (GetLength(playerWeapons) < 5) {
		return(WeaponsMenu());
	}
	SetAction("Idle");
	// create and deploy crew member
	_KC1_player = CreateContents(_KC1);
	_KC1_player->setWreck(this);

	MakeCrewMember(_KC1_player, GetOwner());
	Exit(_KC1_player, 0, 0, 0, RandomX(-3, 3), 100 + Random(50));
	SetCursor(GetOwner(), _KC1_player);
	if (aimStyle == 2) // TODO: why are we doing this?
	{
		// turn player
		SetR(0, _KC1_player);
	}
	lives--;

	_KC1_player->setAimStyle(aimStyle);
	Teleport();
	ChangePhysicalEnergy(_KC1_player, clonkEnergy);
	var weapon;
	// give him his weapons
	for(var i = 0; i < GetLength(playerWeapons); i++) {
		weapon = CreateContents(playerWeapons[i], _KC1_player);
	}
	_KC1_player->Init2();
	return(1);
}

public func getBloodLevel()
{
	return(GetOptions(GetOwner())->getBloodLevel()); //TODO: replace references withrefs to opti^ons obj
}

/**
 * teleports the player to a random spot where he's not stuck and not submerged in liquid
 */
private func Teleport()
{
	var x = Random(LandscapeWidth());
	var y = Random(LandscapeHeight());
	var xOff = x - GetX();
	var yOff = y - GetY();

	if (GBackLiquid(xOff - 10, yOff - 10) || GBackLiquid(xOff -10, yOff + 10) || GBackLiquid(xOff + 10, yOff - 10) || GBackLiquid(xOff +10, yOff + 10)) {
		Log("blub, schnell weg!");
		return(Teleport());
	}

	DigFree(x, y, 12);
	SetPosition(x, y, _KC1_player);
	if (Stuck(_KC1_player)) {
		return(Teleport());
	}
}

protected func ControlSpecial()
{
	Options();
	return(1);
}

/**
 * Options Menu (Main Menu)
 */
private func Options()
{
	CreateMenu();
	AddMenuItem("$Locks$", "LockMenu");
	AddMenuItem("$AimingStyle$", "AimStyle");
	AddMenuItem("$BloodLevel$", "BloodLevel");
	AddMenuItem("$Lives$", "LivesLeft");
	AddMenuItem("$Health$", "Health");
	AddMenuItem("$LoadingTimes$", "LoadTime");
	AddMenuItem("$ChooseWeapons$", "WeaponsMenu");
	if (_KC1_player == 0)
		AddMenuItem("$DeployPlayer$", "DeployPlayer", _KC1);
	AddMenuItem("$ResetWeapons$", "ResetWeap"); // we should not need this. TODO: player can lose his active weapon sometimes, when jumping or scaling and you press down twice. or so.
}

// remove player's weapons, and re-create them. this is not to alter the player's weapon options
private func ResetWeap()
{
	if (!_KC1_player)
		return;
	if (ObjectCount2(Find_Container(_KC1_player)) == 5)
		return(Message("$have_all_weapons$"));

	// remove weapons, and re-create them
	var contents = FindObjects(Find_Container(_KC1_player));
	for(var i = 0; i < GetLength(contents); i++) {
		RemoveObject(contents[i]);
	}
	for(var i = 0; i < GetLength(playerWeapons); i++) {
		CreateContents(playerWeapons[i], _KC1_player);
	}

	RemoveLooseWeap();
}


private func RemoveLooseWeap()
{
	var weap = FindObjects(Find_Owner(GetOwner()), Find_NoContainer(), Find_Category(C4D_Object));
	// alle frei rumliegenden Objekte (außer Waffen haben wir da nix) entfernen, die dem Spieler gehören
	for(var i = 0; i < GetLength(weap); i++) {
		RemoveObject(weap[i]);
	}
}

protected func LockMenu()
{
	CreateMenu();
	AddMenuItem(Format("$Lock$", "$live_energy_options$"), "HealthLock");
	AddMenuItem(Format("$Lock$", "$reload_options$"), "LoadLock");
	AddMenuItem(Format("$Lock$", "$weapon_selection$"), "WeapLock");
	AddMenuItem(Format("$Lock$", "$health_options$"), "LivesLock");
}

/**
 * prints a message
 */
private func LockVote(string lockType, bool enable) {
	var fmtParam;
	if (enable) {
		fmtParam = "$enable$";
	} else {
		fmtParam = "$disable$";
	}
	Message("$voted_for$", this, fmtParam, lockType);
}

protected func HealthLock() {
	var options  = GetOptions(GetOwner());
	if (!options)  return(Log("$something_is_bad$ :("));

	var lock = !options->getHealthLock();
	LockVote("$live_energy_options$", lock);
	options->setHealthLock(lock);
}

protected func LoadLock() {
	var options  = GetOptions(GetOwner());
	if (!options)  return(Log("$something_is_bad$ :("));

	var lock = !options->getLoadTimesLock();
	LockVote("$reload_options$", lock);
	options->setLoadTimesLock(lock);
}

protected func WeapLock() {
	var options  = GetOptions(GetOwner());
	if (!options)  return(Log("$something_is_bad$ :("));

	var lock = !options->getWeaponsLock();
	LockVote("$weapon_selection$", lock);
	options->setWeaponsLock(lock);
}

protected func LivesLock() {
	var options  = GetOptions(GetOwner());
	if (!options)  return(Log("$something_is_bad$ :("));

	var lock = !options->getLivesLock();
	LockVote("$health_options$", lock);
	options->setLivesLock(lock);
}

/**
 * first parameter is _H_M, second the id we want :)
 */
private func SetWeapons(blah, id weaponID) {

	var number = GetLength(playerWeapons);

	if (weaponID != 0) {
		playerWeapons[number] = weaponID;
		number++;
	}

	if (number >= 5) {
		Options();
		return;
	}

	Message("$choose_weapon$", this, number + 1);
	CreateMenu();

	for (var i = 0; i < GetLength(weaponMenuArray); i++) {
		AddMenuItem(weaponMenuArray[i][1], "SetWeapons", _H_M, 0, 0, weaponMenuArray[i][0], weaponMenuArray[i][2], 2, i);
	}
}

protected func WeaponsMenu()
{
	if (CheckWeaponsLock())
	{
		return(Message("$sry_lock_is_on$", this, "$weapon_selection$"));
	}
	playerWeapons = [];
	SetWeapons(0);
}

protected func AimStyle()
{
	if (aimStyle == 1) {
		setAimStyle(2);
	} else {
		setAimStyle(1);
	}

	Message("$Aim_Style$", this, aimStyle);
}

private func setAimStyle(style)
{
	aimStyle = style;
	if (_KC1_player) { // maybe we're calling this from the menu without a live clonk out there...
		_KC1_player->setAimStyle(aimStyle);
	}
}

protected func BloodLevel()
{
	var bloodLevel = GetOptions(GetOwner())->getBloodLevel();
	bloodLevel++;
	if (bloodLevel > 11) {
		bloodLevel = 0;
	}
	if (bloodLevel == 11) {
		bloodLevel = 20;
	}
	GetOptions(GetOwner())->setBloodLevel(bloodLevel);
	if (bloodLevel < 11) {
		Message("$Blood_Level$", this, bloodLevel);
	} else {
		Message("$Blood_Level_Extreme$", this, bloodLevel);
	}
}

protected func LivesLeft()
{
	if (CheckLivesLock())
		return(Message("$sry_lock_is_on$", this, "$health_options$"));

	CreateMenu();
	AddMenuItem("$Instant_Game_Over$", "InstGmOvr", _KC1, 0, 0, 1);
	AddMenuItem("5", "SetLives", _KC1, 0, 0, 5);
	AddMenuItem("10", "SetLives", _KC1, 0, 0, 10);
	AddMenuItem("20", "SetLives", _KC1, 0, 0, 20);
	AddMenuItem("30", "SetLives", _KC1, 0, 0, 30);
	AddMenuItem("40", "SetLives", _KC1, 0, 0, 40);
	AddMenuItem("50", "SetLives", _KC1, 0, 0, 50);
	AddMenuItem("60", "SetLives", _KC1, 0, 0, 60);
	AddMenuItem("70", "SetLives", _KC1, 0, 0, 70);
	AddMenuItem("80", "SetLives", _KC1, 0, 0, 80);
	AddMenuItem("90", "SetLives", _KC1, 0, 0, 90);
	AddMenuItem("100", "SetLives", _KC1, 0, 0, 100);
}

protected func SetLives(oID, livesLeft)
{
	lives = livesLeft;
	Message("$livesleft$", this, lives);
}

protected func InstGmOvr(oID, livesLeft)
{
	Message("$only_one_life$", this);
	lives = livesLeft;
}

protected func TheEnd()
{
	Kill();
// 	for(var i = 0; i < 9; i++)
// 	{
// 		Explode(Sum(30, Random(20)), CreateObject(ROCK, Sum(-50, Random(100)), Sum(-50, Random(100))));
// 	}
	Explode(80 + Random(20));
}

protected func Health()
{
	if (CheckHealthLock())
		return(Message("$sry_lock_is_on$", this, "$live_energy_options$"));

	CreateMenu();
	AddMenuItem("$Invincible$", "SetHealth", _KC1, 0, 0, 2000000);
	AddMenuItem("$Very_tough$", "SetHealth", _KC1, 0, 0, 1200000);
	AddMenuItem("$Tough$", "SetHealth", _KC1, 0, 0, 700000);
	AddMenuItem("$Hard$", "SetHealth", _KC1, 0, 0, 250000);
	AddMenuItem("$Normal$", "SetHealth", _KC1, 0, 0, 100000);
	AddMenuItem("$No_good$", "SetHealth", _KC1, 0, 0, 50000);
	AddMenuItem("$Very_bad$", "SetHealth", _KC1, 0, 0, 35000);
	AddMenuItem("$One_shot_one_kill$", "SetHealth", _KC1, 0, 0, 10000);
}

protected func SetHealth(oID, health) {
	var msg;
	if (health < 20000)
		msg = "$Will_die$";
	else if (health < 40000)
		msg = "$Very_vulnerable$";
	else if (health < 60000)
		msg = "$Not_tough$";
	else if (health < 120000)
		msg = "$Normal2$";
	else if (health < 360000)
		msg = "$Hard2$";
	else if (health < 720000)
		msg = "$Tough2$";
	else if (health < 1440000)
		msg = "$Very_tough2$";
	else
		msg = "$Invincible2$";

	clonkEnergy = health;
	ChangePhysicalEnergy(_KC1_player, clonkEnergy);
	PlrMessage(msg, GetOwner(), this);
}

protected func LoadTime() {
	if (CheckLoadTimesLock())
		return(Message("$sry_lock_is_on$", this, "$reload_options$"));
	CreateMenu();
	AddMenuItem("$Very_slow$", "SetLoadTime", 0, 0, 0, 33);
	AddMenuItem("$Slow$", "SetLoadTime", 0, 0, 0, 66);
	AddMenuItem("$Normal3$", "SetLoadTime", 0, 0, 0, 100);
	AddMenuItem("$Fast$", "SetLoadTime", 0, 0, 0, 150);
	AddMenuItem("$Very_fast$", "SetLoadTime", 0, 0, 0, 200);
	AddMenuItem("$No_Time_At_All$", "SetLoadTime", 0, 0, 0, 10000);
}

//natürlich sehr unschön gelöst, ich gebs zu - funktioniert aber ;)

protected func SetLoadTime(oID, percent) {
	var msg;
	if (percent < 34)
		msg =  "$Very_slow$";
	else if (percent < 100)
		msg =  "$Slow$";
	else if (percent == 100)
		msg =  "$Normal3$";
	else if (percent < 150)
		msg =  "$Fast$";
	else if (percent < 500)
		msg =  "$Very_fast$";
	else
		msg =  "$Barely_noticeable$";
	PlrMessage(msg, GetOwner(), this);
	GetOptions(GetOwner())->setReloadMultiplier(percent);
}
