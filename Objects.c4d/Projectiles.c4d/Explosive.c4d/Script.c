#strict 2

protected func Time () {
	if (GetActTime() >(65 + Random(4))) {
		Xplode();
	}
}

public func Launch () {
	SetAction("Delay");
}

private func Xplode () {
	Explode(12 + Random(7));
}
