Initialize:
  SetAction ("Check4Clonk");
  return (1);

Hit:
  Explode (5);
  return (1);

Check:
  if (FindObject (0, -5, -5, 10, 10, OCF_CrewMember ()))
    return (And (ChangeDef (_EB1), Explode (5, CreateObject (ROCK))));
  if (GreaterThan (GetActTime (), 150))
    RemoveObject ();
  return (1);