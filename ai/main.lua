dofile("ai/global.lua")
dofile("ai/utils.lua")
dofile("ai/best_first.lua")

function check_bomb(map)
	return true
end

function check_character(map)
	return true
end

function artificial_intelligence()
	-- set_priority(LEVEL)
	local entities = get_entities()
	local map = create_map(entities, AGGRO)
	display_map(map)
	if (check_bomb(map) and check_character(map)) then
		return best_first(map, entities)
	end
end

X, Y = arg["x"], arg["y"]
AGGRO = arg["aggro"]
LEVEL = arg["level"]
MAP_XMAX = AGGRO
MAP_YMAX = AGGRO
return artificial_intelligence()
