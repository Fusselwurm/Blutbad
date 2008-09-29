#strict 2
#include _W__  //derived from "Generic Weapon"

local salvoCount;

//@override
public func Initialize() {
	inherited();

	energyNeeded = 4; // energy needed for one shot
	reloadRate = 5;
}

//@override
private func DoShoot(int direction) {

	if (salvoCount > 20) {
		salvoCount = 0;
		StopShooting();
		return(0);
	}
	salvoCount++;

	var i = 0;
	for (i = 0; i < 3; i++) {
		var projectile = CreateContents(_FLM);
		var x = Cos(shootingDirection, 10);
		var y = Sin(shootingDirection, 10);
		var xDir = Cos(shootingDirection, 10) + RandomX(-2, 2);
		var yDir = Sin(shootingDirection, 10) + RandomX(-2, 2);
		//bool Exit (object pObj, int iX, int iY, int iR, int iXDir, int iYDir, int iRDir);
		Exit(projectile, x, y, shootingDirection, xDir, yDir, 0);
	}
}
