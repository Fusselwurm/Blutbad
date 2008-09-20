/*-- Cokisautomaatti --*/

Damage:
  if (OnFire ())
    return (1);
  if (GreaterThan (GetDamage (), 1200))
    return (Break ());
  return (1);

Break:
  Sound ("Glassbreak");
  Sound ("Blast2");
  Incinerate ();
  CastObjects (SPRK, 10, 20);
  CastObjects (SPR3, 10, 20);
  CastObjects (SHRD, 5, 20);
  CastObjects (SHRP, 5, 20);
  return (1);