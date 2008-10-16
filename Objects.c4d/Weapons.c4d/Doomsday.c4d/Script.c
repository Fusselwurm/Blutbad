#strict 2
#include _W__  //derived from "Generic Weapon"

local salvoCount;

//@override
public func Initialize() {
	inherited();

	energyNeeded = 15; // energy needed for one shot
	reloadRate = 5;
}

//@override
private func DoShoot(int direction) {

	if (salvoCount > 7) {
		salvoCount = 0;
		StopShooting();
		return(0);
	}
	salvoCount++;

	var projectile = CreateContents(_DDR);
	var x = Cos(shootingDirection, 15);
	var y = Sin(shootingDirection, 15);
	var xDir = Cos(shootingDirection, 50) + RandomX(-10, 10);
	var yDir = Sin(shootingDirection, 50) + RandomX(-10, 10);
	var rDir = 0;
	//bool Exit (object pObj, int iX, int iY, int iR, int iXDir, int iYDir, int iRDir);
	Exit(	projectile, x, y, shootingDirection, xDir, yDir, rDir);

	projectile->Launch(xDir, yDir);
}
