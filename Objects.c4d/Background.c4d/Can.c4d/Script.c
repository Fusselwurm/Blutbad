Hit:
  Sound ("CanHit");
  return (1);

Damage:
  if (GreaterThan (GetDamage (), 500))
    Wreck ();
  return (1);

Wreck:
  CastObjects (SHRD, 2, 10);
  RemoveObject ();
  return (1);