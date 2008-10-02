#strict 2

/* The helper flame object */

/*

This object attaches to the clonk and burns him

*/

local victim;

protected func Initialize () {
	Incinerate();
}

 public func Start (object clonk) {
	Sound("Scream");
	victim = clonk;
	SetAction("Palaminen", victim); //FIXME
}

 protected func Burning () {
	if (GetActTime() > (60 + Random(10)))
		return(End());
	DoEnergy(-1, victim);
	Sound("Hurt*");
}

protected func TimerCall () {
	if (!GetActionTarget()) {
		RemoveObject();
	}
	if (!OnFire()) {
		End();
	}
}

protected func End () {
	RemoveObject();
}
