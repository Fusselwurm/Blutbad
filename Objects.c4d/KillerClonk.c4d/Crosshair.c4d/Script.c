/* The ultimate Crosshair */

local controllingObject;

public func Attach(pObject)
{
	controllingObject = pObject;
	SetAction("Jee", controllingObject); // ActMap.Jee calls ATTACH
	return (1);
}

public func RotateUpRight()
{
	SetRDir(-5);
}

public func RotateDownRight()
{
	SetRDir(5);
}

public func RotateUpLeft()
{
	SetRDir(5);
}

public func RotateDownLeft()
{
	SetRDir(-5);
}


public func StopRotating()
{
	SetRDir(0);
}

public func switchDirection(dir) {
	var r = GetR();

	if (((dir == COMD_Right) &&
	      ((r < -89) || (r > 44))) ||
	     ((dir == COMD_Left) &&
	      ((r > -91) && (r < 136)))) {
		r = -180 - r;
		if (r < -180) {
			r = r + 360;
		}

		SetR(r);
	}
}

protected func Check()
{
	if ((controllingObject != 0) && (controllingObject->getIsChangingDir() == true))
		return(0);

	var r = GetR();
	var dir = controllingObject->getDirSecure();

	if (dir == COMD_Right) {
		if (r < -89) {

			SetR(-89);
			StopRotating();
		}
		else if (r > 45) {

			SetR(44);
			StopRotating();
		}
	}
	else if (dir == COMD_Left){
		if ((r < 136) && (r > 0)) {

			SetR(136);
			StopRotating();
		}
		else if ((r > -91) && (r < 0)) {

			SetR(-91);
			StopRotating();
		}
	}
	return(1);
}

/*
CheckDir:
	if (GetComDir(controllingObject))
		CheckDirLeft();
	else
		CheckDirRight();
	return (1);

CheckDirRight:
  if (Inside (SetVar (0, GetR ()), 1, 89))
    SetR (Sum (180, Sub (Var (0), Mul (Var (0), 2))));
  if (Inside (Var (0), -89, -1))
    SetR (Sum (180, Sub (Var (0), Mul (Var (0), 2))));
  if (Equal (Var (0), 0))
    SetR (180);
  return (1);

CheckDirLeft:
  if (GreaterThan (SetVar (0, GetR ()), 130))
    SetR (Sum (0, Sub (180, Var (0))));
  if (LessThan (Var (0), -90))
    SetR (Sub (180, Var (0)));
  return (1);

CheckRotationDirRight: // 1 if in forbidden sector
	if (Not(Inside(GetR(), -89, 44)))
		return (1);
	return (0);

CheckRotationDirLeft:
  if (Not (Or (GreaterThan (GetR (), 135), LessThan (GetR (), -90))))
    return (1);
  return (0);*/

PntToPntUp:
  if (GetDir (Local ()))
    return (SetUpRight ());
  if (Not (GetDir (Local ())))
    return (SetUpLeft ());
  return (1);

PntToPntDown:
  if (GetDir (controllingObject))
    return (SetDownRight ());
  if (Not (GetDir (Local ())))
    return (SetDownLeft ());
  return (1);

SetUpRight:
  if (Equal (GetR(), 45))
    SetVar (1, 23);
  if (Equal (GetR(), 23))
    SetVar (1, 0);
  if (Equal (GetR(), 0))
    SetVar (1, 337);
  if (Equal (GetR(), -23))
    SetVar (1, 315);
  if (Equal (GetR(), -45))
    SetVar (1, 293);
  if (Equal (GetR(), -67))
    SetVar (1, 270);
  return (SetR(Var (1)));

SetUpLeft:
  SetVar (1, 180);
  if (Equal (GetR (), 135))
    SetVar (1, 158);
  if (Equal (GetR (), 158))
    SetVar (1, 180);
  if (Equal (GetR (), 180))
    SetVar (1, 202);
  if (Equal (GetR (), -158))
    SetVar (1, 225);
  if (Equal (GetR (), -135))
    SetVar (1, 247);
  if (Equal (GetR (), -113))
    SetVar (1, 270);
  return (SetR (Var (1)));

SetDownLeft:
  SetVar (1, 180);
  if (Equal (GetR (), 158))
    SetVar (1, 135);
  if (Equal (GetR (), 180))
    SetVar (1, 158);
  if (Equal (GetR (), -158))
    SetVar (1, 180);
  if (Equal (GetR (), -135))
    SetVar (1, 202);
  if (Equal (GetR (), -113))
    SetVar (1, 225);
  if (Equal (GetR (), -90))
    SetVar (1, 247);
  return (SetR (Var (1)));

SetDownRight:
  if (Equal (GetR (), -90))
    SetVar (1, 293);
  if (Equal (GetR (), -67))
    SetVar (1, 315);
  if (Equal (GetR (), -45))
    SetVar (1, 337);
  if (Equal (GetR (), -23))
    SetVar (1, 0);
  if (Equal (GetR (), 0))
    SetVar (1, 23);
  if (Equal (GetR (), 23))
    SetVar (1, 45);
  return (SetR (Var (1)));