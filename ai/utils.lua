function display_map(map)
	for i = 1, #map do
		for k, v in pairs(map[i]) do
			io.write(map[i][k])
			nb = tonumber(map[i][k])
			if (nb ~= nil) then
				if (nb > 9) then
					io.write("  ")
				else
					io.write("   ")
				end
			else
				io.write("   ")
			end
		end
		io.write("\n")
	end
end

function get_abs_dist(entities, x, y, i)
	return math.abs(entities[i]["x"] - x + entities[i]["y"] - y)
end

function have_elem(entities, x, y)
	for i = 1, #entities do
		if (get_abs_dist(entities, x, y, i) <= AGGRO) then
			return 1
		end
	end
	return 0
end

function random_movement()
	local mov = {1, -1, 1, -1}
	local n = math.random(1, 4)

	if (n == 1 or n == 2) then
		local x = X + mov[n]
		if (x < 1) then x = 1 end
		if (x > MAP_XMAX) then x = MAP_XMAX end
	else
		local y = Y + mov[n]
		if (y < 1) then y = 1 end
		if (y > MAP_YMAX) then y = MAP_YMAX end
	end
	return x, y
end

function set_priority(player, item, box, bomb)
	TYPE_PRIORITY["player"] 	= player
	TYPE_PRIORITY["item"]		= item
	TYPE_PRIORITY["box"]		= box
	TYPE_PRIORITY["bomb"]		= bomb
end

function set_aggro(a)
	AGGRO = a
end
