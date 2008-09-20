FlyProcess:
  if (GreaterThan (GetActTime (), 75))
    return (SetAction ("Idle"));
  if (Not (Random (4)))
    CreateObject (_EF1);
  SetXDir (Local (1));
  SetYDir (Local (2));
  if (FindObject (0, -5, -5, 10, 10, OCF_CrewMember ()))
    return (Hit ());
  if (Stuck ())
    return (Hit ());
  return (1);

Hit:
  Explode (12, CreateObject (ROCK, Sum (-7, Random (14)), Sum (-7, Random (14))));
  Explode (17);
  return (1);

Launch:
  SetAction ("Fly");  
  SetLocal (1, Mul (2, Par (0)));
  SetLocal (2, Mul (2, Par (1)));
  return (1);