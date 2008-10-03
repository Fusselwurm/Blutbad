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

public func RotateUp() {
	var dir = InternalGetDir();
	if (dir == COMD_Right) {
		RotateUpRight();
	} else if (dir == COMD_Left) {
		RotateUpLeft();
	}
}

public func RotateDown() {
	var dir = InternalGetDir();
	if (dir == COMD_Right) {
		RotateDownRight();
	} else if (dir == COMD_Left) {
		RotateDownLeft();
	}
}

private func RotateUpRight()
{
	SetRDir(-rotationSpeed);
}

private func RotateDownRight()
{
	SetRDir(rotationSpeed);
}

private func RotateUpLeft()
{
	SetRDir(rotationSpeed);
}

private func RotateDownLeft()
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
		InternalSetR(r);
	}
}

protected func Check()
{
	if ((controllingObject != 0) && (controllingObject->getIsChangingDir() == true))
		return(0);

	var r = GetR();
	var dir = InternalGetDir();

	if (dir == COMD_Right) {
		if (r == -90) {
			StopRotating();
			InternalSetR(-89);
		} else if (r < -90) { // check if crosshair goes over the  top
			StopRotating();
			switchDirection(COMD_Right);
		} else if ((r > 45) && (r <= 90)) { // crosshair's going too far down
			StopRotating();
			InternalSetR(44);
		} else if (r > 90) { //crosshair is somehow *on the wrong side*
			switchDirection(COMD_Right);
		}
	} else if (dir == COMD_Left) {
		if ((r < 136) && (r >= 90)) { // crosshair's going too far down
			StopRotating();
			InternalSetR(136);
		} else if ((r < 90) && (r >= 0)) { //crosshair is somehow *on the wrong side*
			switchDirection(COMD_Left);
		} else if ((r > -89) && (r < 0)) { // check if crosshair goes over the  top
			StopRotating();
			switchDirection(COMD_Left);
		} else if (r == -90) { // check if crosshair goes over the  top
			StopRotating();
			InternalSetR(-91);
		}
	}
	if (GetID(controllingObject) == _KC1) {
		controllingObject->AimActionCheck();
	}
	return(1);
}

public func PntToPntUp() {
	var dir = InternalGetDir();
	if (dir == COMD_Right) {
		return(SetUpRight());
	}
	else if (dir == COMD_Left) {
		return(SetUpLeft());
	}
}

public func PntToPntDown() {

	var dir = InternalGetDir();
	if (dir == COMD_Right) {
		return(SetDownRight());
	}
	else if (dir == COMD_Left) {
		return(SetDownLeft());
	}
}

private func SetUpRight() {
	var r = GetR();
	var i = ArrayIndexOf(directionsRight, r);
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
	var i = ArrayIndexOf(directionsRight, r);
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
	var i = ArrayIndexOf(directionsLeft, r);
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
	var i = ArrayIndexOf(directionsLeft, r);
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
	SetR(r);
}

/**
 * returns the direction the crosshair should face - this is not necessarily the same as the clonk's
 */
private func InternalGetDir() {
 	var dir = controllingObject->getDirSecure();
// 	if (ArrayIndexOf([COMD_Right, COMD_Left], dir) == -1) {
// 		Log(Format("Direction %d", dir));
// 	}
	// the clonk's direction is not always the crosshair's - while scaling, for example, we want to shoot away from the wall
	var action = GetAction(controllingObject);
	if (WildcardMatch(action, "Scale*")) {
		if (dir == COMD_Right) dir = COMD_Left;
		else if (dir == COMD_Left) dir = COMD_Right;
	}
	return dir;
}