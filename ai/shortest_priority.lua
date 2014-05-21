function determine_way(map, cur_x, cur_y)
	if (map[cur_y][cur_x] == "B") then return ENUM_ACTION["bomb"] end
	if (cur_x > X) then return ENUM_ACTION["right"] end
	if (cur_x < X) then return ENUM_ACTION["left"] end
	if (cur_y > Y) then return ENUM_ACTION["back"] end
	if (cur_y < Y) then return ENUM_ACTION["forward"] end
end

function get_shortest_distance_of(map, x, y)
	local cur_dist = AGGRO + 1
	local cur_x, cur_y = 0, 0

	if (x - 1 > 0 and type(map[y][x - 1]) == "number") then
		if (map[y][x - 1] < cur_dist) then
			cur_dist = map[y][x - 1]
			cur_x, cur_y = x - 1, y
		end
	end
	if (x + 1 < MAP_XMAX + 1 and type(map[y][x + 1]) == "number") then
		if (map[y][x + 1] < cur_dist) then
			cur_dist = map[y][x + 1]
			cur_x, cur_y = x + 1, y
		end
	end
	if (y - 1 > 0 and type(map[y - 1][x]) == "number") then
		if (map[y - 1][x] < cur_dist) then
			cur_dist = map[y - 1][x]
			cur_x, cur_y = x, y - 1
		end
	end
	if (y + 1 < MAP_YMAX + 1 and type(map[y + 1][x]) == "number") then
		if (map[y + 1][x] < cur_dist) then
			cur_dist = map[y + 1][x]
			cur_x, cur_y = x, y + 1
		end
	end
	return cur_dist, cur_x, cur_y
end

function get_good_way(map, x, y, nb)
	if (x - 1 > 0 and type(map[y][x - 1]) == "number") then
		if (map[y][x - 1] < nb) then return y, x - 1 end
	end
	if (x + 1 < MAP_XMAX + 1 and type(map[y][x + 1]) == "number") then
		if (map[y][x + 1] < nb) then return y, x + 1 end
	end
	if (y - 1 > 0 and type(map[y - 1][x]) == "number") then
		if (map[y - 1][x] < nb) then return y - 1, x end
	end
	if (y + 1 < MAP_YMAX + 1 and type(map[y + 1][x]) == "number") then
		if (map[y + 1][x] < nb) then return y + 1, x end
	end
end

function take_shortest_priority(map, entities)
	local x, tmp_x = 1000000, 1000000
	local y, tmp_y = 1000000, 1000000
	local cur_dist = 0
	local min_dist = 50
	local t = 4

	for i = 1, #entities do
		if (entities[i]["type"] ~= TYPE_PRIORITY["wall"] and
			entities[i]["type"] ~= TYPE_PRIORITY["free"] and
			(entities[i]["x"] ~= X or entities[i]["y"] ~= Y))
		then
			cur_dist, tmp_x, tmp_y = get_shortest_distance_of(map, entities[i]["x"], entities[i]["y"])
			if (cur_dist ~= AGGRO + 1 and tmp_x ~= 0 and tmp_y ~= 0) then
				if (entities[i]["type"] < t) then
					min_dist = 50
					t = entities[i]["type"]
				end
				if (min_dist > cur_dist and entities[i]["type"] == t) then
					x, y = tmp_x, tmp_y
					min_dist = cur_dist
				end
			end
		end
	end
	while (map[y][x] ~= 0 and map[y][x] ~= 1) do
		y, x = get_good_way(map, x, y, map[y][x])
	end
	return x, y
end
