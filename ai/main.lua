dofile("ai/global.lua")
dofile("ai/utils.lua")
dofile("ai/danger_dir.lua")
dofile("ai/construct_map.lua")
dofile("ai/directions.lua")
dofile("ai/best_first.lua")
dofile("ai/actions.lua")
dofile("ai/shortest_priority.lua")

function check_item_dir(map, cur_x, cur_y, w, cond)
	for i = 0, cond do
		if ((cur_x + i ~= MAP_XMAX + 1 and map[cur_y][cur_x + i] == w) or
			(cur_x - i ~= 0 and map[cur_y][cur_x - i] == w) or
			(cur_y + i ~= MAP_YMAX + 1 and map[cur_y + i][cur_x] == w) or
			(cur_y - i ~= 0 and map[cur_y - i][cur_x] == w))
		then return true
		else return false end
	end
	return false
end

function check_elem_at(map, cur_x, cur_y, w, n)
	if (cur_x - n ~= 0 and map[cur_y][cur_x - n] == w) then return ENUM_ACTION["left"] end
	if (cur_y - n ~= 0 and map[cur_y - n][cur_x] == w) then return ENUM_ACTION["forward"] end
	if (cur_x + n ~= MAP_XMAX + n and map[cur_y][cur_x + n] == w) then return ENUM_ACTION["right"] end
	if (cur_y + n ~= MAP_YMAX + n and map[cur_y + n][cur_x] == w) then return ENUM_ACTION["back"] end
	return -1
end

function take_decision(map, map_nb, entities)
	-- print("IN TAKE DECISION MAP AFTER fill_dangerous_fields")
	-- display_map(map_nb)
	if (arg["bomb"] == 1 or
		check_elem_at(map_nb, X, Y, "D", 1) ~= -1 or
		check_elem_at(map_nb, X, Y, "O", 1) ~= -1)
	then
		if (arg["bomb"] == 1) then map[Y][X] = "O" end
		local block = {0, 0, 0, 0}
		local cur_x, cur_y = run_out_danger(map_nb, X, Y, block)
		-- print(X, Y, cur_x, cur_y)
		return determine_way(map, cur_x, cur_y)
	else
		local item = check_elem_at(map_nb, X, Y, "I", 1)
		if (check_elem_at(map_nb, X, Y, "P", 1) ~= -1 or
			check_elem_at(map_nb, X, Y, "B", 1) ~= -1) then
			return ENUM_ACTION["bomb"]
		elseif (item ~= -1) then
			return item
		end
		return best_first(map, map_nb, entities)
	end
end

function artificial_intelligence()
	set_priority(LEVEL)
	local entities = get_entities()
	local map = create_map(entities, AGGRO)
	local map_nb = create_map(entities, AGGRO)
	-- print("MAP AFTER RECONSTITUTION")
	-- display_map(map_nb)
	local action = take_decision(map, fill_dangerous_fields(map_nb), entities)
	if (action == ENUM_ACTION["bomb"]) then
		local block = {0, 0, 0, 0}
		local cur_x, cur_y = can_i_put_bomb(map_nb, X, Y, block)
		if (cur_x ~= X or cur_y ~= Y) then
			return action
		else
			cur_x, cur_y = random_movement(map)
			return determine_way(map, cur_x, cur_y)
		end
	end
	return action
end

X, Y = arg["x"], arg["y"]
AGGRO = arg["aggro"]
LEVEL = arg["level"]
-- print("BOMB ? ", arg["bomb"])
return artificial_intelligence()
