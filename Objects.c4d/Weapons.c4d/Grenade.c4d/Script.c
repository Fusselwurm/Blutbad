#strict 2
#include _W__  //derived from "Generic Weapon"

local salvoCount;

//@override
public func Initialize() {
	inherited();

	energyNeeded = 100; // energy needed for one shot
	reloadRate = 5;
}

//@override
private func DoShoot(int direction) {

	if (salvoCount > 0) {
		salvoCount = 0;
		StopShooting();
		return(0);
	}
	salvoCount++;

	var projectile = CreateContents(_GR2);
	var x = Cos(shootingDirection, 15);
	var y = Sin(shootingDirection, 15);
	var xDir = Cos(shootingDirection, 8);
	var yDir = Sin(shootingDirection, 8);
	var rDir = 0;
	//bool Exit (object pObj, int iX, int iY, int iR, int iXDir, int iYDir, int iRDir);
	Exit(	projectile, x, y, 0, xDir, yDir, Random(180));

	projectile->Launch(xDir, yDir);
}