#strict 2

local shootingDirection;

protected func FlyProcess() {

	var actTime = GetActTime();

	if (actTime > 150) {
    		return(Hit());
    	}

	if (actTime < 40) { // acceleration phase. not beautiful, but okay
		Smoke(0, 0, 10 + Random(10));
		var xDir = Sin(5 + actTime*2, 50)*Cos(shootingDirection, 100)/5;
		var yDir = Sin(5 + actTime*2, 50)*Sin(shootingDirection, 100)/5;
		SetXDir(xDir);
		SetYDir(yDir);
	}

	if (FindObject (0, -5, -5, 10, 10, OCF_CrewMember)) {
		return(Hit());
	}

	if (Stuck()) {
		return(Hit());
	}
}

protected func Hit() {
	Sound("Detonate");
	Explode(30 + Random (15), CreateObject(ROCK, RandomX(-10, 10), RandomX(-10, 10)));
	Explode(30 + Random (15), CreateObject(ROCK, RandomX(-10, 10), RandomX(-10, 10)));
	Explode(80);
}

public func Launch(int dir) {
	shootingDirection = dir;
	SetAction ("Fly");
}