#strict 2

local xDir;
local yDir;

protected func FlyProcess() {

	if (GetActTime() > 100)
		return(SetAction("Idle"));

	Smoke(0, 0, 10 + Random(10));
	SetXDir(xDir);
	SetYDir(yDir);
	if (FindObject(0, -5, -5, 10, 10, OCF_CrewMember) || Stuck())
		return(Hit());

	Exit(Contents(), 0, 1, 0, xDir/(18 + Random(5)), yDir/(18 + Random(5)));
	Exit(Contents(), 0, 1, 0, xDir/(18 + Random(5)) , yDir/(18 + Random(5)));
}

protected func Hit() {
	var lvl = Sqrt(ContentsCount(_CST, this) * 10);
	Explode(lvl, this);
}

public func Launch(x, y) {
	SetAction("Fly");
	xDir = x * 4;
	yDir = y * 4;
	CreateContents(_CST, this, 100);

	SetXDir(xDir);
	SetYDir(yDir);
}
