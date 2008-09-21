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
		//Log(Format("switchDirection - SetR: %d", r));
		InternalSetR(r);
	}
}

protected func Check()
{
	if ((controllingObject != 0) && (controllingObject->getIsChangingDir() == true))
		return(0);

	var r = GetR();
	var dir = controllingObject->getDirSecure();

	if (dir == COMD_Right) {
		if (r == -90) {
			//Log(Format("1Check - SetR: %d", r));
			StopRotating();
			InternalSetR(-89);
		} else if (r < -90) { // check if crosshair goes over the  top
			//Log(Format("2Check - SetR: %d", r));
			StopRotating();
			switchDirection(COMD_Right);
		} else if ((r > 45) && (r <= 90)) { // crosshair's going too far down
			//Log(Format("3Check - SetR: %d", r));
			StopRotating();
			InternalSetR(44);
		} else if (r > 90) { //crosshair is somehow *on the wrong side*
			//Log(Format("4Check - SetR: %d", r));
			switchDirection(COMD_Right);
		}
	} else if (dir == COMD_Left) {
		if ((r < 136) && (r >= 90)) { // crosshair's going too far down
			//Log(Format("5Check - SetR: %d", r));
			StopRotating();
			InternalSetR(136);
		} else if ((r < 90) && (r > 0)) { //crosshair is somehow *on the wrong side*
			//Log(Format("6Check - SetR: %d", r));
			switchDirection(COMD_Left);
		} else if ((r > -89) && (r < 0)) { // check if crosshair goes over the  top
			//Log(Format("7Check - SetR: %d", r));
			StopRotating();
			switchDirection(COMD_Left);
		} else if (r == -90) { // check if crosshair goes over the  top
			//Log(Format("8Check - SetR: %d", r));
			StopRotating();
			InternalSetR(-91);
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
	InternalSetR(r);
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
	InternalSetR(r);
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
	InternalSetR(r);
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
	InternalSetR(r);
}

/**
 * so that I can write a debug message before InternalSetR() occurs ;)
 */
private func InternalSetR(r) {
	//Log(Format("SetR: %d", r));
	SetR(r);
}