#strict 2

protected func FlyProcess() {
	Smoke(0, 0, 7 + Random(5));
	if (Stuck() || (GetActTime() > 150))
		return(Hit());
}

protected func Hit() {
	Sound("Detonate");
	Explode(40 + Random(10));
	CastObjects(_GCS, 5, 50 + Random(20));
}

public func Launch() {
	SetAction("Fly");
}