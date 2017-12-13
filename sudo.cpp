/*

create initial vehicle

main loop

	if condition for changing vehicle
		vehicle = new vehicle(~new vehicle stats and model~)

	if acceleration button isPressed
		vehicle.accelerate(true)
	else
		vehicle.accelerate(false)

	//Note the bool is for direction (true = right, false = left)
	if turnRight button isPressed
		vehicle.turn(true)
	else if turnLeft button isPressed
		vehicle.turn(false)

	//Set the tilt and roll of the current vehicle (don't know if this is actually possible)
	if normal.y of ground at vehicle position != vehicle.getTilt()
		vehicle.setTilt(normalGround.y)

	if normal.z of ground at vehicle position != vehicle.getRoll()
		vehicle.setRoll(normalGround.z)

	draw ground (presumably a gaint plane, enless we want to get more complicated)
	draw hot air balloons (maybe? if we have those)
	draw anything else the environment needs (if we actually want to add some character)

	for all collectibles
		if collectible.canBeCollected(vehicle pos)
			collect that collectible!
			remove collectible from collectible list
			increment score
			add fuel (possibly)
		else if collectible.isClose(vehicle pos)
			highlight collectible in some way
		push matrix
		apply collectible transformation
		draw collectible
		pop matrix

	push matrix
	apply vehicle transformation
	draw vehicle
	pop matrix
	
*/