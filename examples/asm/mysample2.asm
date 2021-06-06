$main1
	alloc	0
	pushcI	0
	setrvI
	returnf
$decide0
	alloc	8
	pushcI	1
	jumpz	$1
	pusha	5
	fetchR
	setrvR
	returnf
	jump	$2
$1
	pusha	13
	fetchR
	setrvR
	returnf
$2
	returnf
main
	enter	0
	alloc	8
	enter	0
	call	$main1, 0
	return
