Check:
  if (SetVar (1, FindObject (0, -10, -20, 20, 30, OCF_CrewMember ())))
    Sting (Var (1));
  if (GreaterThan (GetActTime (), 1200))
    RemoveObject ();
  return (1);

Launch:
  SetAction ("Check");  
  return (1);

Sting:
  Punch (Par (0), Sum (6, Random (3)));
  ObjectCall (Par (0), "Hurt");
  CastObjects (_EB1, Mul (12, Local (2, Local (1, Par (0)))), 50);
  RemoveObject ();
  return (1);