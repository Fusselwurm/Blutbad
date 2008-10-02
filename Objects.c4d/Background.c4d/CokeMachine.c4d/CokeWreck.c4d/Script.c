#strict 2

protected func Initialize () {
	SetAction("Canning");
}

protected func Can () {
	Exit(CreateContents(_BCA), 0, 10, 0, RandomX(-1, 2), Random(2), Random(180));
	if (GetActTime() > 100) {
		return(SetAction("Idle"));
	}
}

public func Damage () {
	if (GetDamage() > 1000) {
		Vaporize();
	}
}

public func Vaporize () {
	CastObjects(SPRK, 20, 20);
	CastObjects(SPK3, 20, 20);
	CastObjects(SHRD, 20, 20);
	CastObjects(SHRP, 20, 20);
	Explode(20);
}
