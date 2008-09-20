#strict 2

public func Initialize() {
	SetAction("Check4Clonk");
}

protected func Hit() {
	Explode(10);
}

protected func Check() {
	if (FindObject(0, -5, -5, 10, 10, OCF_CrewMember))
		return(ChangeDef(_EB1) && Explode(5, CreateObject(ROCK))); //TODO: it shouldn 'become' blood... the _clonk_ is supposed to bleed, not the projectile
	if (GetActTime() > 200)
		return(Hit());
}