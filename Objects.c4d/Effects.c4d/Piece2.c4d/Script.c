#strict 2

protected func Hit () {
	CastPXS("Blood", 5, 100);
	CreateObject(_KS1);
	RemoveObject();
}
