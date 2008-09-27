#strict 2

protected func Check() {
	var clonk = FindObject(0, -10, -20, 20, 30, OCF_CrewMember);
	if (clonk) {
		Sting(clonk);
	}
	if (GetActTime() > 1200) {
		RemoveObject();
	}
}

public func Launch() {
	SetAction("Check");
}

private func Sting(object lifeform) {
	Punch(lifeform, 6 + Random(3));
	lifeform->Hurt();
	CastObjects(_EB1, GetOptions(lifeform->GetOwner())->getBloodLevel() * 12, 50);
	RemoveObject();
}