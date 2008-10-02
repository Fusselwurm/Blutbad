#strict 2

protected func Initialize() {
	if (RandomX(0, 1) == 0) {
		SetAction("TimeI");
	} else {
		SetAction("TimeII");
	}
}

public func Disappear() {
	CastPXS("Blood", 20, 50);
	RemoveObject();
}