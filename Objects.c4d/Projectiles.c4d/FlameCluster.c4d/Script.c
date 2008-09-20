#strict 2

public func Initialize() {
	SetAction("Fly");
}

public func Hit() {
	RemoveObject();
	CastObjects(DFLM, 2, 10);
}

public func Flying() {
	if (GetActTime() > 150)
		Hit();
	CastObjects(DFLM, 1, 15 + Random(15));
}