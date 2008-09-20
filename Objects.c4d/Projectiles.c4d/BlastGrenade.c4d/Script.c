FlyProcess:
  Smoke (0, 0, Sum (7, Random (5)));
  if (Stuck ())
    return (Hit ());
  if (GreaterThan (GetActTime (), 150))
    Hit ();
  return (1);

Hit:
  Sound ("Detonate");
  Explode (Sum (40, Random (10)));
  CastObjects (_GCS, 5, Sum (50, Random (20)));
  return (1);

Launch:
  SetAction ("Fly");  
  return (1);