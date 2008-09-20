#strict 2
/* The ultimate Crosshair */

local controllingObject;
local rotationSpeed;

// vars for pre-set point-to-point directions, arrays of int
local directionsRight;
local directionsLeft;


public func Initialize() {
	rotationSpeed = 5;
	directionsRight = [44, 23, 0, -23, -45, -67, -89];
	directionsLeft = [136, 158, 180, -158, -135, -113, -91];
}

public func Attach(pObject)
{
	controllingObject = pObject;
	SetAction("Jee", controllingObject); // ActMap.Jee calls ATTACH
	return (1);
}

public func RotateUpRight()
{
	SetRDir(-rotationSpeed);
}

public func RotateDownRight()
{
	SetRDir(rotationSpeed);
}

public func RotateUpLeft()
{
	SetRDir(rotationSpeed);
}

public func RotateDownLeft()
{
	SetRDir(-rotationSpeed);
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

public func PntToPntUp() {
	var dir = controllingObject->getDirSecure();
	if (dir == COMD_Right) {
		return(SetUpRight());
	}
	else if (dir == COMD_Left) {
		return(SetUpLeft());
	}
}

public func PntToPntDown() {

	var dir = controllingObject->getDirSecure();
	if (dir == COMD_Right) {
		return(SetDownRight());
	}
	else if (dir == COMD_Left) {
		return(SetDownLeft());
	}
}

private func SetUpRight() {
	var r = GetR();
	var i = IndexOfArray(directionsRight, r);
	if (i >= (GetLength(directionsRight) - 1))
		return;

	if (i == -1) {
		r = directionsRight[0];
	} else {
		r = directionsRight[i + 1];
	}
	SetR(r);
}

private func SetDownRight() {
	var r = GetR();
	var i = IndexOfArray(directionsRight, r);
	if (i == 0)
		return;

	if (i == -1) {
		r = directionsRight[0];
	} else {
		r = directionsRight[i - 1];
	}
	SetR(r);
}


private func SetUpLeft() {
	var r = GetR();
	var i = IndexOfArray(directionsLeft, r);
	if (i >= (GetLength(directionsLeft) - 1))
		return;

	if (i == -1) {
		r = directionsLeft[0];
	} else {
		r = directionsLeft[i + 1];
	}
	SetR(r);
}

private func SetDownLeft() {
	var r = GetR();
	var i = IndexOfArray(directionsLeft, r);
	if (i == 0)
		return;

	if (i == -1) {
		r = directionsLeft[0];
	} else {
		r = directionsLeft[i - 1];
	}
	SetR(r);
}