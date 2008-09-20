Initialize:
  SetAction ("Fly");
  return (1);

Hit:
  Explode (15);
  CastObjects (_SPL, 2, Sum (30, Random (20)));
  return (1);

Flying:
  if (GreaterThan (GetActTime (), 150))
    RemoveObject ();
  Smoke (0, 0, Sum (2, Random (3)));
  if (Not (Random (5)))
    CastObjects (_SPL, 1, 20);
  return (1);