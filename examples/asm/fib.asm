$main1
	alloc	1
	enter	1
	pushs	"Enter a number: "
	call	$printf, 1
	popI	4
	enter	1
	pushs	"%d"
	pusha	5
	call	$scanf, 2
	popI	4
	enter	1
	pushs	"The first %d fibonacci numbers are:\n1\n1\n"
	pusha	5
	fetchI
	call	$printf, 2
	popI	4
	pushga	1, 5
	pushcI	0
	storeI
	popI	4
	pushga	1, 6
	pushcI	1
	storeI
	popI	4
	pushga	1, 7
	pushcI	1
	storeI
	popI	4
$1
	pushga	1, 5
	fetchI
	pusha	5
	fetchI
	pushcI	2
	subI
	ltI
	jumpz	$2
	enter	1
	call	$fib0, 0
	popI	4
	jump	$1
$2
	pushcI	0
	setrvI
	returnf
$fib0
	alloc	1
	pushga	1, 5
	pushga	1, 5
	fetchI
	pushcI	1
	addI
	storeI
	popI	4
	pusha	5
	pushga	1, 6
	fetchI
	pushga	1, 7
	fetchI
	addI
	storeI
	popI	4
	pushga	1, 6
	pushga	1, 7
	fetchI
	storeI
	popI	4
	pushga	1, 7
	pusha	5
	fetchI
	storeI
	popI	4
	enter	1
	pushs	"This is the expression: %d\n"
	pusha	5
	fetchI
	call	$printf, 2
	popI	4
	returnf
main
	enter	0
	alloc	3
	enter	0
	call	$main1, 0
	return
