dofile("ai/global.lua")
dofile("ai/utils.lua")
dofile("ai/best_first.lua")

function check_way_out(map, cur_x, cur_y)
	local w = -1
	for i = 1, BOMB_RANGE + 1 do
		w = check_elem_at(map, cur_x, cur_y, ".", i)
		if (w == -1) then return -1 end
	end
	return w
end

function check_item_dir(map, cur_x, cur_y, w, cond)
	for i = 0, cond do
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

function take_decision(map, map_nb, entities)
	if (map[Y][X] == "D") then
		-- return check_way_out
	else
		if (check_item_dir(map_nb, X, Y, "O", BOMB_RANGE) == true) then return check_way_out(map_nb, X, Y) end
		r = check_elem_at(map_nb, X, Y, "P", 1)
		if (r ~= -1) then return ENUM_ACTION["bomb"] end
		-- r = check_elem_at(map, X, Y, "B", 1)
		-- if (r ~= -1) then return ENUM_ACTION["bomb"] end
		return best_first(map, map_nb, entities)
	end
end

function artificial_intelligence()
	-- set_priority(LEVEL)
	local entities = get_entities()
	local map = create_map(entities, AGGRO)
	local map_nb = create_map(entities, AGGRO)
	fill_dangerous_fields(map_nb)
	display_map(map)
	return take_decision(map, map_nb, entities)
end

X, Y = arg["x"], arg["y"]
BOMB_RANGE = arg["bomb_range"]
AGGRO = arg["aggro"]
LEVEL = arg["level"]
MAP_XMAX = AGGRO
MAP_YMAX = AGGRO
print("for player in ", X, Y)
return artificial_intelligence()
