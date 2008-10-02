#strict 2

protected func Process () {
	if (GetActTime() > 20) {
		return(AssignRemoval());
	}
}

protected func Completion () {
	SetAction("Sparkle");
}
