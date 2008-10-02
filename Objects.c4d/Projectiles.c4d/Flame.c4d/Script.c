#strict 2

public func BurnProcess () {
	DoCon(3);
	var crew = FindObject(0, -5, -5, 10, 10, OCF_CrewMember);
  	if (crew) {
		RemoveObject();
		DoEnergy(-5, crew);
		CastObjects(DFLM, 2, 15);
	}
	if (Random(4) && (GetActTime() > 40))  {
		return(AssignRemoval());
	}
  	if (!OnFire()) {
  		return(AssignRemoval()); //WTF is das für ne Funktion? FIXME
	}
}

protected func Initialize () {
	Incinerate();
	SetAction("Burn");
}

protected func Hit () {
	RemoveObject();
}
