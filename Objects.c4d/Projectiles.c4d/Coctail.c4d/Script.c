#strict 2

protected func FlyProcess() {
	Smoke (0, 0, 7 + Random(5));
	if (Stuck() || (GetActTime() > 100))
		return(Hit());
}

protected func Hit() {
	Sound("Inflame");
	CastObjects(_FCS, 10, 50 + Random(20));
	RemoveObject();
}

protected func Launch() {
	SetAction("Fly");
}