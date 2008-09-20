#strict 2

public func Initialize() {
	SetAction ("Fly");
}

public func Hit() {
	Explode (Sum (25, Random (10)));
	CastObjects (_SPL, 2, Sum (30, Random (20)));
}

public func Flying() {
	if (FindObject(0, -5, -5, 10, 10, OCF_CrewMember))
		return(Hit());
	if (Not (Local (1)))
		SetLocal (1, GetXDir ());
	if (Not (Local (2)))
		SetLocal (2, GetYDir ());
	if (GetActTime() > 150)
		Hit ();
	SetXDir(Local (1));
	SetYDir(Local (2));
}