protected func Initialize()
{
	if (RandomX(0, 1) == 0)
		SetAction ("TimeI");
	else
		SetAction ("TimeII");
	return(1);
}

public func Disappear()
{
	CastPXS ("Blood", 20, 50);
	RemoveObject ();
	return(1);
}