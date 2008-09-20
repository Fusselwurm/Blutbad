#strict 2
#include _W__  //derived from "Generic Weapon"

local salvoCount;

//@override
public func Initialize() {
	inherited();

	energyNeeded = 33; // energy needed for one shot
	reloadRate = 5;
}

//@override
private func DoShoot() {

	if (ObjectCount (_SKB) > 70) {
		Message ("Too many spikeballs!");
		StopShooting();
		return(0);
	}

	if (salvoCount > 0) {
		salvoCount = 0;
		StopShooting();
		return(0);
	}
	salvoCount++;

	var projectile = CreateContents(_SKB);
	var x = Cos(shootingDirection, 15);
	var y = Sin(shootingDirection, 15);
	var xDir = Cos(shootingDirection, 7) + RandomX(-2, 2);
	var yDir = Sin(shootingDirection, 7) + RandomX(-2, 2);
	//bool Exit (object pObj, int iX, int iY, int iR, int iXDir, int iYDir, int iRDir);
	Exit(	projectile, x, y, Random(360), xDir, yDir, Random (135)); //TODO: dat soll gut sein, in *irgendeine* Richtung?

	projectile->Launch(xDir, yDir);

}