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

	if (salvoCount > 16) {
		salvoCount = 0;
		StopShooting();
		return(0);
	}

	if (salvoCount == 0) {
		Sound ("Blast2");
	}

	salvoCount++;

	var projectile = CreateContents(_SPL);
	var x = Cos(shootingDirection, 15);
	var y = Sin(shootingDirection, 15);
	var xDir = Cos(shootingDirection, 15) + RandomX(-3, 3);
	var yDir = Sin(shootingDirection, 15) + RandomX(-3, 3);
	var rDir = 0;
	//bool Exit (object pObj, int iX, int iY, int iR, int iXDir, int iYDir, int iRDir);
	Exit(	projectile, x, y, 0, xDir, yDir, 0);

}