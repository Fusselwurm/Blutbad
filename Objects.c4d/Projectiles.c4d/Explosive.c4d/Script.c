Time:
  if (GreaterThan (GetActTime (), Sum (15, Random (4))))
    Xplode ();
  return (1);

Launch:
  SetAction ("Delay");
  return (1);

Xplode:
  Explode (Sum (12, Random (7)));
  return (1);