#strict 2

//TODO: create an action "Shooting" for automatic weapons... then our StopShoot function becomes sensible ^^
//WISH: we could remember the user's former magic energy and give it back to him once he disarms.

local user; // this may be, for example, a belligerent Clonk. Or anything else that can hold weapons >D
local magicEnergyFactor;
local energyNow;
local energyNeeded; // = 100; // energy needed for one shot
local reloadRate; // = 5;
local isLoading; // reload may be allowed after the magazine has been emptied. also, during reload, shooting is forbidden
local maxEnergy; // = 100; // maximum energy
local reloadMultiplier; // the weapon retrieves this value from the player's option object. it is a percentage with which to adjust the reloadRate
local shootingDirection; // unfortunately, due to the call of DoShoot by the engine (action Shooting), we can't set the direction parameter directly :/

//private

// this should be overridden to:
//	* do the actual shooting
//	* stop the shooting if deemed appropriate ^^
private func DoShoot() {
	// just an example what to do... here we fire only this one shot. to fire multiple shots, don't call StopShoot ^^
	Message("bang! you're dead!", this);
	StopShooting();
}

protected func UseEnergy(int amount) {
	if (amount == 0) {
		amount = energyNeeded;
	}
	if (energyNeeded <= energyNow) {
		energyNow -= amount;
		DoMagicEnergy((-amount * magicEnergyFactor), user, true);
		return(true);
	}
	else {
		return(false);
	}
}

// protected

// engine (action) called
protected func Load() {
	energyNow +=reloadRate * reloadMultiplier/100;
	if (user) {
		DoMagicEnergy(reloadRate * reloadMultiplier/100 * magicEnergyFactor, user, true);
	}

	if (energyNow >= maxEnergy) {
		energyNow = maxEnergy;
		SetAction("Idle");
		isLoading = false;
	}
}

// public

// the user takes the weapon in his hand
public func Arm(object newUser) {
	user = newUser;
	// when the Clonk (or whoever uses it takes the weapon, we have to represent its energy via the magic energy... let's do this:
	// first retrieve the maximal magic energy the user has, so we know what would amount to "fully loaded"
	//var maxUserEnergy = GetPhysical("Magic", 0, user); //TODO: warum gibt GetPhysical("Magic" ..) etwas anderes zurück als GetMagicEnergy, wenns auf max is? hää? // weil energy/magicenergy immer in prozenten angegeben wird -.-

	// load reloadrate multiplier
	var options = FindObjects(Find_Owner(GetOwner(newUser)), Find_ID(_LOC));
	if (GetLength(options) > 0) {
		reloadMultiplier = options[0]->getReloadMultiplier();
	}

	magicEnergyFactor = 100 / maxEnergy;
	if (GetMagicEnergy(user) > 0) {
		DoMagicEnergy(-100, user, true); // first, we reset the user's energy to 0
	}
	DoMagicEnergy(energyNow * magicEnergyFactor, user, true); // then, we set it according to our weapon's current energy

	if (energyNow < maxEnergy) {
		SetAction("Loading");
	}
	Message(GetName(), user);
}

// the user stows the weapon away, drops it or whatever
public func DisArm() {
	DoMagicEnergy(-GetPhysical("Magic", 1, user), user, true); // first, we reset the former user's magic energy to zero, so he knows he's got no power anymore^^
	SetAction("Idle"); // we don't load automagically, right?
	user = 0; // and last, we know we're not in use anymore
}

// usually engine called
public func Initialize() {
	reloadMultiplier = 100;
	// defaults...
	energyNeeded = 100; // energy needed for one shot
	reloadRate = 5;
	maxEnergy = 100; // maximum energy
	isLoading = false;
	energyNow = maxEnergy; // when created, the weapon is fully loaded.
}

// shoot weapon.
public func Shoot(int direction) {
	shootingDirection = direction;

	if (GetAction() == "Shooting")  {
		return(0);
	}

	if ((user) && (energyNow >= energyNeeded) && (!isLoading)) {
		if (UseEnergy()) {
			isLoading = false;
			SetAction("Shooting");
		}
		return(1);
	}
	return(0);
}

// end the destruction!
public func StopShooting() {
	if ((energyNow < energyNeeded) && (user)) {
		isLoading = true;
		SetAction("Loading");
	}
	else {
		SetAction("Idle");
	}
}