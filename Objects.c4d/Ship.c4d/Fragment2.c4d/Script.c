#strict 2

//TODO: same script as with the other fragment --> merge objects!

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