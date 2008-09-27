#strict 2

protected func Initialize() {
	SetAction("Smoke");
	Incinerate();
}

protected func Hit() {
	Sound("MetalHit*");
}

protected func Smoking() {
	Smoke (0, 0, 20 + Random(10));
}