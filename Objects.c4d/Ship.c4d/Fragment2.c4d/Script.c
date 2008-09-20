Initialize:
  SetAction ("Smoke");
  Incinerate ();
  return (1);

Hit:
  Sound("MetalHit*");
  return(1);

Smoking:
  Smoke (0, 0, Sum (20, Random (10)));
  return (1);