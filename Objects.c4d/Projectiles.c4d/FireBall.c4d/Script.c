#strict 2

// this is the hellrider ^^

protected func FlyProcess() {
	Explode(13 + Random(7), CreateObject(ROCK));
	if (Stuck() || (GetActTime() > (50 + Random(10))))
		return(End());
	return(1);
}

protected func Hit() {
	SetXDir(RandomX(-50, 50));
	SetYDir(RandomX(-50, 50));
}

public func Launch() {
	SetAction ("Fly");
}

public func End() {
	Sound("Detonate");
	Explode(60 + Random(20));
	CastObjects(_FCL, 20, 50 + Random(20));
}