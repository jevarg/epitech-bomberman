print("lol")
dofile("ai/global.lua")
dofile("ai/utils.lua")
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
	if (cur_x + n ~= MAP_XMAX + n and map[cur_y][cur_x + n] == w) then return ENUM_ACTION["right"] end
	if (cur_x - n ~= 0 and map[cur_y][cur_x - n] == w) then return ENUM_ACTION["left"] end
	if (cur_y + n ~= MAP_YMAX + n and map[cur_y + n][cur_x] == w) then return ENUM_ACTION["back"] end
	if (cur_y - n ~= 0 and map[cur_y - n][cur_x] == w) then return ENUM_ACTION["forward"] end
	return -1
end

function take_decision(map, map_nb, entities)
	if (map[Y][X] == "D") then
		-- run_out_danger(map_nb, X, Y, 0)
		-- return 
	else
		display_map(map)
		if (check_elem_at(map_nb, X, Y, "P", 1) ~= -1) then
			return ENUM_ACTION["bomb"]
		end
		return best_first(map, map_nb, entities)
	end
end

function artificial_intelligence()
	local entities = get_entities()
	local map = create_map(entities, AGGRO)
	local map_nb = create_map(entities, AGGRO)
	fill_dangerous_fields(map_nb)
	return take_decision(map, map_nb, entities)
end

X, Y = arg["x"], arg["y"]
BOMB_RANGE = arg["bomb_range"]
AGGRO = arg["aggro"]
LEVEL = arg["level"]
-- print("for player in ", X, Y)
return artificial_intelligence()
