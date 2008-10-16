#strict 2
#include _W__  //derived from "Generic Weapon"

local salvoCount;

//@override
public func Initialize() {
	inherited();

	energyNeeded = 10; // energy needed for one shot
	reloadRate = 7;
}

//@override
private func DoShoot(int direction) {

	if (salvoCount > 5) {
		salvoCount = 0;
		StopShooting();
		return(0);
	}
	salvoCount++;

	var projectile = CreateContents(_SPL);
	var x = Cos(shootingDirection, 15);
	var y = Sin(shootingDirection, 15);
	var xDir = Cos(shootingDirection, 15) + RandomX(-2, 2);
	var yDir = Sin(shootingDirection, 15) + RandomX(-2, 2);
	//bool Exit (object pObj, int iX, int iY, int iR, int iXDir, int iYDir, int iRDir);
	Exit(	projectile, x, y, shootingDirection, xDir, yDir, 0);
}