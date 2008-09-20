/*-- Funke --*/

protected Initialize:
  SetAction("Sparkle");
  Sound("Electrify");
  return(1);

private Process:
  if (GreaterThan(GetActTime(),10)) return(RemoveObject());
  return(1);

