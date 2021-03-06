#strict 2
#include _W__  //derived from "Generic Weapon"

local salvoCount;

//@override
public func Initialize() {
	inherited();

	energyNeeded = 25; // energy needed for one shot
	reloadRate = 10;
}

//@override
private func DoShoot(int direction) {

	if (salvoCount > 0) {
		salvoCount = 0;
		StopShooting();
		return(0);
	}
	salvoCount++;

	var projectile = CreateContents(_SHT);
	var x = Cos(shootingDirection, 15);
	var y = Sin(shootingDirection, 15);
	var xDir = Cos(shootingDirection, 12);
	var yDir = Sin(shootingDirection, 12);
	var rDir = 0;
	//bool Exit (object pObj, int iX, int iY, int iR, int iXDir, int iYDir, int iRDir);
	Exit(	projectile, x, y, shootingDirection, xDir, yDir, Random (180));

	projectile->Launch(xDir, yDir);
}