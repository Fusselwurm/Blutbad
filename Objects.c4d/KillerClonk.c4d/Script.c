#strict 2
//#include CLNK

//TODO: don't raise the delay, but increase walk animation length from 8 to 16 (like with the the normal clonk)
/*-- TappajaClonk --*/

/* Locals */ //obsolete

// 0 Crosshair
// 1 The crewcarrier
// 2 Grapplin' hook
// 3 Flame

local _AEW_myWreck;
local _CR1_myCrosshair;
local aimStyle;
local isChangingDir;
local _HK1_myGrapplingHook; // exists only temporarily, created when fired
local myFlame; // if assgned, i'm on fire. ouch its hot!

/* Initialize */
protected func Initialize()
{
	aimStyle = 1;
	isChangingDir = false;

	// Weapon fully loaded
	DoMagicEnergy(100);

	// Created the crosshair
	_CR1_myCrosshair = CreateObject(_CR1);

	// The crosshair attached to the clonk
	_CR1_myCrosshair->Attach(this());

	// Walk!
	SetAction("Walk");

	SetComDir(COMD_Left);

	// Ready, Soldier!
	return(1);
}

// a bit awful, but ive no mind to think at this ungodly hour
public func Init2() {
	Contents()->Arm(this);
	SetComDir(COMD_Right);
}

// @override
protected func SetComDir(dir) {

	isChangingDir = true;

	var setCrosshair = (dir != getDirSecure());

	if (setCrosshair) {

		// if we change direction, we want the rotation direction of the crosshair to be changed, too - so e.g. rotating upwards doesnt not become downwards.
		if (GetRDir(_CR1_myCrosshair) != 0) {
			SetRDir(- GetRDir(_CR1_myCrosshair), _CR1_myCrosshair);
		}
		//also, we have to mirror the crosshair's direction.
		_CR1_myCrosshair->switchDirection(dir);
	}

	inherited(dir);

	isChangingDir = false;
}

public func getIsChangingDir() {
	return isChangingDir;
}


public func setWreck(object wreck)
{
	_AEW_myWreck = wreck;
	return(1);
}

public func setAimStyle(int style)
{
	aimStyle = style;
	SetR(0, _CR1_myCrosshair);
}

public func getAimStyle()
{
	return aimStyle;
}

public func getWreck()
{
	return(_AEW_myWreck);
}

/* Controls */

// Moving the crosshair

private func IsAimAllowed()
{
	var action = GetAction();
	return (!((action == "KneelDown") ||
			  (action == "KneelUp") ||
			  (action == "FlatUp") ||
			  (action == "Tumble") ||
			  (action == "SpecDig") ||
			  (action == "Push") ||
			  (action == "Swim") ||
			  (action == "Dead") ||
			  (action == "Scale")));
}

protected func ControlThrowSingle()  // Crosshair up!
{
	if (!(IsAimAllowed()))
		return(1);

	// If the crosshair is set to "point to point", move it up!
	if (aimStyle == 2) {
		_CR1_myCrosshair->PntToPntUp();
		return(1);
	}

	// If the crosshair is rotating, STOP IT!
	if (GetRDir(_CR1_myCrosshair) != 0) {
		_CR1_myCrosshair->StopRotating();
		return(1);
	}

	if (getDirSecure() == COMD_Right)
		_CR1_myCrosshair->RotateUpRight();
	else if (getDirSecure() == COMD_Left)
		_CR1_myCrosshair->RotateUpLeft();

	return(1);
}

// irgendwie um sicherzugehen. GetDir ist nämlich leider nicht immer sofort gleich GetComDir :(
// gibt COMD_Left, COMD_Right und -1 zurück...
public func getDirSecure() {
	var comDir = GetComDir();
	var lookDir = GetDir();
	var dir = -1;

	if (comDir == COMD_Right)
		dir = COMD_Right;
	else if (comDir == COMD_Left)
		dir = COMD_Left;
	else if (lookDir == DIR_Right)
		dir = COMD_Right;
	else if (lookDir == DIR_Left)
		dir = COMD_Left;

	return(dir);
}

protected func ControlThrowDouble()  // Rotate crosshair up or stop it
{
	if (aimStyle == 2)
		_CR1_myCrosshair->PntToPntUp();
	else
		_CR1_myCrosshair->StopRotating();

	return(1);
}

protected func ControlDigSingle()  // C down
{
	if (!(IsAimAllowed())) {
		return(1);
	}

	// If the crosshair is set to "point to point", move it down!
	if (aimStyle == 2) {
		_CR1_myCrosshair->PntToPntDown();
		return(1);
	}

	// If the crosshair is rotating, STOP IT!
	if (GetRDir(_CR1_myCrosshair) != 0) {
		_CR1_myCrosshair->StopRotating();
		return(1);
	}

	// Rotate down (right)
	if (getDirSecure() == COMD_Right)
		_CR1_myCrosshair->RotateDownRight();
	else if (getDirSecure() == COMD_Left)
		_CR1_myCrosshair->RotateDownLeft();

	return(1);
	// we have to not return false, else the Clonk will complain about "kann nicht graben"
}

protected func ControlDigDouble()  // C down
{
	if (aimStyle == 2)
		_CR1_myCrosshair->PntToPntDown();
	else
		_CR1_myCrosshair->StopRotating();

	return(1);
}

// Turnin'

protected func ControlLeft()  // Left
{

	var action = GetAction();

	// Swing with the grappling hook
	if (action == "ToHook")
		return(SwingLeft());

	// no action when doing....
	if ((action == "KneelDown") ||
	    (action == "KneelUp") ||
	    (action == "FlatUp") ||
	    (action == "Tumble") ||
	    (action == "SpecDig") ||
	    (action == "Push") ||
	    (action == "Dead") ||
	    (action == "Scale"))
		return(0);

	// Left  turn!
	SetComDir(COMD_Left);

	return(0);
}

protected func ControlRight() // Right
{
	var action = GetAction();

	// Swing with the grappling hook
	if (action == "ToHook")
		return(SwingRight());

	// no action when doing....
	if ((action == "KneelDown") ||
	    (action == "KneelUp") ||
	    (action == "FlatUp") ||
	    (action == "Tumble") ||
	    (action == "SpecDig") ||
	    (action == "Push") ||
	    (action == "Dead") ||
	    (action == "Scale"))
		return(0);

	// Right turn!
	SetComDir(COMD_Right);

	return(0);
}

// Weapons

protected func ControlSpecial()  // Shoot
{
	// If the clonk is shooting, stop it!
	if ((GetAction(Contents()) == "Shoot") || (GetAction(Contents()) == "Shooting" /*new weap*/)) {
		StopShoot();
		return(1);
	}
	else {
		Contents()->Shoot(GetR(_CR1_myCrosshair));
		return(1);
	}
}

protected func ControlSpecialDouble()  // Stop shootin' action
{
	// If shooting, stop!
	if (GetAction(Contents()) == "Shoot")
		return(StopShoot());

	// Done
	return(1);
}

protected func ControlSpecial2() // Change weapon
{
	//Contents()->WeapOff(); // od
	Contents()->DisArm(); // new
	ShiftContents();
	//Contents()->Weapon(); //old
	Contents()->Arm(this); // new
	return(1);
}

protected func ControlUp()  // Grappling hook or jump
{

	var action = GetAction();
	// If already hangin', release!
	if (action == "ToHook") {
		Release();
		return(1);
	}

	// If already shot the rope, pull it back
	if (_HK1_myGrapplingHook) {
		_HK1_myGrapplingHook->Break();
		return(1);
	}

	if ((action ==  "Jump") ||
	    (action == "Jump1") ||
	    (action == "Jump2") ||
	    (action == "Jump3") ||
	    (action == "Jump4") ||
	    (action == "Jump5") ||
	    (action == "Jump6") ||
	    (action == "Jump7"))
		LaunchHook();

	Jump();

	return(1);
}

// Diggin'

protected func ControlDownDouble()  // Dig, dug, dug
{
	// Not with these actions
	var action = GetAction();

	if ((action == "Jump") ||
	      (action == "Jump1") ||
	      (action == "Jump2") ||
	      (action == "Jump3") ||
	      (action == "Jump4") ||
	      (action == "Jump5") ||
	      (action == "Jump6") ||
	      (action == "Jump7"))
		return(1);

	if ((action == "ToHook") ||
	     (action == "KneelDown") ||
	     (action == "KneelUp") ||
	     (action == "FlatUp") ||
	     (action == "Tumble") ||
	     (action == "SpecDig") ||
	     (action == "Push") ||
	     (action == "Swim") ||
	     (action == "Dead") ||
	     (action == "Scale"))
		return(1);

	// Diggin' action
	SetAction("SpecDig");
	return(1);
}

// Mouse

protected func ControlCommand()
{
  // Does not do anything
	return(1);
}

/* Actions */

private  func SpecDigging()  // Diggin'
{
	// Dig
	DigFree(Sum (GetX(), Kosini (5)), Sum (GetY(), Sini (5)), 12);

	// Sound
	Sound("Dig*");

	// Done!
	return(1);
}

private func AimAngleToActionParameter(angle) {

	if (Inside(angle, -12, 12) || (angle < -167) || (angle > 167))
		return(1);
	else if (Inside(angle, -33, -13) || Inside(angle, -167, -147))
		return(2);
	else if (Inside(angle, -57, -34) || Inside(angle, -146, -123))
		return(3);
	else if (Inside(angle, -76, -58) || Inside(angle, -122, -104))
		return(4);
	else if (Inside(angle, -103, -77))
		return(5);
	else if (Inside(angle, 13, 33) || Inside(angle, 147, 167))
		return(6);
	else if (Inside(angle, 34, 57) || Inside(angle, 123, 146))
		return(7);


	// differenz angles are illegal. the following lines are from the original version of this script, i suspect they were pretty obsolete back then
		//   if (Inside (getAimAngle(), 58, 76)) SetVar (1, 6); // illegal
		//   if (Inside (getAimAngle(), 77, 103)) SetVar (1, 7); // illegal
		//   if (Inside (getAimAngle(), 104, 122)) SetVar (1, 6); // illegal

}

protected func WalkCheck()  // C's position check while walking
{
	// Set action that fits in with the crosshair's position
	SetAction(Format("Walk%d", AimAngleToActionParameter(getAimAngle())));
}

protected func JumpCheck()  // C's position check while jumping
{
	// Set action that fits in with the crosshair's position
	SetAction(Format("Jump%d", AimAngleToActionParameter(getAimAngle())));
}

/* Redefine */

/*TODO: why?*/
public func Redefine()
{
	// Change definition
	ChangeDef (Par(0));

	SetAction ("Walk");

	return(1);
}

protected func LaunchHook()  // Shoot the g-hook
{
  // If there is already a hook, then quit
  if (_HK1_myGrapplingHook)
    return(1);

  _HK1_myGrapplingHook = CreateContents(_HK1);

  // X coordinate
  SetVar (1, Kosini (5));

  // Y coordinate
  SetVar (2, Sini (5));

  // X direction
  SetVar (4, Kosini (20));

  // Y direction
  SetVar (5, Sini (20));

  // Angle
  SetVar (3, Random (360));

  // Shoot!
  Exit (_HK1_myGrapplingHook, Var (1), Var (2), Var (3), Var (4), Var (5), Var (3));

  // Activate the hook
  _HK1_myGrapplingHook->Launch(this);

  // Done!
  return(1);
}

// TODO: syntax. called by the hook, btw
public func Fly2Hook()  // The hook pulls the clonk
{

  // Jump, so it's easy to pull
  Jump();

  // Hang to the other end of the rope
  SetAction ("ToHook");

  // X dir
  SetVar (8, GetXDir());

  // Y dir
  SetVar (9, GetYDir());

  // Powerful pull
  SetXDir (Sum (Var (8), Kosini2 (40)));
  SetYDir (Sum (Var (9), Sini2 (40)));

  // Done!
  return(1);
}

protected func Hooking()
{

	// TODO: she hook should pull along the way the rope goes... not just in the hook's direction
  // The hook is pullin'
	if (Not (LessThan (Distance (GetX(), GetY(), GetX (_HK1_myGrapplingHook), GetY(_HK1_myGrapplingHook)), 30)))
	And (SetXDir (Sum (GetXDir(), Kosini2 (4))), SetYDir (Sum (GetYDir(), Sini2 (4))));

	// If there is no rope, release
	if(Not (_HK1_myGrapplingHook))
		return(Release());

	// Done!
	return(1);
}

protected func SwingRight() // Swing!
{
	// Turn the clonk
	SetComDir (COMD_Right);

	//   // Turn the crosshair
	//   if (GreaterThan (SetVar (0, GetR (_CR1_myCrosshair)), 130))
	//     SetR (Sum (0, Sub (180, Var (0))), _CR1_myCrosshair);
	//   if (LessThan (Var (0), -90))
	//     SetR (Sub (180, Var (0)), _CR1_myCrosshair);

	// The hook pulls
	SetXDir (Sum (GetXDir(), 2));
	SetYDir (Sum (GetYDir(), 2));

	// Done!
	return(1);
}

protected func SwingLeft() // Swing!
{
	// Turn the clonk
	SetComDir(COMD_Left);

	// shouldnt be necessary, we do this in the overridden setcomdir()
// 	// Turn the crosshair
// 	if (Inside (SetVar (0, GetR (_CR1_myCrosshair)), 1, 89))
// 		SetR(Sum (180, Sub (Var (0), Mul (Var (0), 2))), _CR1_myCrosshair);
// 	if (Inside (Var (0), -89, -1))
// 	SetR (Sum (180, Sub (Var (0), Mul (Var (0), 2))), _CR1_myCrosshair);
// 	if (Equal (Var (0), 0))
// 	SetR (180, _CR1_myCrosshair);

	// The hook pulls
	SetXDir (Sub(GetXDir(), 2));
	SetYDir (Sum(GetYDir(), 2));

	// Done!
	return(1);
}

protected func Release()  // Release the hook
{
	// Release
	_HK1_myGrapplingHook->Break();

	// Walk
	SetAction("Walk");

	return(1);
}


protected func CatchBlow()  // Explode nearby
{
	// Not if the clonk is dead
	if (GetAction() == "Dead")
		return(0);

	// Blood effect
	CastObjects(_EB1, (5 * _AEW_myWreck->getBloodLevel()), 50);

	// Every 5th time the clonk gets more badly hurt
	if (Random(5) == 0)
		Hurt();

	return(1);
}

protected func Hurt()  // Ai! Ei!
{
	// BloooD
	CastObjects(_EB1, (8 * _AEW_myWreck->getBloodLevel()), 50);
	Sound("Hurt*");
}

protected func Grab()  // Grabs something
{
	Sound ("Grab");
}

protected func Get()  // Gets something
{
	Sound ("Grab");
}

protected func Put()  // Puts something smewhere
{
	Sound("Grab");
}

//@override
protected func Death(int iKilledBy){  // Deeaatth!

	// Blood spreads around according to the settings
	CastObjects(_EB1, (15 * _AEW_myWreck->getBloodLevel()), 50);

	// Gibs
	CastObjects (_PC1, 5, 35);
	CastObjects (_PC2, 5, 25);
	CastObjects (_PC3, 5, 30);

	// Severed head
	CastObjects (_PC4, 1, Sum (25, Random (10)));

	// Remove the crosshair
	RemoveObject(_CR1_myCrosshair);

	// Aaarrrggghhh!
	Sound ("Die");

	// Death
	RemoveObject();

	// Check lives left
	_AEW_myWreck->CheckLives();

	return(1);
}

protected  func StopShoot()  // Stop shooting sequence
{
	Contents()->StopShooting();
	return(1);
}

protected func DeepBreath()  // Air! Need air!
{
	// Sound
	Sound ("Breath");
}

private  func Incineration()  // Burn baby burn!
{
	// Aaahhh
	Extinguish();

	// if the clonk is already on fire
	if (myFlame)
		return(1);  // Quit the function

	myFlame = CreateObject(_HFO);
	myFlame->Start(this());
	DoEnergy (-5);
	return(1);
}

/* Calculator */

// omfg - the weapons call this Calculations just so they know where to fire.
// TODO: direction (angle) should be parameter of [weapon]->shoot(). Weapons (hook included) should not have to call methods of their bearer! - this goes for: Kosini(), Kosini2(), Sini(), Sini2(), getAimAngle(), Angle2()

public  func Kosini()  // Cosine, int Distance
{
  return(Cos (getAimAngle(), Par (0)));
}

public  func Kosini2()  // Cosine, int Distance
{
  return(Cos (Angle2(), Par (0)));
}

public  func Sini2()  // Sine, int Distance
{
  return(Sin (Angle2(), Par (0)));
}

public  func Sini()  // Sine, int Distance
{
  return(Sin (getAimAngle(), Par (0)));
}

public func getAimAngle()  // Crosshair's angle
{
	// Returns the angle of the crosshair
	return(GetR (_CR1_myCrosshair));
}

public func Angle2()  // Hook's angle
{

	// Var 1 is the angle between the hook and this clonk
	SetVar (1, Angle (GetX(), GetY(), GetX (_HK1_myGrapplingHook), GetY (_HK1_myGrapplingHook)));

	// Converts the var 1 to a number, that the "Kosini" can use
	SetVar (1, Sub (Var (1), 90));
	if (GreaterThan (Var (1), 180))
		SetVar (1, Sub (Var (1), 360));

	// Done and return the final value
	return(Var (1));
}