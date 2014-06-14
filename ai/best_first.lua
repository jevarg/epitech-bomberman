function get_abs_dist(entities, x, y, i)
	return math.abs(entities[i]["x"] - x + entities[i]["y"] - y)
end

function determine_way(map, cur_x, cur_y)
	if (map[cur_y][cur_x] == "B") then return ENUM_ACTION["bomb"] end
	if (cur_x > X) then return ENUM_ACTION["right"] end
	if (cur_x < X) then return ENUM_ACTION["left"] end
	if (cur_y > Y) then return ENUM_ACTION["back"] end
	if (cur_y < Y) then return ENUM_ACTION["forward"] end
	return -1
end

function have_elem(entities, x, y, word)
	for i = 1, #entities do
		if (entities[i]["type"] == TYPE_PRIORITY[word] and
			get_abs_dist(entities, x, y, i) <= AGGRO and
			(entities[i]["x"] ~= x or entities[i]["y"] ~= y)) then
			return 1
		end
	end
	return 0
end

function travel_map(map, cur_x, cur_y)
	local move = 0

	map[cur_y][cur_x] = 0
	move = move + check_directions(map, cur_x, cur_y, 0, -1) 	-- up
	move = move + check_directions(map, cur_x, cur_y, 0, 1)		-- down
	move = move + check_directions(map, cur_x, cur_y, 1, 0)		-- right
	move = move + check_directions(map, cur_x, cur_y, -1, 0)	-- left
	if (move == 0) then	return end
	move = 1
	while (move == 1) do
		move = go_all_directions(map, cur_x, cur_y)
	end
end

function best_first(map, map_nb, entities)
	local cur_x, cur_y = X, Y
	-- print("best first")
	if (have_elem(entities, cur_x, cur_y, "box") == 1 or
		have_elem(entities, cur_x, cur_y, "item") == 1 or
		have_elem(entities, cur_x, cur_y, "player") == 1)then
			travel_map(map_nb, cur_x, cur_y)
			-- display_map(map_nb)
			local nx, ny = take_shortest_priority(map, map_nb, entities)
			if (cur_x == nx and cur_y == ny) then
				return ENUM_ACTION["bomb"]
			else cur_x, cur_y = nx, ny
			end
	else
		cur_x, cur_y = random_movement(map) end
	return determine_way(map, cur_x, cur_y)
end
