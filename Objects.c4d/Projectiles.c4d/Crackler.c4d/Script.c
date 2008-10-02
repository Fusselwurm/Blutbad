#strict 2

public func Crackle () {
	if (GetActTime() > 100) {
		End();
	}
	CastObjects(_SP2, 1, 30 + Random(10));
}

public func Launch () {
	SetAction("Crackle");
}

private func End () {
	CastObjects(_SP2, 10, 30 + Random(10));
	Explode();
}

public func Hit () {
	SetXDir(RandomX(-50, 50));
	SetYDir(RandomX(-50, 50));
}
