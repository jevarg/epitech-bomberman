dofile("ai/global.lua")
dofile("ai/utils.lua")
dofile("ai/best_first.lua")

function check_entities(entities)
	
end

function check_way_out(map, cur_x, cur_y, w)
	if (cur_x + 1 ~= MAP_XMAX + 1 and map[cur_y][cur_x + 1] == w) then return ENUM_ACTION["right"] end
	if (cur_x - 1 ~= 0 and map[cur_y][cur_x - 1] == w) then return ENUM_ACTION["left"] end
	if (cur_y + 1 ~= MAP_YMAX + 1 and map[cur_y + 1][cur_x] == w) then return ENUM_ACTION["back"] end
	if (cur_y - 1 ~= 0 and map[cur_y - 1][cur_x] == w) then return ENUM_ACTION["forward"] end
	return -1
end

function check_item_dir(map, cur_x, cur_y, w)
	for i = 0, AGGRO do
		if (cur_x + i ~= MAP_XMAX + 1) then
			if (map[cur_y][cur_x + i] == w) then return true end
		elseif (cur_x - i ~= 0) then
			if (map[cur_y][cur_x - i] == w) then return true end
		elseif (cur_y + i ~= MAP_YMAX + 1) then
			if (map[cur_y + i][cur_x] == w) then return true end
		elseif (cur_y - i ~= 0) then
			if (map[cur_y - i][cur_x] == w) then return true end
		else
			return false
		end
	end
	return false
end

function take_decision(map, entities)
	if (check_item_dir(map, X, Y, "O") == true) then return check_way_out(map, X, Y, ".") end
	r = check_way_out(map, X, Y, "P")
	if (r ~= -1) then return ENUM_ACTION["bomb"] end
	r = check_way_out(map, X, Y, "B")
	if (r ~= -1) then return ENUM_ACTION["bomb"] end
	return best_first(map, entities)
end

function artificial_intelligence()
	-- set_priority(LEVEL)
	local entities = get_entities()
	local map = create_map(entities, AGGRO)
	display_map(map)
	return take_decision(map, entities)
end

X, Y = arg["x"], arg["y"]
AGGRO = arg["aggro"]
LEVEL = arg["level"]
MAP_XMAX = AGGRO
MAP_YMAX = AGGRO
print("for player in ", X, Y)
return artificial_intelligence()
