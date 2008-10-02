#strict 2

/*-- Cokisautomaatti --*/
protected func Damage () {
	if (OnFire())
		return(1);
	if (GetDamage() > 1200)
		return(Break());
}

protected func Break () {
	Sound("Glassbreak");
	Sound("Blast2");
	Incinerate();
	CastObjects(SPRK, 10, 20);
	CastObjects(SPR3, 10, 20);
	CastObjects(SHRD, 5, 20);
	CastObjects(SHRP, 5, 20);
}
