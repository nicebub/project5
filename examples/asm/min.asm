$main1
	alloc	1
	enter	1
	pushs	"Enter a number: "
	call	$printf, 1
	popI	4
	enter	1
	pushs	"%d"
	pushga	1, 5
	call	$scanf, 2
	popI	4
	enter	1
	pushs	"Enter a number: "
	call	$printf, 1
	popI	4
	enter	1
	pushs	"%d"
	pushga	1, 6
	call	$scanf, 2
	popI	4
	pusha	5
	enter	1
	pushga	1, 5
	fetchI
	pushga	1, 6
	fetchI
	call	$min2, 2
	storeI
	popI	4
	enter	1
	pushs	"The min of %d"
	pushga	1, 5
	fetchI
	call	$printf, 2
	popI	4
	enter	1
	pushs	" and %d"
	pushga	1, 6
	fetchI
	call	$printf, 2
	popI	4
	enter	1
	pushs	" is %d\n"
	pusha	5
	fetchI
	call	$printf, 2
	popI	4
	pushcI	0
	setrvI
	returnf
$min2
	alloc	0
	enter	1
	pushs	"First argument to min is %d\n"
	pusha	5
	fetchI
	call	$printf, 2
	popI	4
	enter	1
	pushs	"Second arguement to min is %d\n"
	pusha	6
	fetchI
	call	$printf, 2
	popI	4
	pusha	5
	fetchI
	pusha	6
	fetchI
	ltI
	jumpz	$1
	pusha	5
	fetchI
	setrvI
	returnf
	jump	$2
$1
	pusha	6
	fetchI
	setrvI
	returnf
$2
	returnf
main
	enter	0
	alloc	2
	enter	0
	call	$main1, 0
	return
