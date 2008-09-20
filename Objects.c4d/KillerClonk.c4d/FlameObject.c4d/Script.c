/* The helper flame object */

/*

This object attaches to the clonk and burns him

*/

Initialize:
  Incinerate ();
  return (1);

Start:
  Sound ("Scream");
  SetLocal (1, Par (0));
  SetAction ("Palaminen", Local (1));
  return (1);

Burning:
  if (GreaterThan (GetActTime (), Sum (60, Random (10))))
    return (End ());
  DoEnergy (-1, Local (1));
  Sound ("Hurt*");
  return (1);

TimerCall:
  if (Not (GetActionTarget ()))
    RemoveObject ();
  if (Not (OnFire ()))
    return (End ());
  return (1);

End:
  RemoveObject ();
  return (1);