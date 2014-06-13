function authorized_ent_danger(map, cur_x, cur_y, i_y, i_x)
	if (map[cur_y + i_y][cur_x + i_x] == "W" or
		map[cur_y + i_y][cur_x + i_x] == "I" or
		map[cur_y + i_y][cur_x + i_x] == "P" or
		map[cur_y + i_y][cur_x + i_x] == "B")
	then
		return 1
	end
	return 0
end

function put_danger_around_at(map, cur_x, cur_y, n, e)
	-- print(MAP_XMAX, MAP_YMAX, cur_x, cur_y, n, e)
	up_danger(map, cur_x, cur_y, n, e)
	down_danger(map, cur_x, cur_y, n, e)
	left_danger(map, cur_x, cur_y, n, e)
	left_danger(map, cur_x, cur_y, n, e)
end

function fill_dangerous_fields(map)
	for i = 1, #map do
		for j = 1, #map[i] do
			if (map[i][j] == "O") then
				-- print("have bomb at ", j, i)
					local block = {0, 0, 0, 0}
				for k = 1, BOMB_RANGE do
					put_danger_around_at(map, j, i, k, "D", block)
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
			if (map[entities[i]["y"]][entities[i]["x"]] ~= "D") then
				map[entities[i]["y"]][entities[i]["x"]] = "." end
		end
		if (entities[i]["type"] == TYPE_PRIORITY["player"]) then
			map[entities[i]["y"]][entities[i]["x"]] = "P" end
		if (entities[i]["type"] == TYPE_PRIORITY["box"]) then
			map[entities[i]["y"]][entities[i]["x"]] = "B" end
		if (entities[i]["type"] == TYPE_PRIORITY["bomb"]) then
			map[entities[i]["y"]][entities[i]["x"]] = "O" end
		if (entities[i]["type"] == TYPE_PRIORITY["item"]) then
			map[entities[i]["y"]][entities[i]["x"]] = "I" end
		if (entities[i]["type"] == TYPE_PRIORITY["danger"]) then
			map[entities[i]["y"]][entities[i]["x"]] = "D" end
	end
	MAP_XMAX, MAP_YMAX = set_pos_map(map)
	return map
end
