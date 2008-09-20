
Process:
  if (GreaterThan(GetActTime(),20)) return(AssignRemoval());
  return(1);

Completion:
  SetAction("Sparkle");
  return(1);
