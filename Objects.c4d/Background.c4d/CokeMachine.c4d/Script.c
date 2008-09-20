/*-- Cokisautomaatti --*/

protected func Damage()
{
	Sound ("Glassbreak");
	Sound ("Blast2");
	ChangeDef(_BCW, this ());
	CastObjects(SPRK, 10, 20);
	CastObjects(SPR3, 10, 20);
	CastObjects(SHRD, 5, 20);
	CastObjects(SHRP, 5, 20);
	this->Initialize();
	return(1);
}