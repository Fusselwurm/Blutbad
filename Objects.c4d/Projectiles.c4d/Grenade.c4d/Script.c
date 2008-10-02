#strict 2

public func FlyProcess () {
	if (Stuck() || (GetActTime() > (30 + Random(10)))) {
		Xplode();
	}
}

public func Xplode () {
	Explode(20 + Random(10));
	CastObjects(_SP2, 30 + Random(10), 50 + Random(20));
}

public func Launch () {
	SetAction("Fly");
}
