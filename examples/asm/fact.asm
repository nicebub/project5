$main1
	alloc	2
	pusha	6
	pushcI	0
	storeI
	popI	4
	enter	1
	pushs	"Enter a number: "
	call	$printf, 1
	popI	4
	enter	1
	pushs	"%d"
	pusha	5
	call	$scanf, 2
	popI	4
$1
	pusha	5
	fetchI
	pushcI	1
	ltI
	jumpz	$2
	enter	1
	pushs	"Too small\n"
	call	$printf, 1
	popI	4
	enter	1
	pushs	"%d"
	pusha	5
	call	$scanf, 2
	popI	4
	jump	$1
$2
	pusha	6
	enter	1
	pusha	5
	fetchI
	call	$fact2, 1
	storeI
	popI	4
	enter	1
	pushs	"The factorial of you number is %d\n"
	pusha	6
	fetchI
	call	$printf, 2
	popI	4
	pushcI	0
	setrvI
	returnf
$fact2
	alloc	0
	pusha	5
	fetchI
	pushcI	1
	eqI
	jumpz	$3
	pushcI	1
	setrvI
	returnf
	jump	$4
$3
	pusha	5
	fetchI
	enter	1
	pusha	5
	fetchI
	pushcI	1
	subI
	call	$fact2, 1
	mulI
	setrvI
	returnf
$4
	returnf
main
	enter	0
	alloc	0
	enter	0
	call	$main1, 0
	return
