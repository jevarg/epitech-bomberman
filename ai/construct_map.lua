function put_danger_around_at(map, cur_x, cur_y, n, e)
	if (cur_x + n ~= MAP_XMAX + n and
		map[cur_y][cur_x + n] ~= "O" and
		map[cur_y][cur_x + n] ~= "P") then map[cur_y][cur_x + n] = e end
	if (cur_x - n ~= 0 and
		map[cur_y][cur_x - n] ~= "O" and
		map[cur_y][cur_x - n] ~= "P") then map[cur_y][cur_x - n] = e end
	if (cur_y + n ~= MAP_YMAX + n and
		map[cur_y + n][cur_x] ~= "O" and
		map[cur_y + n][cur_x] ~= "P") then map[cur_y + n][cur_x] = e  end
	if (cur_y - n ~= 0 and
		map[cur_y - n][cur_x] ~= "O" and
		map[cur_y - n][cur_x] ~= "P") then map[cur_y - n][cur_x] = e end
end

function fill_dangerous_fields(map)
	for i = 1, #map do
		for j = 1, #map[i] do
			if (map[i][j] == "O") then
				map[i][j] = "D"
				for k = 1, BOMB_RANGE + 1 do
					put_danger_around_at(map, j, i, k, "D")
				end
			end
		end
	end
	return map
end

function set_pos_map(map)
	local max_x, max_y = 0, 0

	for i = 1, #map do
		if (map[i][1] == " ") then
			max_y = i - 1
			break
		end
		for j = 1, #map[i] do
			if (map[i][j] == " ") then
				max_x = j - 1
				break
			end
		end
	end
	return max_x, max_y
end

function create_map(entities, aggro)
	local map = {}

	for i = 1, aggro * 2 + 2 do
		table.insert(map, {})
		for j = 1, aggro * 2 + 2 do
			table.insert(map[i], " ")
		end
	end
	for i = 1, #entities do
		if (entities[i]["type"] == TYPE_PRIORITY["wall"]) then
			map[entities[i]["y"]][entities[i]["x"]] = "W" end
		if (entities[i]["type"] == TYPE_PRIORITY["free"]) then
			map[entities[i]["y"]][entities[i]["x"]] = "." end
		if (entities[i]["type"] == TYPE_PRIORITY["player"]) then
			map[entities[i]["y"]][entities[i]["x"]] = "P" end
		if (entities[i]["type"] == TYPE_PRIORITY["box"]) then
			map[entities[i]["y"]][entities[i]["x"]] = "B" end
		if (entities[i]["type"] == TYPE_PRIORITY["bomb"]) then
			map[entities[i]["y"]][entities[i]["x"]] = "O" end
	end
	MAP_XMAX, MAP_YMAX = set_pos_map(map)
	return map
end
