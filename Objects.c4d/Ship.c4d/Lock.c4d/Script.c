#strict 2

/*
This object does nothing but store constant values/options  for every player,
for example which options the player would like to be able to modify ("locks"),
the loadtime multiplier etc
*/

/*

Locals - deprecated
1 Health
2 Loading times
3 Weapons
4 Lives

*/

local lockHealth;
local lockLoadTimes;
local lockWeapons;
local lockLives;
local reloadMultiplier; //modifier for weapons' load time. percentage.
local bloodLevel;

// TODO this  should be static
private func asString(bool on) {
	if (on)
		return("on");
	return("off");
}

public func setReloadMultiplier(val) {
	reloadMultiplier = val;
}

public func getReloadMultiplier() {
	return reloadMultiplier;
}

protected func Initialize() {
	setHealthLock(true);
	setLoadTimesLock(true);
	setWeaponsLock(false); // default: that you can choose your weapons freely
	setLivesLock(true);
	bloodLevel = 2;
	reloadMultiplier = 100; // normal value.
}

public func getHealthLock() {
	return lockHealth;
}

public func getLoadTimesLock() {
	return lockLoadTimes;
}

public func getWeaponsLock() {
	return lockWeapons;
}

public func getLivesLock() {
	return lockLives;
}

// sets the lock. checks if the global options have changed
public func setHealthLock(bool val) {
	var iDiffer = false;
	if (lockHealth != val) {
		if (CheckHealthLock() != val) {
			iDiffer = true;
		}
		lockHealth = val;
		if (iDiffer && (CheckHealthLock() == val)) {
			Message("Health lock is now %s", 0, asString(val));
		}
	}
}

public func setLoadTimesLock(bool val) {
	var iDiffer = false;
	if (lockLoadTimes != val) {
		if (CheckLoadTimesLock() != val) {
			iDiffer = true;
		}
		lockLoadTimes = val;
		if (iDiffer && (CheckLoadTimesLock() == val)) {
			Message("Load times lock is now %s", 0, asString(val));
		}
	}
}

public func setWeaponsLock(bool val) {
	var iDiffer = false;
	if (lockWeapons != val) {
		if (CheckWeaponsLock() != val) {
			iDiffer = true;
		}

		lockWeapons = val;
		if (iDiffer && (CheckWeaponsLock() == val)) {
			Message("Weapons lock is now %s", 0, asString(val));
		}
	}
}

public func setLivesLock(bool val) {
	var iDiffer = false;
	if (lockLives != val) {
		if (CheckLivesLock() != val) {
			iDiffer = true;
		}

		lockLives = val;
		if (iDiffer && (CheckLivesLock() == val)) {
			Message("Lives lock is now %s", 0, asString(val));
		}
	}
}

public func setBloodLevel(int val) {
	bloodLevel = val;
}

public func getBloodLevel() {
	return bloodLevel;
}