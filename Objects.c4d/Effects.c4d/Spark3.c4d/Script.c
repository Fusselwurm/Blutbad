#strict 2

protected func Initialize () {
	SetAction("Sparkle");
	Sound("Electrify");
}

private func Process () {
	if (GetActTime() > 10) {
		RemoveObject();
	}
}
