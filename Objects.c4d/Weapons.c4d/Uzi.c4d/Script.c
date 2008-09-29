#strict 2
#include _W__  //derived from "Generic Weapon"


local salvoCount;

//@override
private func DoShoot(int direction) {

	if (salvoCount > 100) {
		salvoCount = 0;
		StopShooting();
		return(0);
	}
	salvoCount++;

	var projectile = CreateContents(_SPL);
	var xDir = Cos(shootingDirection, 15);
	var yDir = Sin(shootingDirection, 15);
	//bool Exit (object pObj, int iX, int iY, int iR, int iXDir, int iYDir, int iRDir);
	Exit(
		projectile,
		Cos(shootingDirection, 15), Sin(shootingDirection, 15),
		shootingDirection,
		xDir, yDir,
		0);
}

//@override
public func Initialize() {
	inherited();

	energyNeeded = 33; // energy needed for one shot
	reloadRate = 5;
}
