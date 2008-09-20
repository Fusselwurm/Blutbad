#strict 2

public func Initialize() {
	SetAction("Off");
}

public func Check() {
	if(FindObject(_KC1, -10, -10, 20, 20))
		Set();
}

public func Set() {
	var action = GetAction();
	if (action =="Off")
		return(On());
	if(action == "On")
		return(Off());
}

public func Off() {
	Message("Off", this);
	SetAction("Off");
	var drains = Find_ID(_BDR);
	for (var i = 0; i < GetLength(drains); i++) {
		drains[i]->Still();
	}
}

public func On() {
	SetAction("On");
	Message("On", this);

	var drains = Find_ID(_BDR);
	for (var i = 0; i < GetLength(drains); i++) {
		drains[i]->NuuNuu();
	}
}