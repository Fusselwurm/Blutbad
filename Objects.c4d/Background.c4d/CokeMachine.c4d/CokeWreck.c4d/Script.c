/*-- Rikkinäinen cokislaite --*/

protected Initialize:
  SetAction ("Canning");
  return (1);

protected Can:
  Exit (CreateContents (_BCA), 0, 10, 0, Sum (-1, Random (3)), Random (2), Random (180));
  if (GreaterThan (GetActTime (), 100))
    return (SetAction ("Idle"));
  return (1);

Damage:
  if (GreaterThan (GetDamage (), 1000))
    return (Vaporize ());
  return (1);

Vaporize:
  CastObjects (SPRK, 20, 20);
  CastObjects (SPK3, 20, 20);
  CastObjects (SHRD, 20, 20);
  CastObjects (SHRP, 20, 20);
  Explode (20);
  return (1);