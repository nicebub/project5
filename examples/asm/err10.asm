$main1
	alloc	2
	enter	1
	pushs	"%d"
	pusha	5
	call	$scanf, 2
	popI	4
	pusha	6
	enter	1
	pusha	5
	fetchI
	call	$count2, 1
