#strict 2
/*-- table --*/


public func Damage() {
  	if(GetDamage() > 1500) {
		Sound("Glassbreak");
		CastObjects(SPRK, 20, 20);
		CastObjects(SPR3, 20, 20);
		CastObjects(SHRD, 20, 20);
		CastObjects(SHRP, 20, 20);
		RemoveObject();
	}
}