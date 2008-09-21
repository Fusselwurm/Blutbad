#strict 2

/* Wrecked Crewcarrier */

/*
	the crew carrier serves as factory/controller/whatnot for the team it belongs to.
	yes, it is a team member.
	it creates clonks, knows their energy, gives 'em weapons...
	Options etc shall be stored in the _LOC object, but for now the wreck is okay, also
	TODO: dont let it be a team member. this stinks. it even gets a name -.-
	TODO: localization
	FIXME:
*/

local aimStyle; // 1... rotating, 2.. point-to-point
local _KC1_player; // the single living clonk of the team
local clonkEnergy; // "health"  -
local lives; // lives left
local bloodLevel;
local playerWeapons; //array of Weapon IDs

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
	bloodLevel = 1;
	lives = 20;
	clonkEnergy = 100000;
	playerWeapons = []; // we use the length of this array to check if the player already has all the weapons he needs
	SetAction("Delay");
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
	return(bloodLevel);
}

/**
 * teleports the player to a random spot where he's not stuck and not submerged in liquid
 */
private func Teleport()
{
	var x = Random(LandscapeWidth());
	var y = Random(LandscapeHeight());

	if (GBackLiquid(x - 10, y - 10) || GBackLiquid(x -10, y + 10) || GBackLiquid(x + 10, y - 10) || GBackLiquid(x +10, y + 10)) {
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
	AddMenuItem("$ResetWeapons$", "ResetWeap"); // we should not need this. TODO: test if there is a case when the player loses his weapons
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

// get player's options object
private func GetOptions() {
	var lock = FindObjects(Find_ID(_LOC), Find_Owner(GetOwner()));
	if (GetLength(lock) > 0) {
		return lock[0];
	}
	return false;
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
		fmtParam = "enabling";
	} else {
		fmtParam = "disabling";
	}
	Message("$voted_for$", this, fmtParam, lockType);
}

protected func HealthLock() {
	var options  = GetOptions();
	if (!options)  return(Log("$something_is_bad$ :("));

	var lock = !options->getHealthLock();
	LockVote("health", lock);
	options->setHealthLock(lock);
}

protected func LoadLock() {
	var options  = GetOptions();
	if (!options)  return(Log("$something_is_bad$ :("));

	var lock = !options->getLoadTimesLock();
	LockVote("load times", lock);
	options->setLoadTimesLock(lock);
}

protected func WeapLock() {
	var options  = GetOptions();
	if (!options)  return(Log("$something_is_bad$ :("));

	var lock = !options->getWeaponsLock();
	LockVote("weapons", lock);
	options->setWeaponsLock(lock);
}

protected func LivesLock() {
	var options  = GetOptions();
	if (!options)  return(Log("$something_is_bad$ :("));

	var lock = !options->getLivesLock();
	LockVote("lives", lock);
	options->setLivesLock(lock);
}

private func SetWeapons(id weaponID) {

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
	AddMenuItem("$NapalmThrower$", "SetWeapons", _WFS);
	AddMenuItem("$Spray$", "SetWeapons", _WSP);
	AddMenuItem("$DoomsdayRocket$", "SetWeapons", _WDD);
	AddMenuItem("$AntiTankMissile$", "SetWeapons", _WBZ);
	AddMenuItem("$Larpa$", "SetWeapons", _WLP);
	AddMenuItem("$Blaster$", "SetWeapons", _WBL);
	AddMenuItem("$Cannon$", "SetWeapons", _WCN);
	AddMenuItem("$Hellrider$", "SetWeapons", _WHR);
	AddMenuItem("$MolotovCoctail$", "SetWeapons", _WMC);
	AddMenuItem("$Shotgun$", "SetWeapons", _WSG);
	AddMenuItem("$SuperShotgun$", "SetWeapons", _WSS);
	AddMenuItem("$Mines$", "SetWeapons", _WMS);
	AddMenuItem("$Explosives$", "SetWeapons", _WEX);
	AddMenuItem("$Spikeballs$", "SetWeapons", _WSB);
	AddMenuItem("$Crackler$", "SetWeapons", _WCR);
	AddMenuItem("$Grenades$", "SetWeapons", _WKR);
	AddMenuItem("$DirtBall$", "SetWeapons", _WDB);
	AddMenuItem("$HandGun$", "SetWeapons", _WHG);
 	AddMenuItem("$Uzi$", "SetWeapons", _WUZ);
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
	bloodLevel++;
	if (bloodLevel > 10) {
		bloodLevel = 0;
	}
	Message("$Blood_Level$", this, bloodLevel);
}

protected func LivesLeft()
{
	if (CheckLivesLock())
		return(Message("$sry_lock_is_on$", this, "$health_options$"));

	CreateMenu();
	AddMenuItem("Instant Game Over", "InstGmOvr", _KC1, 0, 0, 1);
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
	AddMenuItem("Very Slow", "SetLoadTime", 0, 0, 0, 33);
	AddMenuItem("Slow", "SetLoadTime", 0, 0, 0, 66);
	AddMenuItem("Normal", "SetLoadTime", 0, 0, 0, 100);
	AddMenuItem("Fast", "SetLoadTime", 0, 0, 0, 150);
	AddMenuItem("Very Fast", "SetLoadTime", 0, 0, 0, 200);
	AddMenuItem("No Time At All!", "SetLoadTime", 0, 0, 0, 10000);
}

protected func SetLoadTime(oID, percent) {
	var msg;
	if (percent < 34)
		msg =  "Your loading time is very slow";
	else if (percent < 100)
		msg =  "Your loading time is slow";
	else if (percent == 100)
		msg =  "Your loading time is normal";
	else if (percent < 150)
		msg =  "Your loading time is fast";
	else if (percent < 500)
		msg =  "Your loading time is very fast";
	else
		msg =  "Your loading time is barely noticeable";
	PlrMessage(msg, GetOwner(), this);
	GetOptions()->setReloadMultiplier(percent);
}
