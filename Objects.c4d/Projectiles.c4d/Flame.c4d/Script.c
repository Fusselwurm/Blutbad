BurnProcess:
  DoCon (+3);
  if (SetVar (1, FindObject (0, -5, -5, 10, 10, OCF_CrewMember ())))
    And (RemoveObject (), And (DoEnergy (-5, Var (1)), CastObjects (DFLM, 2, 15)));
  if (Random(4))
    if (GreaterThan(GetActTime(),40)) return(AssignRemoval());
  if (Not(OnFire())) return(AssignRemoval());
  return(1);

Initialize:
  Incinerate();
  SetAction("Burn");
  return(1);

Hit:
  RemoveObject ();
  return (1);