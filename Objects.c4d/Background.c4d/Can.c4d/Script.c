#strict 2

 protected func Hit () {
	Sound("CanHit");
}

 protected func Damage () {
	if (GetDamage() > 500) {
		Wreck();
	}
}

 private func Wreck () {
	CastObjects(SHRD, 2, 10);
	RemoveObject();
}
