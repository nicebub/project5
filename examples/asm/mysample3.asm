$main1
	alloc	4
	pusha	5
	enter	1
	pusha	8
	fetchI
	call	$decide2, 1
	storeI
	popI	4
	pusha	6
	enter	1
	pusha	7
	fetchI
	call	$decide2, 1
	storeI
	popI	4
	enter	1
	pusha	8
	fetchI
	pusha	5
	fetchI
	addI
	pusha	6
	fetchI
	addI
	call	$decide2, 1
	popI	4
	pushcI	0
	setrvI
	returnf
$decide2
	alloc	0
	pusha	5
	fetchI
	setrvI
	returnf
	returnf
main
	enter	0
	alloc	8
	enter	0
	call	$main1, 0
	return
