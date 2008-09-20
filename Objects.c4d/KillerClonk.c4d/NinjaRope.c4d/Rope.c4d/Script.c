/* The rope */

/*

This rope attaches to the hook and the clonk. This pulls the clonk towards the hook.

*/

Beam:
	SetAction("Connect", Par (), Par (1));
	SetVertex(0,0,GetX()); SetVertex(0,1,GetY());
	SetVertex(1,0,GetX()); SetVertex(1,1,GetY());
	ForcePosition(this(),0,0);
	return(1);

LineBreak:
	Sound("LineBreak");
	RemoveObject ();
	return(1);