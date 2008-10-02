#strict 2

protected func Initialize () {
	SetAction("Check4Clonk");
}

protected func Hit() {
	Explode(5);
}

protected func Check() {
	if (FindObject(0, -5, -5, 10, 10, OCF_CrewMember)) {
		ChangeDef(_EB1);
		Explode(5, CreateObject(ROCK));
	} else if (GetActTime() > 150) {
		RemoveObject();
	}
}