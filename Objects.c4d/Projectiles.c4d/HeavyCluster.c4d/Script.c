#strict 2

protected func Initialize() {
	SetAction ("Fly");
}

protected func Hit() {
	Explode(15);
	CastObjects(_SPL, 2, 30 + Random(20));
}

protected func Flying() {
	if (GetActTime() > 150) {
		RemoveObject();
	}
	Smoke(0, 0, 2 + Random(3));
	if (!Random(5)) {
		CastObjects(_SPL, 1, 20);
	}
}