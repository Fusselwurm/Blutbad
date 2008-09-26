/* Severed head */

#strict 2

local bloodStream;

public func Initialize() {
	SetAction ("Bleed");
	bloodStream = GetOptions(GetOwner())->getBloodLevel() ;
	bloodStream *= bloodStream;
}

public func Bleed() {
	CastPXS ("Blood", bloodStream, Random(100));
	if ((GetActTime() % 10) == 0) {
		bloodStream = ((bloodStream*100)/105) - 1;
	}
}

public func Damage() {
	if (OnFire())
		return(1);
	if (GetDamage() > 500)
		return(Flame());
}

public func Flame() {
	SetAction("Idle");
	Incinerate();
}