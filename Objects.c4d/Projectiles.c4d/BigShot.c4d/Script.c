FlyProcess:
  Smoke (0, 0, Sum (5, Random (4)));
  if (Stuck ())
    return (Hit ());
  if (FindObject (0, -5, -5, 10, 10, OCF_CrewMember ()))
    return (Hit ());
  if (GreaterThan (GetActTime (), 150))
    Hit ();
  return (1);

Hit:
  Explode (Sum (15, Random (10)));
  CastObjects (_SPL, Sum (6, Random (4)), Sum (50, Random (20)));
  return (1);

Launch:
  SetAction ("Fly");  
  return (1);