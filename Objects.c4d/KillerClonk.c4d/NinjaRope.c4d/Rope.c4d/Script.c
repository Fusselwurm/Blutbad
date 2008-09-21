#strict 2
/* The rope attaches to the hook and the clonk.*/

public func Beam(object hook, object user) {
	SetAction("Connect", hook, user);
	var x = GetX();
	var y = GetY();
	SetVertex(0, 0, x);
	SetVertex(0, 1, y);
	SetVertex(1, 0, x);
	SetVertex(1, 1, y);
	ForcePosition(this, 0, 0);
}

protected func LineBreak() { //DANGER: if this occurs, the hook may not know that the rope is gone
	Sound("LineBreak");
	RemoveObject();
}