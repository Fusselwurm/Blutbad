#strict 2

public func Check () {
	if (FindObject(0, -10, -20, 20, 30, OCF_CrewMember) || (GetActTime() > 1000)) {
		Xplode();
	}
}

public func Launch () {
	SetAction("Check");
}

private func Xplode () {
	Explode(25 + Random(10));
	Explode(30 + Random(10), CreateObject(ROCK, RandomX(-5, 5), RandomX(-5, 5)));
}
