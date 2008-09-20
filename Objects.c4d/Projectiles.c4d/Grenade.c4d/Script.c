FlyProcess:
  if (Stuck ())
    return (Xplode ());
  if (GreaterThan (GetActTime (), Sum (30, Random (10))))
    Xplode ();
  return (1);

Xplode:
  Explode (Sum (20, Random (10)));
  CastObjects (_SP2, Sum (30, Random (10)), Sum (50, Random (20)));
  return (1);

Launch:
  SetAction ("Fly");
  return (1);