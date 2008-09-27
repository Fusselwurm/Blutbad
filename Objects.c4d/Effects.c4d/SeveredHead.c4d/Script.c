/* Severed head */

#strict 2

local bloodStream;
local extreme;

public func Initialize() {
	bloodStream = GetOptions(GetOwner())->getBloodLevel() ;
	if (bloodStream > 10) {
		extreme = true;
	} else {
		extreme = false;
	}

	bloodStream *= bloodStream;
	SetAction ("Bleed");
}

public func Bleed() {
	CastPXS ("Blood", bloodStream, Random(100));
	if ((GetActTime() % 10) == 0) {
		if (!(extreme) || (bloodStream > 20)) {
			bloodStream -= 1;
		} else {
			// be nice... if ppl got enough blood, we stop bleeding
			if (GetOptions(GetOwner())->getBloodLevel() < 11) {
				bloodStream -= 1;
			}
		}
	}
	if (bloodStream <= 0) {
		SetAction("Idle");
	}
}

public func Damage() {
	if (OnFire()) {
		return(1);
	}
	if (GetDamage() > 500) {
		return(Flame());
	}
}

public func Flame() {
	SetAction("Idle");
	Incinerate();
}