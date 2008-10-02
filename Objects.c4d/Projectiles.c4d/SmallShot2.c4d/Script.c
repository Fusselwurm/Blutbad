#strict 2

public func Hit () {
	Explode(6 + Random(4));
}

protected func Check () {
	if (GetActTime() > 500) {
		Hit();
	}
}
