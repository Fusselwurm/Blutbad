/* Abflussrohr */
#strict 2

protected func Initialize() {
	SetAction ("Still");
}

protected func Pump() {
	var j;
	for (var i = 0; i < 5; i++) {
		for (j = -2; j <= 2; j++) {
			ExtractLiquid (0, j);
		}
	}
}

public  func Still() {
	SetAction ("Still");
}

public func NuuNuu() {
	SetAction ("Drain");
}