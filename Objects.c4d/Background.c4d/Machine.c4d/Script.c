/*-- Cokisautomaatti --*/

Damage:
  Sound ("Glassbreak");
  Sound ("Blast2");
  ChangeDef (_BMW, this ());
  CastObjects (SPRK, 10, 20);
  CastObjects (SPR3, 10, 20);
  CastObjects (SHRD, 5, 20);
  CastObjects (SHRP, 5, 20);
  return (1);