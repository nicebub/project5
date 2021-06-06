$main1
	alloc	1
	enter	1
	pushs	"%d"
	pusha	5
	call	$scanf, 2
	popI	4
	enter	1
	pusha	5
	fetchI
	call	$count2, 1
	popI	4
	enter	1
	pushs	"%d\n"
	pushga	1, 5
	fetchI
	call	$printf, 2
	popI	4
	pushcI	0
	setrvI
	returnf
$count2
	alloc	1
	pusha	6
	pushcI	1
	storeI
	popI	4
	pushga	1, 5
	pushcI	0
	storeI
	popI	4
$1
	pusha	6
	fetchI
	pusha	5
	fetchI
	leI
	jumpz	$2
	pushga	1, 5
	pushga	1, 5
	fetchI
	pusha	6
	fetchI
	addI
	storeI
	popI	4
	pusha	6
	pusha	6
	fetchI
	pushcI	1
	addI
	storeI
	popI	4
	jump	$1
$2
	returnf
main
	enter	0
	alloc	1
	enter	0
	call	$main1, 0
	return
