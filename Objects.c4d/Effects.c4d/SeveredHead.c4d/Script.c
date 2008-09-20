/* Severed head */

#strict 2

public func Initialize() {
	SetAction ("Bleed");
}

public func Bleed() {
	CastPXS ("Blood", 1, Random(100));
	if (GetActTime() > 500)
		SetAction ("Idle");
}

public func Damage() {
	if (OnFire())
		return (1);
	if (GetDamage() > 500)
		return (Flame());
}

public func Flame() {
	SetAction("Idle");
	Incinerate();
}