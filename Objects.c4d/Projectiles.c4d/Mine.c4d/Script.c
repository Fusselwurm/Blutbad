Check:
  if (FindObject (0, -10, -20, 20, 30, OCF_CrewMember ()))
    Xplode ();
  if (GreaterThan (GetActTime (), 1000))
    Xplode ();
  return (1);

Launch:
  SetAction ("Check");  
  return (1);

Xplode:
  Explode (Sum (15, Random (10)));
  Explode (Sum (20, Random (10)), CreateObject (ROCK, Sum (-5, Random (10)), Sum (-5, Random (10))));
  return (1);