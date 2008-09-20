#strict 2
/* CrewCarrier */

protected func Initialize()
{
	SetPosition (Random (LandscapeWidth ()), 0, this ());
	SetAction("Wrecking");
	SetR(Random (360));
	SetRDir(Random (360));
	return (1);
}

protected func Hit()
{

// 	for (var i = 0; i < 2; i++) {
//   		Explode (Sum (15, Random (30)), CreateObject (ROCK, Sum (-50, Random (100)), Sum (-50, Random (100))));
//   	}
	for (var i = 0; i < 4; i++) {
		Smoke (Sum (-50, Random (100)), Sum (-50, Random (100)), Sum (10, Random (20)));
	}
	return (1);
}

protected func Wreck()
{

// 	for (var i = 0; i < 2; i++) {
//   		Explode (Sum (15, Random (30)), CreateObject (ROCK, Sum (-50, Random (100)), Sum (-50, Random (100))));
//   	}
	for (var i = 0; i < 4; i++) {
		Smoke (Sum (-50, Random (100)), Sum (-50, Random (100)), Sum (10, Random (20)));
	}

	if (GetActTime() > Sum(50, Random(100))) {
		return(WreckWreck());
	}
	return (1);
}

private func WreckWreck()
{
	ChangeDef(_AEW);
	this->Initialize();

// 	for (var i = 0; i < 2; i++) {
// 		CastObjects (_SF1, Sum (5, Random (10)), Sum (50, Random (30)));
// 	}
// 	for (var i = 0; i < 10; i++) {
// 		Explode (Sum (35, Random (30)), CreateObject (ROCK, Sum (-50, Random (100)), Sum (-50, Random (100))));
// 	}
// 	Explode (Sum (100), CreateObject (ROCK, Sum (-50, Random (100)), Sum (-50, Random (100))));
	for (var i = 0; i < 8; i++) {
		Smoke (Sum (-50, Random (100)), Sum (-50, Random (100)), Sum (10, Random (20)));
	}

	Sound ("Detonate");
	return (1);
}