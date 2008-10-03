#strict 2
/*

The player's options are stored either in the Sipwrek or in their "lock" or "options" object, of which each player has one

*/

//-------------------------------------

/**
 * Returns position of needle in haystack or -1
 * @param haystack Array in which to search
 * @param needle the thing which is searched for...
 */
global func ArrayIndexOf(array haystack, needle) {
	var len = GetLength(haystack);
	for (var i = 0; i < len; i++) {
		if (haystack[i] == needle) {
			return(i);
		}
	}
	return(-1);
}

/**
 * retrieves one player's options object
 */
global func GetOptions(int player) {
	var lock = FindObjects(Find_ID(_LOC), Find_Owner(player));
	if (GetLength(lock) > 0) {
		return lock[0];
	}
	return false;
}

protected func Initialize()
{
	// create 30 stones, flints and bones at random places.
	var tmp1, tmp2;
	var tmpObjectIDs = [ROCK, FLNT, BONE];
	for (var j = 0; j < GetLength(tmpObjectIDs); j++) {
		for (var i = 0; i < 29; i++) {
			tmp1 = Random(LandscapeWidth());
			tmp2 = Random(LandscapeHeight());
			if (GBackSemiSolid(tmp1, tmp2)) {
				CreateObject(tmpObjectIDs[j], tmp1, tmp2, -1);
			}
		}
	}

	// create drain switch
	CreateObject (_BSW, 1650, 1970);

	// clear area near the drains
	var drains = FindObjects(Find_ID(_BDR));
	for (var i = 0; i < GetLength(drains); i++) {
		for (var j = 0; j < 3; j++) {
			Explode(10, CreateObject(ROCK, GetX(drains[i]), GetY(drains[i])));
		}
	}

	tmpObjectIDs = [BUSH, PLM1, PLM2];
	for (var i = 0; i < GetLength(tmpObjectIDs); i++) {
		PlaceVegetation (tmpObjectIDs[i], 0, 0, LandscapeWidth(), LandscapeHeight(), 50 + Random(50));
	}
}

// on player initialization, create player's options object
protected func InitializePlayer(iPlr) {
	CreateObject(_LOC, 0, 0, iPlr);
}

// on player finalization, remove player's options object
protected func RemovePlayer(iPlr) {
	var tmp = FindObjects(Find_ID(_LOC), Find_Owner(iPlr));
	for (var i = 0; i < GetLength(tmp); i++) {
		RemoveObject(tmp[i], false);
	}
}

global func CheckLivesLock() {
	var options = FindObjects(Find_ID(_LOC));
	for (var i = 0; i < GetLength(options); i++) {
		if (options[i]->getLivesLock()) return(true);
	}
	return(false);
}

global func CheckLoadTimesLock() {
	var options = FindObjects(Find_ID(_LOC));
	for (var i = 0; i < GetLength(options); i++) {
		if (options[i]->getLoadTimesLock()) return(true);
	}
	return(false);
}

global func CheckHealthLock() {
	var options = FindObjects(Find_ID(_LOC));
	for (var i = 0; i < GetLength(options); i++) {
		if (options[i]->getHealthLock()) return(true);
	}
	return(false);
}

global func CheckWeaponsLock() {
	var options = FindObjects(Find_ID(_LOC));
	for (var i = 0; i < GetLength(options); i++) {
		if (options[i]->getWeaponsLock() == false) return(false);
	}
	return(true);
}