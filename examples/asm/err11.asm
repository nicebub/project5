$main1
	alloc	2
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
	pusha	6
	fetchI
	call	$printf, 2
	popI	4
	pushcI	0
	setrvI
	returnf
$count2
	alloc	2
	pusha	6
	pushcI	1
	storeI
	popI	4
	pusha	7
	pushcI	0
	storeI
	popI	4
$1
	pushs	"hello"
	jumpz	$2
	pusha	7
	pusha	7
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