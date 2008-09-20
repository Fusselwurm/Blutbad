Crackle:
  if (GreaterThan (GetActTime (), 100))
    End ();
  CastObjects (_SP2, 1, Sum (30, Random (10)));
  return (1);

Launch:
  SetAction ("Crackle");
  return (1);

End:
  CastObjects (_SP2, 10, Sum (30, Random (10)));
  Explode ();
  return (1);

Hit:
  SetXDir (Sum (-50, Random (100)));
  SetYDir (Sum (-50, Random (100)));
  return (1);