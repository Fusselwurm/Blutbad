Hit:
  Explode (Sum (6, Random (4)));
  return (1);

Check:
  if (GreaterThan (GetActTime (), 500))
    Hit ();
  return (1);