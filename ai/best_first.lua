function get_abs_dist(entities, x, y, i)
	return math.abs(entities[i]["x"] - x + entities[i]["y"] - y)
end

function have_elem(entities, x, y)
	for i = 1, #entities do
		if ((entities[i]["type"] == TYPE_PRIORITY["box"] or
			entities[i]["type"] == TYPE_PRIORITY["item"] or
			entities[i]["type"] == TYPE_PRIORITY["player"]) and
			get_abs_dist(entities, x, y, i) <= AGGRO) then
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

	if (have_elem(entities, cur_x, cur_y)) then
		travel_map(map_nb, cur_x, cur_y)
		print("\nFINAL MAP\n")
		display_map(map_nb)
		local nx, ny = take_shortest_priority(map_nb, entities)
		print("\ndirection is : x y : ", cur_x, cur_y)
		if (cur_x == nx and cur_y == ny) then
			return ENUM_ACTION["bomb"]
		else
			cur_x, cur_y = nx, ny
		end
	else
		cur_x, cur_y = random_movement()
	end
	return determine_way(map, cur_x, cur_y)
end
