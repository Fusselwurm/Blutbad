#strict 2
/* The hook */

/*
This hook attaches a rope to itself and the rope pulls the clonk towards this hook.
*/

local user;
local rope;

public func Launch(object newUser) {
	user = newUser;
	// SetLocal (2, ObjectSetAction (CreateObject (_NR1), "Connect", this (), Local (1)));
	rope = CreateObject(_NR1);
	rope->Beam(this, user);
}

public func Hit() {
	SetAction("Hook");
	user->Fly2Hook();
}

public func Hooking() {
	if ((GetAction(user) != "ToHook") || (!rope))
		return(Break());
	return(1);
}

public func Break() {
	RemoveObject(rope);
	RemoveObject();
}