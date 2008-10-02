#strict 2

local xDir;
local yDir;

public func FlyProcess () {
	if (GetActTime() > 75) {
		return(SetAction("Idle"));
	}

	if (!Random(4)) {
		CreateObject(_EF1);
	}

	SetXDir(xDir);
	SetYDir(yDir);
	if (FindObject(0, -5, -5, 10, 10, OCF_CrewMember) || Stuck()) {
		Hit();
	}
}

public func Hit () {
	Explode(12, CreateObject(ROCK, RandomX(-7, 7), RandomX(-7, 7)));
	Explode(17);
}

public func Launch (x, y) {
	SetAction("Fly");
	xDir = x * 2;
	yDir = y  *2;
}
